// PROGRAM	: U4_5.c						2020.0519
// FUNCTION	: DHT-22 Reading Program		By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	pLCMEN		_pe2	
#define	pLCMRW		_pe1	
#define	pLCMRS		_pe0	
#define	pLCMENC		_pec2	
#define	pLCMRWC		_pec1	
#define	pLCMRSC		_pec0	
#define	LCMData		_pg
#define	LCMDataC	_pgc
#define	pDHT		_pc2					//DHT信號輸出連接腳位
#define	pDHTC		_pcc2
#define	pDHTPU		_pcpu2
#define	fSYS		8000000					//系統工作時脈
//#define StartTC		(1*(fSYS/(4*1000)))	//DHT22 Start信號時間參數:1ms (Error Demonstration when fINT=fSYS/4)
#define StartTC		((u32)1*fSYS/(16*1000))	//DHT22 Start信號時間參數:1ms[1ms/(1/fINT)] where fINT=fH/16 

const u8 STR1[] = {" Humi.:   .  %RH"};		//字串1建表			
const u8 STR2[] = {" Temp.:   .  Deg"};		//字串2建表
u8 ReadDHT(u16*,u16*);
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
void main()
{	const u8* ptr;
	u16 h,t;
	_wdtc=0b10101111;						//關閉看門狗計時器
	pDHTC=1; pDHTPU=1; 						//PC2設置為輸入並致能提升電阻
	LCMInit();				           		//LCM初始化
	LCMWrite(0,0x80); ptr=STR1;				//第一列
	while(*ptr!=0) LCMWrite(1,*ptr++); 		//顯示STR1[]字串
	LCMWrite(0,0xC0); ptr=STR2;				//第二列
	while(*ptr!=0) LCMWrite(1,*ptr++); 		//顯示STR2[]字串
	while(1)
	{	while(ReadDHT(&h,&t)==1)			//正確讀取DHT22?
		{	LCMWrite(0,0x88);
			LCMWrite(1,h/100+'0'); h%=100;	//顯示溼度:十位數
			LCMWrite(1,h/10+'0'); h%=10;	//顯示溼度:個位數
			LCMWrite(0,0x8B);
			LCMWrite(1,h+'0');				//顯示溼度:小數點後一位
			LCMWrite(0,0xC8);
			LCMWrite(1,t/100+'0'); t%=100;	//顯示溫度:十位數
			LCMWrite(1,t/10+'0'); t%=10;	//顯示溫度:個位數
			LCMWrite(0,0xCB);				//顯示溫度:小數點後一位
			LCMWrite(1,t+'0');
			Delayms(1000);					//延遲1秒
		}
	}
}
u8 ReadDHT(u16* ptrh,u16* ptrt)
{	u32	temp=0,temp1=(u32)1<<31; //MSB first 
	volatile u16 TCnt; volatile u8 parity=0;
	_ptm0c0=0x20;							//fINT=fSYS/16
	_ptm0c1=0b10110000;						//Single-Pulse/Active Low
	_ptm0al=(u8)StartTC; _ptm0ah=StartTC>>8;//Start Signal
	_pcs0=0x20;								//PC2==>PTP0		
	_ptm0af=0; _pt0on=1; 					//開始輸出
	while(!_ptm0af); 						//等待Start Signal結束
	_pcs0=0;								//PC2==>I/O 						
	_ptm0c0=0;								//fINT=fSYS/4
	_ptm0c1=0b01010000;						//Capture I/P,負緣捕捉 
	_ptm0rpl=(u8)400; _ptm0rph=400>>8;		//設置捕捉值上限(Response=80+80us, max:85us*2)
	_ptp0ips=0;								//PTP0I -> PC2 (IFS1)	
 	_ptm0af=0; _ptm0pf=0; 					//清除旗標
 	while(pDHT);							//等待DHT Pull-low
	_pt0on=1; 								//啟動Capture
	while(!_ptm0af)							//等待DHT結束Response	
	{	if(_ptm0pf) { _pt0on=0; return 0;}	//超過時間未回應,讀取錯誤
	} 
	_pt0on=0;
	TCnt=_ptm0ah; TCnt=(TCnt<<8)|_ptm0al;	//取得捕捉值
	if(TCnt<240) return 0;					//Response信號過短,讀取錯誤(min:75us*2) 
	while(temp1!=0)							//取得32-Bit資料
	{	_ptm0af=0; _pt0on=1;				//啟動Capture
		while(!_ptm0af);					//等待負緣捕捉		
		_pt0on=0;
		TCnt=(u16)_ptm0ah<<8; TCnt|=_ptm0al;//取得捕捉值	
		if(TCnt>190) temp|=temp1;			//0:78us(70us~85us), 1:120us(116us~130us)
		temp1>>=1;
	}
	temp1=1<<7;	 							//取得Check Sum
	while(temp1!=0)
 	{	_ptm0af=0; _pt0on=1;				//啟動Capture
		while(!_ptm0af);					//等待負緣捕捉
		_pt0on=0;
		TCnt=(u16)_ptm0ah<<8; TCnt|=_ptm0al;//取得捕捉值	
		if(TCnt>190) parity|=temp1;			//0:78us(70us~85us), 1:120us(116us~130us)
		temp1>>=1;
	}
	while(!pDHT);							//等待End Signal結束
	TCnt=temp;								//計算 Checksum
	TCnt+=temp>>8;
	TCnt+=temp>>16;
	TCnt+=temp>>24;
	if((u8)TCnt!=parity) return 0;			//Checksum Error
	*ptrt=temp; *ptrh=temp>>16;				//取得溫度、濕度
	return 1;								//回傳1(正確讀取)
}
void LCMInit(void)
{	pLCMEN=0; pLCMRW=0; pLCMRS=0;	      	//設定EN/RW/RS腳位為低電位
	pLCMENC=0; pLCMRWC=0; pLCMRSC=0;	 	//設定EN/RW/RS腳位為輸出模式
	Delayms(40);							//LCM Power-On Time
	LCMWrite(0,0x38);						//功能設定:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);						//顯示控制:Display on, No Cursor
	LCMWrite(0,0x06);						//進入模式:Increse, Not Shift
	LCMWrite(0,0x01);						//清除LCM
}
u8 LCMWrite(_Bool fgCD,u8 CD)
{	u8 BusyAC;
	LCMDataC=0b11111111;					//規劃Port為輸入模式
	pLCMRS=0; pLCMRW=1;						//RS=0,RW=1 (Read IR)
	GCC_NOP(); 								//tAS
	do
	{	pLCMEN=1; GCC_NOP();				//EN=1,tDDR
		BusyAC=LCMData;						//讀取LCM IR
		pLCMEN=0;							//EN=0	
	} while (BusyAC & 1<<7);				//若LCM忙碌,再次讀取
	LCMDataC=0;								//規劃Port為輸出模式
	pLCMRW=0;								//RW=0 (Write)
	pLCMRS=fgCD;							//依fgCD值設置 RS腳位狀態
	LCMData=CD;								//送出資料或命令
	pLCMEN=1; GCC_NOP(); pLCMEN=0; 			//EN=1,tPW,EN=0
	return BusyAC;							//回傳Address Counter
}
void Delayms(u16 del)
{	u16 i;									//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}
