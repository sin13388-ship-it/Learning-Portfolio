// PROGRAM	: U3_1.c							2017.0425
// FUNCTION	: Multi 7-SEGMENT Control with TB 	By Steven
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
{	u8 i,j=0;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性
	ScanPort&=0xF0; ScanPortC&=0xF0;			//規劃ScanPort[3:0]為輸出屬性
	_psc0r=0x01; _tb0c=0x85;_tb0e=1;			//fPSC0=fSYS/4,週期=8192*(1/fPSC0),致能TB0中斷
	_psc1r=0x02; _tb1c=0x87;					//fPSC1=fSUB,週期=32768*(1/fPSC1)
	ptr=Buffer; ScanCode=0b00000001;		    //指標初值設定
	for(i=0;i<4;i++) Buffer[i]=0;				//顯示初值設定
	_emi=1;										//致能EMI
	while(1)									//無窮迴圈
	{	for(i=3;i!=0;i--) Buffer[i]=Buffer[i-1];//Buffer[]傳遞
		Buffer[0]=j++;							//更新Buffer[0]
		if(j>9) j=0;							//若j超過9則歸零	
		while(!_tb1f);							//等待TB1數到設定的時間
		_tb1f=0;								//清除TB1旗標
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	SEGPort=0;									//關閉七段
	ScanPort=ScanCode;							//送出掃描碼								
	SEGPort=SEG_TAB[*ptr++];					//送出節段碼
	GCC_RL(ScanCode);							//更新掃描碼
	if(ScanCode==0b00010000)					//若已掃完四顆七段
	{	ScanCode=0b00000001; ptr=Buffer;	    //重新初始指標與掃描碼	
	}
}