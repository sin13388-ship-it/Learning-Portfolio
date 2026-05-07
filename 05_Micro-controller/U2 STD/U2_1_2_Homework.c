// PROGRAM	: U2_1_1.c							2017.0420
// FUNCTION	: External Interrupt Demo Program	By Steven
#include <HT66F2390.h>			
#include "MyType.H"
#define	LEDPort		_pf							//DEFINE LED PORT
#define	LEDPortC	_pfc						//DEFINE LED CONTROL REG.
#define	SEGPort		_pg							//DEFINE 7-SEG PORT
#define	SEGPortC	_pgc						//DEFINE 7-SEG PORT CONTROL REG.			
const u8 SEG_TAB[] = {							//7-Segment Table
			0x3F,0x06,0x5B,0x4F,0x66,
			0x6D,0x7D,0x07,0x7F,0x67};
void Delayms(u16);
void main()
{	u8 i;
	_wdtc=0b10101111;							//關閉看們狗計時器
	LEDPort=0xFF; LEDPortC=0;					//規劃LEDPort為輸出屬性並輸出FFh熄滅LEDs
	SEGPort=0; SEGPortC=0;						//規劃SEGPort為輸出屬性並輸出00h熄滅七段顯示器
	
	_pdpu0=1; _pcpu7=1;						    //致能PD0/PC7 Pull-High電阻
	_int2ps=1;									//指定INT2功能於PD0腳位實現
	_int3ps=1;									//指定INT3功能於PC7腳位實現
	_integ=0b10100000;							//選擇INT3/INT2為負緣觸發型式
	_int2e=1; _int3e=1; _emi=1;					//致能INT2,INT3及中斷總開關
	
	while(1)
	{	for(i=0;i<10;i++)						//顯示迴圈 
		{	SEGPort=SEG_TAB[i];					//查表並送至顯示器顯示	
		 	Delayms(1000);						//延遲1Sec
		}
	}
}
DEFINE_ISR(ISR_Int2,0x30)						//INT2 ISR
{	u8 i,temp;
	temp=LEDPort;								//保留LEDPort目前狀態	
	LEDPort=0b11111110;							//設定LEDPort初值
	for(i=0;i<8;i++)
	{	GCC_DELAY(200000);						//延遲0.1Sec
		GCC_RL(LEDPort);	 		           	//LEDPort左旋
	}
	LEDPort=temp;								//還原LED_Port之狀態
	_int2f=0;									//避免彈跳引發之誤動作
}
DEFINE_ISR(ISR_Int3,0x34)						//INT3 ISR
{	u8 i,temp;
	temp=LEDPort;								//保留LEDPort目前狀態
	LEDPort=0b01111111;							//設定LEDPort初值
	for(i=0;i<8;i++)
	{	GCC_DELAY(200000); GCC_DELAY(200000);	//延遲0.2Sec
		GCC_RR(LEDPort);						//LEDPort右旋
	}
	LEDPort=temp;								//還原LEDPort之狀態
	_int3f=0;									//避免彈跳引發之誤動作
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}