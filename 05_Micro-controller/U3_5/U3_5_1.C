// PROGRAM	: U3_5_1.c							2017.0502
// FUNCTION	: Software Multipiler Test Program	By Steven
#include <HT66F70A.h>
#include "MyType.h"
DEFINE_SFR(volatile u32, product[32], 0x280);	//Bank 2:80h~FFh, 指定從0x280這個位置開始放
void main()
{	u8 index;
	u16 i=256,j=256;
	_wdtc=0b10101011;					//關閉看們狗計時器
	for(index=0;index<32;index++)
	{ product[index]=(u32)i*j;
		i+=100;j+=500;
	}
	GCC_NOP();							//設置斷點以觀測耗費周期數			
}