// PROGRAM	: 5-6EXT.c							2025.0711
// FUNCTION	: 20*2 LCM Contrl Demo Program		By Steven
#include <HT66F2390.h>
#define	 pLCMEN		_pe2	
#define  pLCMRW		_pe1	
#define  pLCMRS		_pe0	
#define  pLCMENC	_pec2	
#define  pLCMRWC	_pec1	
#define  pLCMRSC	_pec0	
#define  LCMData	_pg
#define  LCMDataC	_pgc	   
#include "Mytype.H"
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	LCMInit();				           			//LCM Initialization
	while(1)
	{	LCMWrite(0,0x01);						//Clear LCM Display						
		LCMWrite(0,0x06);						//COMD:Increment, Not Shift
		for(i=0;i<16;i++)
		{	LCMWrite(1,'1'); Delayms(100);  	//Dispay "1"
		}
		LCMWrite(0,0x80+16+(16>>1)-3);			//Set Line 1, Position 	COL+COL/2	
		LCMWrite(1,'H');		
		LCMWrite(1,'e');
		LCMWrite(1,'l');
		LCMWrite(1,'l');
		LCMWrite(1,'o');
		
		LCMWrite(0,0x80+0x40+16+(16>>1)-3);		//Set Line 2, Position COL+COL/2	
		LCMWrite(1,'W');		
		LCMWrite(1,'o');
		LCMWrite(1,'r');
		LCMWrite(1,'l');
		LCMWrite(1,'d');
		LCMWrite(1,'!');
		
		LCMWrite(0,0xC0+16-1);					//Set Line 2, Position COL-1
		LCMWrite(0,0x04);						//COMD:Decrement, Not Shift
		for(i=0;i<16;i++) 
		{	LCMWrite(1,'2'); Delayms(100);		//Dispay "2"
		}  
		for(i=0;i<16;i++) 
		{	LCMWrite(0,0x18);					//shift
			Delayms(200);
		}  
		Delayms(100);
		for(i=0;i<16;i++) 
		{	LCMWrite(0,0x1C);					//Shift
			Delayms(200);
		}  
	}
}
void LCMInit(void)
{	pLCMEN=0; pLCMRW=0; pLCMRS=0;	        	//設定EN/RW/RS腳位為低電位
	pLCMENC=0; pLCMRWC=0; pLCMRSC=0;	  		//設定EN/RW/RS腳位為輸出模式
	Delayms(40);								//LCM Power-On Time
	LCMWrite(0,0x38);							//功能設定:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0F);							//顯示控制:Display/Cursor Blinking On
	LCMWrite(0,0x06);							//進入模式:Increse, Not Shift
	LCMWrite(0,0x01);							//清除LCMy
}
u8 LCMWrite(_Bool fgCD,u8 CD)
{	u8 BusyAC;
	LCMDataC=0b11111111;						//規劃Port為輸入模式
	pLCMRS=0; pLCMRW=1;							//RS=0,RW=1 (Read IR)
	GCC_NOP(); 									//tAS
	do
	{	pLCMEN=1; GCC_NOP();					//EN=1,tDDR
		BusyAC=LCMData;							//讀取LCM IR
		pLCMEN=0;								//EN=0	
	} while (BusyAC & 1<<7);					//若LCM忙碌,再次讀取
	LCMDataC=0;									//規劃Port為輸出模式
	pLCMRW=0;									//RW=0 (Write)
	pLCMRS=fgCD;								//依fgCD值設置 RS腳位狀態
	LCMData=CD;									//送出資料或命令
	pLCMEN=1; GCC_NOP(); pLCMEN=0; 				//EN=1,tPW,EN=0
	return BusyAC;								//回傳Address Counter
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}