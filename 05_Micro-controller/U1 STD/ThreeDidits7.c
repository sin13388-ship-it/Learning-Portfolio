// PROGRAM	: ThreeDigits.c							2026.0424
// FUNCTION	: 7 SEGMENT LED Demo Program			Modified By Vera

//include 需要的庫
#include "HT66F2390.h"
#include "MyType.h"

//define _pg, _pgc 
#define SEGPort		_pg
#define SEGPortC	_pgc

//Delaytime
void delay10ms(u8);

//Display pattern with delaytime
//const 讓compiler 使用程式記憶體
const u16 SEG_PATTERN[]={
			(20<<8)+0x3F,(30<<8)+0x06,(40<<8)+0x5B,	//High-Byte:延遲常數
			(50<<8)+0x4F,(60<<8)+0x66,(70<<8)+0x6D,	//Low-Byte:七段顯示碼
			(80<<8)+0x7D,(90<<8)+0x07,(100<<8)+0x7F,
			(110<<8)+0x67};
			
int main(){	
	u8 i;
	_wdtc=0xAB;										//Disable watch dog timer
	//set SEGPort IO : Input
	SEGPortC=0;
	while(1)
	{
		for(i=9; (s8) i>=0; i--){
		
			SEGPort=(u8)SEG_PATTERN[i]; //get LSB
			delay10ms(SEG_PATTERN[i]>>8);		
		}		
	}
}

void delay10ms(u8 delayCount)
{
	u8 i;
	for(i=0; i<delayCount; i++)
		GCC_DELAY(20000); //20000 clks =10ms	
}