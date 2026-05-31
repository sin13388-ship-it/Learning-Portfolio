// PROGRAM	: U2_1_2.c							2017.0420
// FUNCTION	: Nest Interrupt Demo Program		By Steven
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
	_papu1=1; _papu7=1;							//致能PA1/PA7 Pull-High電阻
	_int1ps=1;									//指定INT1功能於PA7腳位實現
	_integ=0b00001010;							//選擇INT1/INT0為負緣觸發型式
	_int0e=1; _int1e=1; _emi=1;					//致能INT0,INT1及中斷總開關
	while(1)
	{	for(i=0;i<10;i++)						//顯示迴圈 
		{	SEGPort=SEG_TAB[i];					//查表並送至顯示器顯示	
		 	Delayms(1000);						//延遲1Sec
		}
	}
}
DEFINE_ISR(ISR_Int0,0x04)						//INT0 ISR
{	u8 i,temp;
	_int0e=0;									//禁能INT0中斷,避免彈跳引發之誤動作
	_emi=1;										//致能中斷總開關
	temp=LEDPort;								//保留LEDPort目前狀態	
	LEDPort=0b11111110;							//設定LEDPort初值
	for(i=0;i<8;i++)
	{	GCC_DELAY(250000); GCC_DELAY(250000);   //延遲0.25Sec
		GCC_RL(LEDPort);	 		           	//LEDPort左旋
	}
	LEDPort=temp;								//還原LED_Port之狀態
	_int0f=0;									//避免彈跳引發之誤動作
	_int0e=1;									//重新致能INT0中斷
}
DEFINE_ISR(ISR_Int1,0x08)						//INT1 ISR
{	u8 i,temp;
	_int1e=0;									//禁能INT1中斷,避免彈跳引發之誤動作
	_emi=1;										//致能中斷總開關
	temp=LEDPort;								//保留LEDPort目前狀態
	LEDPort=0b01111111;							//設定LEDPort初值
	for(i=0;i<8;i++)
	{	GCC_DELAY(250000); GCC_DELAY(250000);	//延遲0.25Sec
		GCC_RR(LEDPort);;						//LED_Port右旋
	}
	LEDPort=temp;								//還原LEDPort之狀態
	_int1f=0;									//避免彈跳引發之誤動作
	_int1e=1;									//重新致能INT1中斷
}
void Delayms(u16 del)
{	u16 i;										//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}