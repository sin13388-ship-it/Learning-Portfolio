// PROGRAM	: U6_3_2.c						2017.0524
// FUNCTION	: SIM SPI Slave Demo Program	By Steven
#include <HT66F2390.h>
#include "MyType.h"
#define  SEGPort	_pg
#define  SEGPortC	_pgc
void Delayms(u16);							//函式原型宣告			
void main()
{	u8 i=1;
	_wdtc=0b10101111;						//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;					//清除Port並規劃為輸出屬性
	_simc0=0b10100000;						//SPI Slave
	_simc2=0b00111100;						//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	_ifs2=0b01110000;						//PF0->/SCS,PF2->SDI,PF3->SCK
	_pfs0=0b10101010;						//PF0->/SCS,PF1->SDO, PF2->SDI,PF3->SCK
	_simen=1;								//致能SIMEN
	while(1)
	{	_simd=i++;							//寫資料至SIMD
		_trf=0;								//清除TRF旗標	
		do
		{ 	Delayms(50);  					//延遲 50ms
			SEGPort^=(1<<7);				//七段顯示器h節段亮滅切換
		} while(!_trf);	   					//等待接收完成
		SEGPort=_simd;				    	//顯示
		if(i>9) i=0;
		Delayms(400); SEGPort=0;
	}	
}
void Delayms(u16 del)						//@fSYS=8MH,延遲del*ms				
{	u16 i;							
	for(i=0;i<del;i++) GCC_DELAY(2000);		//延遲del*2000指令週期			
}