// PROGRAM	: U6_4_1.c						2017.0526
// FUNCTION	: I2C Master R/W Demo Program	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define  SEGPort	_pg
#define  SEGPortC	_pgc
#define  KeyPort	_pc			
#define  KeyPortC	_pcc
#define  KeyPortPU	_pcpu
#define  SIDPort	_pe			
#define  SIDPortC	_pec
#define  SIDPortPU	_pepu
#define	 SCLC		_pfc3
#define	 SDAC		_pfc2
#define	 SCL		_pf3
#define	 SDA		_pf2
#define	 SDAPU		_pfpu2
const u8 SEG_TAB[] = {0x3F,0x06,0x5B,0x4F,	//7-Segment Table(0~F)
			0x66,0x6D,0x7D,0x07,0x7F,0x67,
			0x77,0x7C,0x58,0x5E,0x79,0x71};
void I2C_Init(void)	;
void I2C_START(void);
void I2C_STOP(void);
_Bool CheckACK(void);
void WriteByte(u8);
u8 ReadByte(void);
u8 ScanKey(void);
void Delayms(u16);
void main()
{	volatile u8 Key,DeviceID; 	
	_wdtc=0b10101111;						//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;					//清除Port並規劃為輸出屬性
	SIDPortC=0xFF; SIDPortPU=0xFF; 			//ID_Port as I/P & Enable Pull-up
	I2C_Init();								//腳位初始化
	while(1)
	{	do  							   	//等待按壓4x4 Keypad
	   	{	Key=ScanKey();
	      	SEGPort^=(1<<6);				//改變七段顯示器G節段之狀態
		   	Delayms(80);			   		//Delay 80ms
	   	} while (Key==16);
	   	SEGPort=SEG_TAB[Key];				//顯示鍵值
	   	DeviceID=(SIDPort & 0x1F)<<1;		//取得欲傳輸的Slave ID
		I2C_START(); 						//送出START Condition
		WriteByte(DeviceID|0);				//送出Device ID,及Write
		if(CheckACK()) 						//是否有裝置回應ACK
		{	WriteByte(SEG_TAB[Key]);		//若有裝置回應則送出
			CheckACK();						//檢查裝置回應
			I2C_STOP();						//送出STOP Condition
	   		Delayms(1000);			
			I2C_START(); 					//送出START Condition
			WriteByte(DeviceID|1);			//送出Device ID,及Read
			while(!CheckACK());				//是否有裝置回應ACK
			SEGPort=SEG_TAB[Key=ReadByte()];//若有裝置回應則讀取並顯示
			SDAC=0; SDA=1; 					//送出NOACK，只讀一筆
			SCL=1; GCC_DELAY(10); SCL=0;	 		
			I2C_STOP();						//送出STOP Condition
	   		Delayms(250);					//延遲0.25秒
		}
		else
		{ 	SEGPort|=(1<<7);               	//點亮七段顯示器dp節段
			I2C_STOP();						//送出STOP Condition
		}
	Delayms(250); SEGPort=0;             	//延遲0.25秒，熄滅七段顯示器
	}
}
void I2C_Init(void)							//20200326
{	SDAPU=1; SCL=1; SDA=1;					//設定 SCL=1, SDA=1
	SCLC=0; SDAC=0; 					   	//SCL/SDA為輸出模式
}
void I2C_START(void)
{	SCL=0; SDA=1; SDAC=0;					//設定 SCL=0, SDA=1
	SCL=1;  								//SCL=1, SDA=1
	SDA=0; GCC_DELAY(10);					//SDA=0 			     						
	SCL=0; 									//SCL=0
}
void I2C_STOP(void)
{	SDA=0; SDAC=0; GCC_DELAY(10);			//設定SDA=0並為輸出模式()
	SCL=1; SDAC=0; GCC_DELAY(10);			//SCL=1
	SDA=1;									//SDA=1
}
_Bool CheckACK(void)
{	u8 i=200;
	SDAC=1;									//設定SDA為輸入模式
	SCL=1; GCC_DELAY(10); 					//設定 SCL=1
	while(i--)
	{	if(!SDA) { SCL=0; return 1;}		//若裝置回應ACK則返回並回傳1
		GCC_DELAY(200);						//200*100uS=20ms 若20ms未回應
	} 
	SCL=0; 									//SCL=0
	return 0; 								//若20ms未回應回傳0
}
void WriteByte(u8 I2CData)
{	u8 temp=0b10000000;
	SDAC=0;									//SDA為輸出模式
	while(temp)								//傳送8個位元
	{	SDA=(I2CData & temp)?1:0; 			//設定 SDA 準位
		SCL=1; GCC_DELAY(8); SCL=0;	    	//產生 SCL Clock
		temp>>=1;							//下一位元
	} 
}
u8 ReadByte(void)
{	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 		//設定 SDA 為輸入模式
	while(temp)								//接收8個位元
	{	SCL=1; GCC_DELAY(8);				//設定 SCL=1
		if(SDA) I2CData|=temp;				//接收位元值
		SCL=0; 								//設定 SCL=0
		temp>>=1;							//下一位元
	}					
	return I2CData;
}
u8 ScanKey(void)
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					 	//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)						//依序檢查四列
	{	if(!(KeyPort & 1<<7)) break;		//檢查第0行(KeyPort[4])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;		//檢查第1行(KeyPort[5])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;		//檢查第2行(KeyPort[6])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<4)) break;		//檢查第3行(KeyPort[7])是否按下
		key++;								//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;	//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}
void Delayms(u16 del)						//@fSYS=8MH,延遲del*ms				
{	u16 i;							
	for(i=0;i<del;i++) GCC_DELAY(2000);		//延遲del*2000指令週期			
}