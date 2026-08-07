// PROGRAM	: ModifyU6_2_3.c					2022.0111
// FUNCTION	: e-Display I2C Demo Program 		By Steven
// LIBRARY	: eDisplay.c,SST25V.c
// NOTE		: PF5->/RES, PF6->SDA, PF7->SCL (eDisplay)
//			  PF0->SCS, PF1->MOSI, PF2->MISO, PF3->SCK
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.h"
#include "SST25V.h"
void main()
 {	u8 i=0;
 	_wdtc=0b10101111;										//關閉看門狗計時器
 	eDisplayReset();										//Reset eDisplay
	_pfs0=0b10101000;										//PF1->SDO, PF2->SDI,PF3->SCK
	_sdisdaps=1;											//PF2->SDI 		
	SCS=1; SCSC=0;											//SCS O/P (PF0)
	_simc0=0b00000010;										//SPI Master(fSYS/4), 致能SIMEN
	_simc2=0b00111000;										//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	eDisplayRet(0,128,0,128,Blue);							//繪製矩形區域
	feDisplay5DigitNoSpace=1;								//不顯示數字前之空白
	while(1)
	{	if(eDisplayFlash(128,0,(u32)i<<15)) 				//顯示第i張圖並延遲2秒
		{	Delayms(1500);
		 	eDisplay5Digit(5,112,i,0);						//顯示目前編號				
		 	Delayms(600);
		}
		else
		{	eDisplayStr(4,25,(u8*)"Num.   is Lack!");	
		 	eDisplay5Digit(45, 25,i,0);
		 	Delayms(500);					
		}							
		if(++i>20) i=0;										//限制20張,可改
		eDisplayRet(0,128,0,128,Black);						//繪製矩形區域
	}
}