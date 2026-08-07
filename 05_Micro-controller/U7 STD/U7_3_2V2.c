// PROGRAM	: U7_3_2V2.c						2022.0812
// FUNCTION	: UART Data RX/TX Demo Program 		By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	 fH		8000000							//MCU HIRC Frequency
#define  BR		19200							//Baud Rate

#if BR>38400 && fH!=11059200
#error Baud Rate Error !!!
#warning "BR Exceed 38400, must use 11.059MHz HXT as fH to Reduce Baud Rate Deviation."
#endif

#define  KeyPort	_pg			
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
#define  pGLED		_pd2			
#define  pGLEDc		_pdc2			

const u16 Pitch_TAB[] = {			      		//音調常數建表區
		fH/(523*2*4),fH/(587*2*4),fH/(659*2*4),
		fH/(698*2*4),fH/(785*2*4),fH/(880*2*4),
		fH/(998*2*4),fH/(523*4*4),fH/(587*4*4),
		fH/(659*4*4),fH/(698*4*4),fH/(785*4*4),
		fH/(880*4*4),fH/(998*4*4),fH/(523*8*4),
		fH/(587*8*4)};
volatile u8 RxData,Count=0;
volatile bit fgRx=0, fgSleep=0;
void Delayms(u16);
u8 ScanKey(void);
void main()
 {	u8 Key;
	_wdtc=0b10101111;							//關閉看門狗計時器
#if BR>38400									//當BR>38400,需啟用外部11.059MHz的HXT
	_pbs1=0xF0; _hxtm=1;						//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);					//致能HXT並等待穩定
#endif											//注意ESK303 OSC1/2 Jumper之設定

	_stm2c0=0; _stm2c1=0b00110001;				//STM2:比對吻合輸出模式,CCRA吻合清除
	_pds1=0x20;									//設定PD6為STP2功能	
	_sledc1=0xC0;								//設置PD[6:4]源流為Level 3	
	_pas1=0xF0;									//設置腳位功能 TX0->PA7,RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11101100;							//TXEN0/RXEN0/BRGH0/WAKE0/RIE0//	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1
	_mf5e=1; _ur0e=1;							//致能UART0中斷
	pGLED=0; pGLEDc=0;							//規劃pGLED為輸出模式並輸出0
	_fhiden=1; _fsiden=0;						//HALT時高頻維持震盪、低頻停止震盪(IDLE2)
	_psc1r=0x03; _tb1c=0x87; _tb1e=1;			//設置TB1每一秒中斷一次
	_emi=1;										//致能EMI
	while(1)
	{	if(fgRx)								//UR是否接收到資料?
		{	fgRx=0;								//是，清除接收旗標
//			RxData=_txr_rxr0;					//取得接收資料
			RxData-=(RxData<'A')?'0':'7';		//ASCII轉換成數值 		
			_stm2al=Pitch_TAB[RxData];			//取得計數時間常數
			_stm2ah=Pitch_TAB[RxData]>>8;          
			Count=0;							//清除Count
			_st2on=1; Delayms(250); _st2on=0;	//啟動STM2計數250ms後關閉
		}
		Key=ScanKey();							//讀取4x4 Keypad
		if(Key!=16) 							//是否按壓鍵盤?
		{	Key+=(Key<10)? '0' : 'A'-10;		//是，轉換成ASCII
			_txr_rxr0=Key;						//透過藍芽傳送
			Count=0; 							//清除Count
			pGLED=1; Delayms(250); pGLED=0;		//點亮GLED 250ms
		}
		if(fgSleep)
		{	pGLED=1;							//點亮GLED	
			GCC_HALT();							//進入Power-Down Mode
			fgSleep=0;							//清除旗標
			Count=0;							//清除Count
			pGLED=0;							//熄滅GLED
		}
	}
}
DEFINE_ISR(UART0,0x3C)
{	RxData=_txr_rxr0;							//取得接收資料
	fgRx=1;										//設置接收旗標
	_ur0f=0;									//清除UR0F旗標(共享型)	
}
DEFINE_ISR(TB1,0x28)
{	if(++Count>=5) fgSleep=1;					//若大於5秒設置旗標
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
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);			//Delay 1ms @ 8MHz
}