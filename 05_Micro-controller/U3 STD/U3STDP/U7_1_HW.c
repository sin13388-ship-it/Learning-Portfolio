/* PROGRAM	: U7_1.c							2026.0604
*  Ref. Program : U3_3_1_Homework.c
*  FUNCTION	: UART Data Transmit Demo Program 	Modified By Vera
*  使用F2390控制HC-05, 發送類比電壓給手機APP
*  同步顯示在7段顯示器上
*  Baud rate =19200

*/



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
// 7-segments port control====
#define	 SEGPort	_pg
#define  SEGPortC	_pgc
#define	 ScanPort	_pe
#define	 ScanPortC	_pec
const u8 SEG_TAB[] = {			   				//七段顯示碼建表區(共陰)
				0x3F,0x06,0x5B,0x4F,0x66,
			   	0x6D,0x7D,0x07,0x7F,0x67};
volatile u8 *ptr,ScanCode,Buffer[4];
//=============================

void Delayms(u16);
void main()
{	
	u8 i; u16 adr;
	
	_wdtc=0b10101111;							//關閉看門狗計時器
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
	
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性
	ScanPort&=0xF0; ScanPortC&=0xF0;			//規劃ScanPort[3:0]為輸出屬性
	_psc0r=0x01; _tb0c=0x85;_tb0e=1;			//fPSC0=fSYS/4,週期=8192*(1/fPSC0),致能TB0中斷
	
	ptr=Buffer; ScanCode=0b00000001;		    //指標初值設定
	for(i=0;i<4;i++) Buffer[i]=0;				//顯示初值設定
	_emi=1;										//致能EMI 
	
	
	while(1)
	{	_start=1; _start=0;						//啟動A/D轉換
		while(_adbz);							//等待A/D轉換完成
		_txr_rxr0=_sadol;						//傳送結果低八位元
		while(!_txif0);							//Check if shift is done
		_txr_rxr0=_sadoh;						//傳送結果高四位元
		
		adr=((u16)_sadoh<<8)|_sadol;			//取得12-bit的轉換結果, 要先擴展再轉, 強制型別轉換
		adr =((u32)adr * 5000) >>12;			//轉換電壓, 2 的整數除法可以用左移右移		
		Buffer[3]=adr/1000; adr%=1000;			//取得千位數
		Buffer[2]=adr/100; 	adr%=100;			//取得百位數	
		Buffer[1]=adr/10;   adr%=10;			//取得時位數
		Buffer[0]=adr;							//取得個位數

		Delayms(300); 							//延遲300mS
		pBLED=!pBLED;							//pBLED反態
	}

	
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);			//Delay 1ms @ 8MHz
}

DEFINE_ISR(ISR_TB0,0x24)
{	SEGPort=0;									//關閉七段
	ScanPort=ScanCode;							//送出掃描碼
	SEGPort=SEG_TAB[*ptr++];					//送出節段碼		
	GCC_RL(ScanCode);							//更新掃描碼
	if(ScanCode==0b00010000)					//若已掃完四顆七段	
	{		
		ScanCode=0b00000001; ptr=Buffer;	    //重新初始指標與掃描碼	
		SEGPort |=0x80;							//如果是第3顆，點亮小數點
	}	
}