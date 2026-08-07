// PROGRAM	: ModifyU6_4_1V2.c				2022.0905
// FUNCTION	: I2C Master R/W Demo Program	By Steven
// Library	: eDisplayV2.c
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.H"
#define  KeyPort	_pg			
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define  SIDPort	_pe			
#define  SIDPortC	_pec
#define  SIDPortPU	_pepu
u8 ScanKey(void);
void main()
{	volatile u8 Key,SlaveID; 	
	_wdtc=0b10101111;						//關閉看們狗計時器
	SIDPortC=0xFF; SIDPortPU=0xFF; 			//ID_Port as I/P & Enable Pull-up
	eDisplayReset();						//Reset eDisplay(含I2C_Init())
	eDisplayRet( 0,128, 0,128,Blue);		//繪製矩形區域
	eDisplayStr(32, 5,(u8*)"U6_4_1V2");
	eDisplayStr(24,25,(u8*)"IIC Master");
	eDisplayStr(20,90,(u8*)"TRX. Cnt:0");
	while(1)
	{	do  							   	//等待按壓4x4 Keypad
	   	{	Key=ScanKey();
			eDisplayStr(4,60,(u8*)"Press Keypad...");
			ForeColor=~ForeColor;
		   	Delayms(80);			   		//Delay 80ms
	   	} while (Key==16);
		Key+=(Key<10)?'0':'7';				//ASCII轉換
		ForeColor=Yellow;
		eDisplayRet(4,124,60,14,BackColor);	//清除Press Keypad...字串
		eDisplayChar(60,60,Key);			//顯示按鍵值
	   	SlaveID=(SIDPort & 0x1F)<<1;		//取得欲傳輸的Slave ID
		I2C_START(); 						//送出START Condition
		WriteByte(SlaveID|0);				//送出Device ID,及Write
		if(CheckACK()) 						//是否有裝置回應ACK
		{	WriteByte(Key);					//若有裝置回應則送出
			CheckACK();						//檢查裝置回應
			I2C_STOP();						//送出STOP Condition
	   		Delayms(250);			
			I2C_START(); 					//送出START Condition
			WriteByte(SlaveID|1);			//送出Device ID,及Read
			while(!CheckACK());				//是否有裝置回應ACK
			Key=ReadByte();					//若有裝置回應則讀取並顯示
			SDAC=0; SDA=1; 					//送出NOACK，只讀一筆
			SCL=1; GCC_DELAY(10); SCL=0;	 		
			I2C_STOP();						//送出STOP Condition
			eDisplayChar(92,90,Key+'0');	//顯示接收值
		}
		else
		{	I2C_STOP();						//送出STOP Condition
			ForeColor=Red;
			eDisplayStr(4,60,(u8*)"...ID Not Exist");
			ForeColor=Yellow;
			Delayms(1500); 			       	//延遲1.5秒
		}
	Delayms(1500); 			             	//延遲1.5秒
	}
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
