// PROGRAM	: U1_1_2.c								2017.0413
// FUNCTION	: LED Scanning Demo Program (Built-in)	By Steven
#include <HT66F2390.h>
#include "MyType.h"			
#define LED_Port  _pf								
#define LED_PortC _pfc
void Delayms(u16);									//函式原型宣告						
void main()
{	_wdtc=0b10101111;								//關閉看們狗計時器
	LED_PortC=0x0;									//設定 LED_Port 為輸出模式
	LED_Port=0xFE;									//設定 LED_Port 初值
	while(1)
	{	while(LED_Port & 0b10000000)				//若MSB不為0則迴圈繼續
		{	Delayms(100);
			GCC_RL(LED_Port);						//左旋
		}
		while(LED_Port & 0b00000001)				//若LSB不為0則迴圈繼續	
		{	Delayms(200);
			GCC_RR(LED_Port);						//右旋
		}				
	}
}
void Delayms(u16 del)								//延遲del*200指令週期
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}	