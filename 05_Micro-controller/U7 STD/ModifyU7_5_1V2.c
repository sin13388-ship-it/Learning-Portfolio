// PROGRAM	: ModifyU7_5_1V2.c							2022.0102
// FUNCTION	: UART Address Detect (Master)				By Steven
// NOTE		: RGB-G Flash : wait key Pressed
// 			  use e-Display to Deisplay Received Data Count
// LIBRARY	: eDisplayV2.c  
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplay.H"
#define	 fH		8000000									//MCU HIRC Frequency
#define  BR		19200									//Baud Rate
#define  KeyPort	_pg			
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define  pGLED		_pd2			
#define  pGLEDc		_pdc2

#define  SLAVE1		0x85
#define  SLAVE2		0x88		
u8 ScanKey(void);
void main()
 {	volatile u8 Key;
	_wdtc=0b10101111;									//關閉看門狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	feDisplay5DigitNoSpace=1;
	eDisplayStr(32, 5,(u8*)"U7_5_1V2");
	eDisplayStr(20,25,(u8*)"UART Master");
	ForeColor=Green;
	eDisplayStr( 4,70,(u8*)"Slave1");
	eDisplayStr( 4,88,(u8*)"TX Cnt");
	ForeColor=White;
	eDisplayStr(76,70,(u8*)"Slave2");
	eDisplayStr(76,88,(u8*)"TX Cnt");
	pGLED=0; pGLEDc=0;									//規劃pGLED為輸出模式並輸出0
	_pas1=0xF0;											//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;									//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11100100;									//TXEN0/RXEN0/BRGH0/WAKE0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;							//BRGH0=1
	_psc1r=0x03; _tb1c=0x84; _tb1e=1;					//設置TB1約每0.125秒中斷一次	
	_emi=1;												//致能EMI
	ForeColor=Yellow;
	while(1)
	{	do											 	//等待按壓4x4 Keypad
		{ 	Key=ScanKey();
			Delayms(90); 	 							//延遲90ms
			eDisplayStr(4,45,(u8*)"Press Keypad...");
			ForeColor=~ForeColor;
		} while(Key==16||(ForeColor!=Yellow));			//未按壓按鍵或前景非黃色
		eDisplayRet(4,124,45,14,BackColor);				//清除Press Keypad...字串
		if(Key&1) _txr_rxr0=SLAVE1;						//若為奇數鍵,送出Slave1位址
		else _txr_rxr0=SLAVE2;							//若為偶數鍵,送出Slave2位址
		eDisplayChar(60,45,(Key<10)?Key+'0':Key+'7');	//顯示轉ASCII之按鍵值			
		while(!_txif0);									//等待位址移至TSR
		_txr_rxr0=Key;									//鍵值傳送至Slave端
	   	Delayms(500);			   						//Delay 800ms(需搭配Slave避免其來不及接收！)
		if(_rxif0)										//Slave是否回傳
		{	if(Key&1) 
			{	eDisplayRet( 8,40,106,14,BackColor);
				eDisplay5Digit( 8,106,(u16)_txr_rxr0,0);
			}
			else
			{	eDisplayRet(80,40,106,14,BackColor);
				eDisplay5Digit(80,106,(u16)_txr_rxr0,0);
			}
		}
		else
		{	if(Key&1) eDisplayRet( 8,40,106,14,Red);
			else      eDisplayRet(80,40,106,14,Red);
		}
	}
}
DEFINE_ISR(TB1,0x28)
{	pGLED=!pGLED;
}
u8 ScanKey(void)
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;						//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					 				//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)									//依序檢查四列
	{	if(!(KeyPort & 1<<7)) break;					//檢查第0行(KeyPort[4])是否按下
		key++;											//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;					//檢查第1行(KeyPort[5])是否按下
		key++;											//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;					//檢查第2行(KeyPort[6])是否按下
		key++;											//否，按鍵值+1
		if(!(KeyPort & 1<<4)) break;					//檢查第3行(KeyPort[7])是否按下
		key++;											//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;				//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}
