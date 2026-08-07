// PROGRAM	: BTModifyU6_2_3.c						2020.0511
// FUNCTION	: e-Display I2C Demo Program 			By Steven
// LIBRARY	: eDisplay.c,SST25V.c
// NOTE		: PF5->/RES, PF6->SDA, PF7->SCL (eDisplay)
//			  PF0->SCS, PF1->MOSI, PF2->MISO, PF3->SCK(eDisplay)
//			  PA6->TX(HC-05), PA7->RX(HC-05),	
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.h"
#include "SST25V.h"
#define	 fH		8000000								//MCU HIRC Frequency
#define  BR		19200								//Baud Rate
void Delayms(u16);
void main()
 {	u8 i=0;
 	_wdtc=0b10101111;								//關閉看門狗計時器
 	eDisplayReset();								//Reset eDisplay
 	
	_pas1=0b00110000;								//設置RX0->PA6
	_u0cr1=0b10000000;								//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b01100000;								///RXEN0/BRGH0////	
	_brg0=fH/((u32)16*BR)-1;						//BRGH0=1
	_rxif0=0;
	_pfs0=0b10101000;								//PF1->SDO, PF2->SDI,PF3->SCK
	_sdisdaps=1;									//PF2->SDI 		
	SCS=1; SCSC=0;									//SCS O/P (PE0)
	_simc0=0b00000010;								//SPI Master(fSYS/4), 致能SIMEN
	_simc2=0b00111000;								//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	eDisplayRet(0,128,0,128,Blue);					//繪製矩形區域
	while(1)
	{	while(!_rxif0);								//等待UR接收到資料
	 	i=_txr_rxr0;								//取得接收資料
	 	i=i-((i<'A')?'0':'7');						//ASCII轉換成數值
	 	if(i==15) eDisplayRet(0,128,0,128,Black); 	//畫面清除
		else
		{	if(eDisplayFlash(128,0,(u32)i<<15)==0)	//顯示第i張圖(自動座標)
			eDisplayRet(0,128,0,128,Black);			//若失敗清除畫面
		}
	}
}