// PROGRAM	: U1_4.c							2026.0430
// FUNCTION	: Fast Mode fSYS Switching 			Modified by vera
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort		_pg 						//DEFINE 7-SEG PORT
#define	SEGPortC	_pgc 						//DEFINE 7-SEG PORT CONTROL REG
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void Display029(void);
void PAUSE(u8);
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;						//清除Port並規劃為輸出屬性
	while(1)
	{ 	for(i=0;i<5;i++)
		{	_scc&=0b00011111;					//scc[7:5]=000,其餘位元維持不變
			_scc|=(i<<5);						//CKS[2:0]=i,其餘位元維持不變 (000 ~ 100)
			Display029();						//顯示0～9	
		}
	}	
}
void Display029(void)
{	u8 i;
		for(i=0;i<10;i++)
		{	SEGPort=SEG_TAB[i]; 				//查表並顯示
			PAUSE(10);							//延遲200000個指令周期
		}	
}
void PAUSE(u8 i)					      
{	u8 j;	
	for (j=0;j<i;j++){
		switch(_scc >> 5){
		
		case 0:
			GCC_DELAY(20000);	
			break;
		case 1:
			GCC_DELAY(10000);	
			break;
		case 2:
			GCC_DELAY(5000);	
			break;
		case 3:
			GCC_DELAY(2500);	
			break;			
		case 4:
			GCC_DELAY(1250);	
			break;
		default:
			GCC_DELAY(20000);	
			break;		
		}		
		
	} 	
}