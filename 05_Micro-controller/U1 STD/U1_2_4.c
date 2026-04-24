// PROGRAM	: U1_2_4.c								2017.0414
// FUNCTION	: 7 SEGMENT LED Demo Program			By Steven
#include "HT66F2390.h"
#include "MyType.h"
#define SEGPort		_pg
#define SEGPortC	_pgc
void Delay10ms(u8);
const u16 SEG_TAB[] = {		      					//7-Segment Table
			(20<<8)+0x3F,(30<<8)+0x06,(40<<8)+0x5B,	//High-Byte:延遲常數
			(50<<8)+0x4F,(60<<8)+0x66,(70<<8)+0x6D,	//Low-Byte:七段顯示碼
			(80<<8)+0x7D,(90<<8)+0x07,(100<<8)+0x7F,
			(110<<8)+0x67};
void main()
{
	u8 i;	
	_wdtc=0xAB;										//關閉看們狗計時器
	SEGPortC=0;										//Config Port as O/P Mode
	while(1)

	{	
	
		for(i=9;(s8)i>=0;i--)
		{	SEGPort=(u8)SEG_TAB[i];			   		//取得Low-byte並送至七段顯示器
			Delay10ms(SEG_TAB[i]>>8);				//延遲函式
		}
		
		
	}
}
void Delay10ms(u8 del)
{	u8 i;											//@fSYS=8MH,延遲del*10ms
	for(i=0;i<del;i++) GCC_DELAY(20000);
}