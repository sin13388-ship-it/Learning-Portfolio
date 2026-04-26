// PROGRAM	: ThreeDigits.c							2026.0424
// FUNCTION	: 7 SEGMENT LED Demo Program			Modified By Vera

//include 需要的庫
#include "HT66F2390.h"
#include "MyType.h"

//define SEG Output 
#define SEGPort		_pg
#define SEGPortC	_pgc

#define COMort		_pe
#define COMPortC	_pec




void delay10ms(u8);
void InitSystem();
u8 GetSegmentCode(int , u8 );
void delay5ms(u8 );

void Polling(u8 period, int Counter);


//Display pattern with delaytime
//const 讓compiler 使用程式記憶體
const u8 SEG_PATTERN[]={
		0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
			
int main(){		

	int Counter =9999;
	
	InitSystem();

	while(1)
	{
		Polling(200,Counter); //1 sec

		Counter--;		
	
		if(Counter < 0)  Counter=9999;
		
	}
}

void delay10ms(u8 delayCount)
{
	u8 i;
	for(i=0; i<delayCount; i++)
		GCC_DELAY(20000); //20000 clks =10ms	
}

void delay5ms(u8 delayCount)
{
	u8 i;
	for(i=0; i<delayCount; i++)
		GCC_DELAY(10000); //10000 clks =5ms	
}

void Polling(u8 period, int Counter)
{
	
	u8 timeout=0;
	static u8 DigiIndex=0;
	
	while(timeout < period)
	{
		
		_pe &=0xF0; //不知幹嘛用的

		_pg=GetSegmentCode(Counter, DigiIndex);

		_pe |=(1<<DigiIndex);	

		DigiIndex=(DigiIndex+1)%4;
		
		delay5ms(1);	
		
		timeout ++;		
	
	}	


}


void InitSystem()
{
	_wdtc=0xAB;										//Disable watch dog timer
	SEGPortC=0;	
	COMPortC=0;	
}

u8 GetSegmentCode(int Number , u8 DigiIndex)
{
	//回傳當前位數對應的值	
	
	u8 code;
	
	switch(DigiIndex){
		case 0 : 
			code =(u8)((Number/1) %10); //個位
			break;
		case 1 :
			code=(u8)((Number/10) %10);
			break;
		case 2 :
			code=(u8)((Number/100) %10);
			break;			
		case 3 :
			code=(u8)((Number/1000) %10);
			break;
		default :
			break;		
	}
	
	return  SEG_PATTERN[code];	
	
}

