// PROGRAM	: U1EXT_01.c							2026.0430
// FUNCTION	: 7 SEGMENT WITH SPEED CONTROL         	Modified by vera
#include <HT66F2390.h>
#include "MyType.h"
#define		SEG_Port	_pg
#define		SEG_PortC	_pgc
#define		DIP_Port	_pe
#define		DIP_PortC	_pec
#define		DIP_PortPU	_pepu
const u8 SEG_TAB[] = {	0x3F,0x06,0x5B,0x4F,0x66,	//7-Segment Table
			         	0x6D,0x7D,0x07,0x7F,0x67};
void main()
{	u8 i,j,k;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEG_PortC=0x0;									//Config Port as O/P Mode
	DIP_PortC|=0b00001111;					      	//Config Port[4..0] as I/P
	DIP_PortPU|=0b00001111;				         	//Enable Port[4..0] Pull-up
	while(1)
	{	for (j=0;j<=9;j++)	
		{			 
			SEG_Port=SEG_TAB[j]; //Read Table							
			while(DIP_Port & 0b00000001);			
			k=(DIP_Port & 0b00001111)*5; 			//Mask unnecessary pin			
			for(i=0;i<k;i++) GCC_DELAY(20000);		//Delay k*10 mSec			

		}
	}
}	l;