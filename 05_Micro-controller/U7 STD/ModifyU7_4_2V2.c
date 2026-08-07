// PROGRAM	: ModifyU7_4_2V2.c					2022.0101
// FUNCTION	: UART Wake-up control (Slave)		By Steven
// NOTE		: RGB-G Flash : wait Data Received
//					OFF	  : enter SLEEP Mode
// 			  use e-Display to Deisplay Received Data
// LIBRARY	: eDisplay.c  
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplay.H"
#define	 fH		8000000							//MCU HIRC Frequency
#define  BR		19200							//Baud Rate
#define  pGLED	_pd2			
#define  pGLEDc	_pdc2
volatile u8 Count=0;
volatile bit fgRX=0, fgSleep=0;
void main()
 {	u8 RxCount=1,tmp;
 	_wdtc=0b10101111;							//關閉看門狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	eDisplayStr(32, 5,(u8*)"U7_4_2V2");
	eDisplayStr(24,25,(u8*)"UART Slave");
	eDisplayStr(20,90,(u8*)"REC. Cnt:0");
	feDisplay5DigitNoSpace=1;	
	_pas1=0xF0;									//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11101100;							//TXEN0/RXEN0/BRGH0/WAKE0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1
	pGLED=0; pGLEDc=0;							//規劃pGLED為輸出模式並輸出0
	_mf5e=1; _ur0e=1;							//致能UART0中斷
	_fhiden=0; _fsiden=0;						//HALT時高頻、低頻均停止震盪(SLEEP)
	_psc1r=0x03; _tb1c=0x84; _tb1e=1;			//設置TB1約每0.125秒中斷一次
	_emi=1;										//致能EMI
	while(1)
	{	if(fgRX)								//UART是否接收到資料?
		{	tmp=_txr_rxr0;						//是，取得鍵值
			ForeColor=Yellow;
			eDisplayRet(4,124,60,14,BackColor);	//清除Wait for Data..字串
			eDisplayChar(60,60,tmp);			//顯示
			eDisplayRet(92,36,60,14,BackColor);	//清除RxCount顯示數值
			eDisplay5Digit(92,90,(u16)RxCount,0);
			_txr_rxr0=RxCount++;				//回傳已接收字元數
			fgRX=0;								//清除接收旗標
			Delayms(1000); 						//顯示0.5秒清除顯示值
		}
		else if(fgSleep)						//是否已5秒未收到資料？
		{	ForeColor=Yellow;
			eDisplayStr(4,60,(u8*)"Enter SLEEP...");
			pGLED=0;							//是,熄滅GLED
			GCC_HALT();							//進入Power-Down Mode
			fgSleep=0;							//喚醒時清除旗標
		}
		else 
		{	eDisplayStr(4,60,(u8*)"Wait for Data..");
			ForeColor=~ForeColor;
			Delayms(50);  						//延遲 50ms
		}
	}
}
DEFINE_ISR(UART0,0x3C)
{	if(_rxif0)									//TXR_RXR0是否有資料?
	{	if(_ferr0)								//是,是否發生Framing Error?
		{	_u0sr=_txr_rxr0;					//是,RX Pin負緣喚醒,清除旗標
		}
		else fgRX=1;							//無Framing Error,資料正確接收
	}	
	Count=0;									//清除5秒計數器
	_ur0f=0;									//清除UR0F旗標(共享型)	
}
DEFINE_ISR(TB1,0x28)
{	if(++Count>=40) fgSleep=1;					//若大於5秒設置旗標
	else pGLED=!pGLED;							//改變pGLED之狀態
}