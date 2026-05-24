// PROGRAM	: U3_4_1.c						2017.0427
// FUNCTION	: CP1 Control Demo Program    	By Steven
#include <HT66F2390.h>
#include "MyType.h"			
#define LEDPort		_pf
#define LEDPortC	_pfc
void main()
{	_wdtc=0b10101111;						//關閉看們狗計時器
	LEDPort=0xFF; LEDPortC=0;				//規劃LEDPort為輸出屬性並輸出FF
	_pds1=0x3F;								//PD6=>C1x, PD5=>C1+,PD4=>C1-
	_cp1c=0b01000000;						//致能CP1,C1POL=0
	_cp1e=1; _emi=1;						//致能CP1中斷與中斷總開關
	while(1);								//無窮迴圈
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