// PROGRAM	: U2_2_2.c							2017.0424
// FUNCTION	: WDT with RES Pin Reset 			By Steven
#include <HT66F2390.h>
#include "MyType.h"
#define SEGPort  	_pg
#define SEGPortC 	_pgc
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void Delayms(u16 del);
void main()
{	u8 i;	
	_wdtc=0b01010110;							//致能看們狗計時器,Time-out=2^17/fLIRC
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性並輸出0
	_rstc=0xAA;									//致能RES腳位重置功能
	if(_to)										//是否為WDT Time-out重置
	{	for(i=0;i<10;i++)						//是,閃爍a～g節段
		{	SEGPort^=0xFF;
			Delayms(100);						//延遲0.1S
		}
	}
	for(i=0;i<10;i++)
	{	SEGPort=SEG_TAB[i]; Delayms(250);		//顯示i值並延遲0.25S
	} 
	SEGPort=0;									//熄滅七段顯示器
	while(1);									//無窮迴圈(模擬MCU當機)
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
	GCC_CLRWDT();								//清除WDT
}