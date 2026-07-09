// PROGRAM	: U4EXT_01.c							2019.0910
// FUNCTION	: GENERATE TONE By USING DELAY SKILL	By Steven
// NOTE: Using PD6 to Toggle Buzzer
#include "HT66F2390.h"
#include "MyType.h"
#define	pSPK	_pd6
#define	pSPKC	_pdc6							
#define M1  1000000								   	//1000000
const u8 TAB_Pitch[] = {		   					//Pitch Constant
			M1/(523*2*10),M1/(587*2*10),
			M1/(659*2*10),M1/(698*2*10),
			M1/(785*2*10),M1/(880*2*10),
			M1/(988*2*10),M1/(523*2*2*10),
			};

const u16 TAB_Duration[] = { 	      				//Duration Constant
			523/2,587/2,659/2,698/2,
			785/2,880/2,988/2,(523*2)/2,
			};
void PAUSE(u8);
void main()
{	u8 i;
	u16 j;
	_wdtc=0b10101111;								//關閉看們狗計時器
	pSPKC=0;										//Config pSPK Pin as Output
	while(1)
	{	for(i=0;i<8;i++)	   		
		{	for(j=0;j<TAB_Duration[i];j++)
			{	pSPK=!pSPK;				   			//Toggle pSPK State
				PAUSE(TAB_Pitch[i]);
			}
		}
		_sledc1^=(3<<6);							//Source Current Control (Level 0/3)
	}	
}
void PAUSE(u8 i)
{	u8 j;
    for(j=0;j<i;j++) GCC_DELAY(20);			      	//Delay i*10uS
}
