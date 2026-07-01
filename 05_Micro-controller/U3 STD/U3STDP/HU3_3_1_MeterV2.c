// PROGRAM	: HU3_3_1MeterV2.c					2025.0625
// FUNCTION	: Multi 7-SEGMENT LED Simple Meter	By Steven
// NOTE		: 取得固定輸入源(VBG*2.5)為ADC輸入,做為量測時之校正
//            先執行HU3_3_1Meter.c,調整VR使顯示電壓為2.500V左右
//			  執行本程式時先不調VR,觀察5V切換3.3V時的電壓顯示變化！	
#include <HT66F2390.h>
#include "MyType.h"
#define	 SEGPort	_pg
#define  SEGPortC	_pgc
#define	 ScanPort	_pe
#define	 ScanPortC	_pec
const u8 SEG_TAB[] = {			   				//七段顯示碼建表區(共陰)
				0x3F,0x06,0x5B,0x4F,0x66,
			   	0x6D,0x7D,0x07,0x7F,0x67};
volatile u8 *ptr,ScanCode,Buffer[4];
const u16 VR=3000;								//Babgap Voltage 1.20V(VBGREF with PGA gain=2.5)
const u16 AVDD=5000;							//VREF 5.00V ***
volatile u16 Volt;
void main()
{	u8 i; u16 adr,ADRVBG;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性
	ScanPort&=0xF0; ScanPortC&=0xF0;			//規劃ScanPort[3:0]為輸出屬性
	_psc0r=0x01; _tb0c=0x85;_tb0e=1;			//fPSC0=fSYS/4,週期=8192*(1/fPSC0),致能TB0中斷
	_vbgren=1; GCC_DELAY(1000);					//致能VBG輸出(VBGS:200us Stable Time)	
	_sadc0=0b00111000;							//ADEN=ADRFS=1, SAC[3:0]=1000(選擇AN8)

	_sadc2=0b10010010;							//Enable PGA, VBGREF as PGA I/P,VREF=AVDD, Gain=2.5
	_pds0=0x03;									//設置PD0功能為AN8
	ptr=Buffer; ScanCode=0b00000001;		    //指標初值設定
	for(i=0;i<4;i++) Buffer[i]=0;				//顯示初值設定
	_emi=1;										//致能EMI
	while(1)
	{	_sadc1=0x57;							//選擇內部PGA輸出(VR)為轉換源,fSYS/128				
		_start=1; _start=0;						//啟動A/D轉換
		while(_adbz);							//等待轉換完成
		ADRVBG=((u16)_sadoh<<8)+_sadol;			//取得VBG轉換結果
/*
		_sadc1=0x07;							//選擇AN8為轉換源,fSYS/64
		_start=1; _start=0;						//啟動AD轉換
		while(_adbz);							//Wait Conversion Complete
		adr=((u16)_sadoh<<8)+_sadol;
		Volt=((u32)adr*AVDD)>>12;				//Volt=(Result*AVDD)/4096(未經校正電壓)
		adr=((u32)adr*VR)/ADRVBG;				//Volt=(VBG*ADR2)/ADR1   (經過校正電壓)
*/
		_sadc1=0x07;							//選擇AN8為轉換源,fSYS/64
		_start=1; _start=0;						//啟動AD轉換
		for(i=0,adr=0;i<16;i++)
		{	while(_adbz);						//Wait Conversion Complete
			adr+=(((u16)_sadoh<<8)+_sadol);
			_start=1; _start=0;					//啟動AD轉換
		}
		Volt=((u32)adr*AVDD)>>16;				//Volt=(Result*AVDD)/4096(未經校正電壓)
		adr=((u32)adr*VR)/(ADRVBG<<4);			//Volt=(VBG*ADR2)/ADR1   (經過校正電壓)

		Buffer[3]=adr/1000; adr%=1000;			//取得千位數
		Buffer[2]=adr/100; 	adr%=100;			//取得百位數	
		Buffer[1]=adr/10;   adr%=10;			//取得時位數
		Buffer[0]=adr;							//取得個位數
		GCC_DELAY(263690);
	}									
}
DEFINE_ISR(ISR_TB0,0x24)
{	SEGPort=0;									//關閉七段
	ScanPort=ScanCode;							//送出掃描碼								
	if(ScanCode!=1<<3) SEGPort=SEG_TAB[*ptr++];	//送出節段碼
	else SEGPort=SEG_TAB[*ptr++]|(1<<7);		//送出節段碼並點亮小數點
	GCC_RL(ScanCode);							//更新掃描碼
	if(ScanCode==0b00010000)					//若已掃完四顆七段
	{	ScanCode=0b00000001; ptr=Buffer;	    //重新初始指標與掃描碼	
	}
}