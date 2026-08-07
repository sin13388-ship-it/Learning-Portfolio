// PROGRAM	: ModifyU7_5_2V2.c						2022.0103
// FUNCTION	: UART Address Detect (SLAVE1)			By Steven
// NOTE		: RGB-G Flash : wait data Received
// 			  use e-Display to Deisplay Received Data
//			: Set PE0 State to Select Slave Address
// LIBRARY	: eDisplay.c  
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplay.H"
#define	 fH		8000000								//MCU HIRC Frequency
#define  BR		19200								//Baud Rate
#define  pGLED	 _pd2			
#define  pGLEDc	 _pdc2
#define  pADDR	 _pe0			
#define  pADDRC	 _pec0
#define  pADDRPU _pepu0

#define  SLAVE1		0x85
#define  SLAVE2		0x88
volatile bit fgRX=0;
volatile u8 address;
void Delayms(u16);
u8 ScanKey(void);
void main()
 {	u8 RxCount1=1,RxCount2=1,tmp;
 	_wdtc=0b10101111;								//關閉看門狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	feDisplay5DigitNoSpace=1;
	eDisplayStr(32, 5,(u8*)"U7_5_2V2");
	eDisplayStr(12,25,(u8*)"I am Slave- ");
	ForeColor=Green;
	eDisplayStr( 4,70,(u8*)"Slave1");
	eDisplayStr( 4,88,(u8*)"RX Cnt");
	ForeColor=White;
	eDisplayStr(76,70,(u8*)"Slave2");
	eDisplayStr(76,88,(u8*)"RX Cnt");
	ForeColor=Yellow;
	pGLED=0; pGLEDc=0;								//規劃pGLED為輸出模式並輸出0
	pADDRC=1; pADDRPU=1;
	_pas1=0xF0;										//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;								//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11101100;								//TXEN0/RXEN0/BRGH0/WAKE0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;						//BRGH0=1
	_mf5e=1; _ur0e=1;								//致能UART0中斷
	_psc1r=0x03; _tb1c=0x83; _tb1e=1;				//設置TB1約每0.0625秒中斷一次
	_emi=1;											//致能EMI
	while(1)
	{	_adden0=1; fgRX=0;							//啟動UART位址偵測,清除接收旗標
		do
		{	if(pADDR)
			{	address=SLAVE1;	eDisplayChar(102,25,'1');
				eDisplayRet( 2,50,62,3,Green);
				eDisplayRet(74,50,62,3,BackColor);
			}
			else
			{	address=SLAVE2; eDisplayChar(102,25,'2');
				eDisplayRet(74,50,62,3,White);
				eDisplayRet( 2,50,62,3,BackColor);
			}
			ForeColor=~ForeColor; Delayms(70);		//延遲70ms
		} while(!fgRX ||(ForeColor!=Yellow));		//UART未接收到資料或前景非黃色?
		tmp=_txr_rxr0;								//是，取得鍵值
		tmp+=(tmp<10)?'0':'7';						//ASCII轉換
		eDisplayChar(60,45,tmp);					//顯示按鍵值			
		if(address==SLAVE1)
		{	eDisplay5Digit( 8,106,(u16)RxCount1,0);	//顯示Slave1已接收字元數
			_txr_rxr0=RxCount1++;					//回傳Slave1已接收字元數
		}
		else
		{	eDisplay5Digit(80,106,(u16)RxCount2,0);	//顯示Slave2已接收字元數
			_txr_rxr0=RxCount2++;					//回傳Slave2已接收字元數
		}
		Delayms(300); 								//顯示0.3秒清除顯示值
		eDisplayChar(60,45,' ');					//清除按鍵值			
	}
}
DEFINE_ISR(UART0,0x3C)
{	if(_rxif0)										//TXR_RXR0是否有資料?
	{	if(_txr_rxr0==address)						//是否是位址偵測且吻合?
		{	_adden0=0;								//是,停止位址偵測
//			_u0sr=_txr_rxr0; 						//清除旗標	
		}
		else if(_adden0==0) fgRX=1;					//非位址偵測,資料正確接收
	}	
	_u0sr=_txr_rxr0; 								//清除旗標	
	_ur0f=0;										//清除UR0F旗標(共享型)	
}
DEFINE_ISR(TB1,0x28)
{	static u8 cnt=0;
	if((cnt++&7)==0) pGLED=1; 
	else pGLED=0;
}