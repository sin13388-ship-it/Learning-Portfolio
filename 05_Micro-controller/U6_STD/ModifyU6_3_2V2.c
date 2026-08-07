// PROGRAM	: ModifyU6_3_2V.c				2020.0905
// FUNCTION	: SIM SPI Slave Demo Program	By Steven
// Library	: eDisplayV2.c
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.H"
void main()
{	u8 i=1;
	_wdtc=0b10101111;						//關閉看們狗計時器
	eDisplayReset();						//Reset eDisplay
	eDisplayRet( 0,128, 0,128,Blue);		//繪製矩形區域
	eDisplayStr(32, 5,(u8*)"U6_3_2V2");
	eDisplayStr(28,25,(u8*)"SPI Slave");
	eDisplayStr(20,90,(u8*)"REC. Cnt:0");
	_simc0=0b10100000;						//SPI Slave
	_simc2=0b00111100;						//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	_ifs2=0b01110000;						//PF0->/SCS,PF2->SDI,PF3->SCK
	_pfs0=0b10101010;						//PF0->/SCS,PF1->SDO, PF2->SDI,PF3->SCK
	_simen=1;								//致能SIMEN
	while(1)
	{	_simd=i;							//寫資料至SIMD
		_trf=0;								//清除TRF旗標	
		do
		{	eDisplayStr(4,60,(u8*)"Wait for Data..");
			ForeColor=~ForeColor;
			Delayms(80);  					//延遲 50ms
		} while(!_trf);	   					//等待接收完成
		ForeColor=Yellow;
		eDisplayRet(4,124,60,14,BackColor);	//清除Wait for Data..字串
		eDisplayChar(60,60,_simd);			//顯示接收值
		eDisplayChar(92,90,i+'0');			//顯示已傳送字元數
		i=(i<9)? i+1 :0;		
		Delayms(900);
	}	
}
