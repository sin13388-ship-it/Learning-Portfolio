// PROGRAM	: U3_4_2.c						2017.0427
// FUNCTION	: CP1 Control with Calibration	By Steven
#include <HT66F2390.h>
#include "MyType.h"			
#define LEDPort		_pf
#define LEDPortC	_pfc
void CP1Calibration(void);
void main()
{	_wdtc=0b10101111;						//關閉看們狗計時器
	LEDPort=0xFF; LEDPortC=0;				//規劃LEDPort為輸出屬性並輸出FF
	_pds1=0x3F;								//PD6=>C1x, PD5=>C1+,PD4=>C1-
	_cp1c=0b01000000;						//致能CP1,C1POL=0, 響應時間最慢
	CP1Calibration();						//進行CP1輸入偏移電壓校正程序
	_cp1e=1; _emi=1;						//致能CP1中斷與中斷總開關
	while(1);								//無窮迴圈
}
void CP1Calibration(void)
{	volatile u8 i,cout,VCOS1,VCOS2;
	_cp1vos=0b01000000;						//C10FM=1(校正模式),C1RSP=0(C1-為參考輸入)
	GCC_DELAY(90); cout=_c1out;				//等待比較器輸出穩定, 取得C1OUT
	for(i=0;i<31;i++)
	{	_cp1vos++; GCC_DELAY(90);			//C1OF[4:0]+1, 等待比較器輸出穩定
		if(cout!=_c1out) break;				//若C1OUT改變,結束迴圈	
	}
	VCOS1=_cp1vos & 0x1F;					//VCOS1=C1OF[4:0]
	_cp1vos=0b01011111;						//C1OF[4:0]=11111b
	GCC_DELAY(90); cout=_c1out;				//等待比較器輸出穩定, 取得C1OUT
	for(i=0;i<31;i++)
	{	_cp1vos--; GCC_DELAY(90);			//C1OF[4:0]-1, 等待比較器輸出穩定
		if(cout!=_c1out) break;				//若C1OUT改變,結束迴圈
	}
	VCOS2=(_cp1vos & 0x1F);					//VCOS2=C1OF[4:0]
	_cp1vos=(VCOS1+VCOS2)>>1; 				//C1OF[4:0]=(VCOS1+VCOS2)/2,C10FM=0
}
DEFINE_ISR(ISR_CP1,0x10)					//CP1 Interrupt Vector
{	u8 i;	
	if(_c1out)								//C1+ > C1- ?
	{	for(i=0;i<8;i++) 					//無反射信號LEDs逐一熄滅
		{	LEDPort>>=1; LEDPort|=(1<<7);	//右移一次並設置MSB=1 
			GCC_DELAY(160000);				//延遲80ms
		}
 	}
	else									//C1+ < C1-
	{ 	for(i=0;i<8;i++) 					//有反射信號LEDs逐一點亮					
		{	LEDPort<<=1; 					//左移一次
			GCC_DELAY(160000);				//延遲80ms
		}
	}
}