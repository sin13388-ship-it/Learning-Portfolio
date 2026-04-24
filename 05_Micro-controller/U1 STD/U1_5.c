// PROGRAM	: u1_5.c								2017.0418
// FUNCTION	: 7 SEGMENT LED WITH BUTTON CONTROL    	By Steven
#include <HT66F2390.h>
#include "MyType.h"
#define		SEGPort		_pg
#define		SEGPortC	_pgc
#define		SW0			_pa1						//PA1
#define		SW0C		_pac1						//PAC1
#define		SW0PU		_papu1						//PAPU1
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66, 	//7-Segment Table
			       		0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	u8 i,index=0;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;							//清除Port並規劃為輸出屬性
	SW0C=1; SW0PU=1;                      			//規劃為輸入屬性並致能提升電阻
	while(1)
	{	SEGPort=SEG_TAB[index];						//查表並顯示
		for(i=0;i<5;i++) GCC_DELAY(20000);			//延遲 50ms
	wait:
		while(SW0);						     		//等待按鍵壓下
		for(i=0;i<5;i++) GCC_DELAY(20000);			//延遲 50ms
		if(SW0) goto wait; 		            		//If Key Released, Bouncing
		if(++index>9) index=0;						//指標值+1, 若大於9則歸零
	}
}	