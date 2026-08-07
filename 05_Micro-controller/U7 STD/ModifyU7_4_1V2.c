// PROGRAM	: ModifyU7_4_1V2.c					2022.0101
// FUNCTION	: UART Wake-up control (Master)		By Steven
// NOTE		: RGB-G Flash : wait key Pressed
//					ON	  : Slave enter SLEEP
// 			  use e-Display to Deisplay Received Data Count	
// LIBRARY	: eDisplay.c  
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.H"

#define	 fH		8000000							//MCU HIRC Frequency
#define  BR		19200							//Baud Rate
#define  KeyPort	_pg			
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define  pGLED		_pd2			
#define  pGLEDc		_pdc2
volatile u8 Count=0;
volatile bit fgSleep=0;
u8 ScanKey(void);
void main()
 {	u8 Key;
	_wdtc=0b10101111;							//關閉看門狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	eDisplayStr(32, 5,(u8*)"U6_4_1V2");
	eDisplayStr(20,25,(u8*)"UART Master");
	eDisplayStr(20,90,(u8*)"TRX. Cnt:0");	
	feDisplay5DigitNoSpace=1;
	_pas1=0xF0;									//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11100100;							//TXEN0/RXEN0/BRGH0/WAKE0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1
	pGLED=0; pGLEDc=0;							//規劃pGLED為輸出模式並輸出0
	_psc1r=0x03; _tb1c=0x84; _tb1e=1;			//設置TB1約每0.125秒中斷一次
	_emi=1;										//致能EMI
	while(1)
	{	do	
		{ 	Key=ScanKey();
			Delayms(100);  						//延遲 100ms
			eDisplayStr(4,60,(u8*)"Press Keypad...");
			ForeColor=~ForeColor;
		} while(Key==16);
		ForeColor=Yellow;
		eDisplayRet(4,124,60,14,BackColor);		//清除Press Keypad...字串
		Key+=(Key<10)?'0':'7';					//ASCII轉換
		eDisplayChar(60,60,Key);				//顯示按鍵值			
		if(fgSleep)								//是否Slave已進入睡眠模式?
		{	_txbrk0=1;							//傳送BREAK字元
		   	Delayms(5);			   				//Delay 5ms
			_txbrk0=0;							//停止傳送BREAK字元
			pGLED=0;							//熄滅GLED
			fgSleep=0;							//清除旗標
			Delayms(5);
		}			
		_txr_rxr0=Key;							//鍵值傳送至Slave端
		Count=0;								//清除Count
		while(!_rxif0);							//等待回傳資料
		eDisplayRet(92,36,60,14,BackColor);		//清除RxCount顯示數值
		eDisplay5Digit(92,90,(u16)_txr_rxr0,0);
	   	Delayms(1500);			   				//Delay 500ms
	}
}
DEFINE_ISR(TB1,0x28)
{	if(++Count>=40) 
	{	pGLED=1;								//若大於5秒點亮GLED(Slave已進入睡眠模式)
		fgSleep=1;								//設置旗標	
	}
	else pGLED=!pGLED;
}
u8 ScanKey(void)
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;				//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					 		//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)							//依序檢查四列
	{	if(!(KeyPort & 1<<7)) break;			//檢查第0行(KeyPort[4])是否按下
		key++;									//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;			//檢查第1行(KeyPort[5])是否按下
		key++;									//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;			//檢查第2行(KeyPort[6])是否按下
		key++;									//否，按鍵值+1
		if(!(KeyPort & 1<<4)) break;			//檢查第3行(KeyPort[7])是否按下
		key++;									//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;		//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}