// PROGRAM	: U3_3_2.c								2017.0427
// FUNCTION	: ADC(VBG) with Multi 7-SEGMENT Display	By Steven
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
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性
	ScanPort&=0xF0; ScanPortC&=0xF0;			//規劃ScanPort[3:0]為輸出屬性
	_psc0r=0x01; _tb0c=0x85;_tb0e=1;			//fPSC0=fSYS/4,週期=8192*(1/fTB0),致能TB0中斷
	_sadc0=0b00111000;							//ADEN=ADRFS=1, SAC[3:0]=1000(選擇AN8)
	_sadc1=0x07;								//SAINS[3:0]=0000(選擇ANn),SACKS[2:0]=7(fSYS/128)
	_vbgrc=0x01;								//Enable VBG
	_sadc2=0b10011011;							//致能PGA, 並選擇輸入為VBGREF
												//SAVR[1:0]=10(vREF=PGA輸出),PGAS[1:0]=11(3.33)
	_pds0=0x03;									//設置PD0功能為AN8
	_ade=1;										//致能A/D中斷
	ptr=Buffer; ScanCode=0b00000001;		    //指標初值設定
	for(i=0;i<4;i++) Buffer[i]=0;				//顯示初值設定
	_emi=1;										//致能EMI
	_start=1; _start=0;							//啟動A/D轉換
	while(1);									//無窮迴圈 (程式idle ADC 中斷時會先去執行該位置)
}
DEFINE_ISR(ISR_ADC,0x1c)
{	u16 adr;
	adr=((u16)_sadoh<<8)|_sadol;				//取得12-bit的轉換結果
	adr=((u32)adr*4000)>>12;					//換算為電壓(放大1000倍), 4v = 4000mv
	Buffer[3]=adr/1000; adr%=1000;				//取得千位數
	Buffer[2]=adr/100; 	adr%=100;				//取得百位數	
	Buffer[1]=adr/10;   adr%=10;				//取得時位數
	Buffer[0]=adr;								//取得個位數
	_start=1; _start=0;							//啟動A/D轉換, 再次啟動中斷
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