// PROGRAM	: U4EXT_01.c							2019.0910
// FUNCTION	: GENERATE TONE By USING DELAY SKILL	By Steven
// NOTE: Using PD6 to Toggle Buzzer
#include "HT66F2390.h"
#include "MyType.h"
#define	pSPK	_pd6
#define	pSPKC	_pdc6
#define 	KeyPort		_pc			
#define 	KeyPortC	_pcc
#define 	KeyPortPU	_pcpu							
#define M1  1000000								   	//1000000
const u8 TAB_Pitch[] = {		   					//Pitch Constant
			M1/(523*10),M1/(587*10),
			M1/(659*10),M1/(698*10),
			M1/(785*10),M1/(880*10),
			M1/(988*10),
			M1/(523*2*10),M1/(587*2*10),
			M1/(659*2*10),M1/(698*2*10),
			M1/(785*2*10),M1/(880*2*10),
			M1/(988*2*10),M1/(523*2*2*10),
			M1/(587*2*2*10),
			};

const u16 TAB_Duration[] = { 	      				//Duration Constant
			523>>2,587>>2,
			659>>2,698>>2,
			785>>2,880>>2,
			988>>2,
			523/2,587/2,
			659/2,698/2,
			785/2,880/2,
			988/2,(523*2)/2,
			(587*2)/2
			};
void PAUSE(u8); v
u8 ScanKey();
void main()
{	u8 i;
	u16 j;
	_wdtc=0b10101111;								//關閉看們狗計時器
	pSPKC=0;										//Config pSPK Pin as Output
	while(1)
	{	
			i=ScanKey();	
			for(j=0;j<TAB_Duration[i];j++)
			{	pSPK=!pSPK;				   			//Toggle pSPK State
				PAUSE(TAB_Pitch[i]);
			}		
	}	
}
void PAUSE(u8 i)
{	u8 j;
    for(j=0;j<i;j++) GCC_DELAY(20);			      	//Delay i*10uS
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					         	//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)								//依序檢查四列
	{	if(!(KeyPort & 1<<4)) break;		      	//檢查第0行(KeyPort[4])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;			   	//檢查第1行(KeyPort[5])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;			   	//檢查第2行(KeyPort[6])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<7)) break;			   	//檢查第3行(KeyPort[7])是否按下
		key++;										//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;	   		//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}