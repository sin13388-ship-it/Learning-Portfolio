// PROGRAM	: U7_1.c							2020.0526
// FUNCTION	: UART Data Transmit Demo Program 	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	fH		8000000							//MCU HIRC Frequency
#define BR		19200							//Baud Rate(Must Match with HC-05)

#if BR>38400 && fH!=11059200
#error Baud Rate Error !!!
#warning "BR Exceed 38400, must use 11.059MHz HXT as fH to Reduce Baud Rate Deviation."
#endif

#define	pBLED	_pd4
#define	pBLEDC	_pdc4
void Delayms(u16);
void main()
{	_wdtc=0b10101111;							//關閉看門狗計時器
#if BR>38400									//當BR>38400,需啟用外部11.059MHz的HXT
	_pbs1=0xF0; _hxtm=1;						//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);					//致能HXT並等待穩定
#endif											//注意ESK303 OSC1/2 Jumper之設定
	_pas1=0b11000000;							//設置TX0->PA7
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b10100000;							//TXEN0///BRGH0////	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1

	_sadc0=0b00111000;							//ADEN=ADRFS=1, SAC[3:0]=1000(選擇AN8)
	_sadc1=0x07;								//SAINS[3:0]=0000(選擇ANn),SACKS[2:0]=7(fSYS/128)
	_sadc2=0b0000000;							//禁能PGA, 並參考電壓為AVDD
	_pds0=0x03;									//設置PD0功能為AN8
	pBLED=1; pBLEDC=0;							//規劃pBLED為輸出屬性並輸出1
	while(1)
	{	_start=1; _start=0;						//啟動A/D轉換
		while(_adbz);							//等待A/D轉換完成
		_txr_rxr0=_sadol;						//傳送結果低八位元
		while(!_txif0);	
		_txr_rxr0=_sadoh;						//傳送結果高四位元
		Delayms(300); 							//延遲300mS
		pBLED=!pBLED;							//pBLED反態
	}
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);			//Delay 1ms @ 8MHz
}