// PROGRAM 	:U2_3_1.c							2020.0402
// FUNCTION : SLEEP Mode Demo Program			By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort		_pg							//DEFINE 7-SEG PORT
#define	SEGPortC	_pgc						//DEFINE 7-SEG PORT CONTROL REG.
#define SW0  		_pa1
#define SW0C  		_pac1
#define SW0PU  		_papu1
#define SW0WU  		_pawu1
#define SW1PU  		_papu7
const u8 SEG_TAB[] = {			   				//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void Delayms(u16);
void main()
{	static u8 Index; 							//Index必須為static型態,否則初值會清除為0
	u8 SleepCount;
	_wdtc=0b10101111;							//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性並輸出0
	SW0C=1; SW0PU=1; SW0WU=1;		   			//致能：輸入屬性/提升電阻/喚醒功能
	SW1PU=1; _int1ps=1;							//致能提升電阻，指定INT1功能於PA7腳位實現
	_integ=0b00001000;							//選擇INT1為負緣觸發
	_fhiden=0; _fsiden=0;						//HALT指令執行後，關閉高/低頻震盪電路
	Delayms(300); _rstc=0xAA;					//致能RES腳位重置功能
	if(_pdf) GCC_CLRWDT(); else	Index=0;	   	//若為喚醒，清除PDF旗標，否則INDEX歸零
	while(1)
	{	SEGPort=SEG_TAB[Index];					//顯示INDEX值 
		Delayms(200); 							//延遲 0.2 Sec
		SleepCount=50;
		do
		{	Delayms(100); 						//延遲 0.1 Sec
			if(--SleepCount==0)					//0.1 Sec*50=5 Sec 
			{	SEGPort=0;						//熄滅七段顯示器
				_int1f=0;						//清除INT1旗標
				_emi=1; _int1e=1;				//致能：中斷總開關/INT1中斷
				_halt();						//進入SLEEP Mode
				GCC_CLRWDT(); 					//清除PDF旗標(若註解此行,注意用INT喚醒後在未進入SLEEP第一次按RESET的狀況)
				_emi=0; _int1e=0;				//禁能：中斷總開關/INT1中斷	
				break;							//跳離do...while迴圈
			}
		} while(SW0);							//SW0未按，重複do...while迴圈
		if(++Index==10) Index=0; 				//若Index>10則歸零
	}
}
DEFINE_ISR(ISR_Int1,0x08)						//INT1 Interrupt Vector
{	u8 i;
	SEGPort=1<<7;								//點亮h節段
	do
	{	GCC_RL(SEGPort);	 					//左旋，點亮下一節段
		for(i=0;i<50;i++) GCC_DELAY(20000);  	//延遲 0.5S
	} while(SEGPort!=(1<<6));
	_int1f=0;									//避免彈跳造成誤動作
	GCC_CLRWDT(); 								//清除PDF旗標(若註解此行,注意用INT喚醒後在未進入SLEEP第一次按RESET的狀況)
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}