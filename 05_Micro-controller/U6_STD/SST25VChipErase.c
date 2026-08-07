// PROGRAM	: SST25VChipErase.c								2023.0111
// FUNCTION	: SST25VF032B  Chip-Erase   					By Steven
// LIBRARY	: eDisplayV2.c,SST25V.c
// NOTE		: PF5->/RES, PF6->SDA, PF7->SCL (eDisplay)
//			  PF0->SCS, PF1->MOSI, PF2->MISO, PF3->SCK
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.h"
#include "SST25V.h"
void main()
{	bit fSucced=1; u8 i; u32 address=0;
	_wdtc=0b10101111;										//關閉看們狗計時器
	eDisplayReset();										//Reset eDisplay
	_pfs0=0b10101000;										//PF1->SDO, PF2->SDI,PF3->SCK
	_sdisdaps=1;											//PF2->SDI 		
	SCS=1; SCSC=0;											//SCS O/P (PE0)
	_simc0=0b00000010;										//SPI Master(fSYS/4), 致能SIMEN
	_simc2=0b00111000;										//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	eDisplayRet(0,128,0,128,Blue);	
	eDisplayStr(15,5,(u8*)"Chip Erase.c");
	eDisplayRet(0,128,22,106,White);						//清除螢幕
	BackColor=White; ForeColor=Black;
	eDisplayStr(5,25,(u8*)"SST25 Protected");				//顯示保護狀態
	do
	{	WriteStatus(0);										//取消保護
	} while (ReadStatus());									//若無法取消保護,持續迴圈
	for(i=0;i<10;i++)
	{	eDisplayRet(0,128,22,106,White);					//清除螢幕
		Delayms(120);
		ForeColor=Red;
		eDisplayStr(10,60,(u8*)"Chip ERASE ???");
		Delayms(250);
	}
	eDisplayRet(0,128,22,106,Yellow);						//繪製矩形區域
	BackColor=Yellow;
	ChipErase();											//清除晶片
	eDisplayStr(10,60,(u8*)"Verify...     ");
	SCS=0;
	SPIReadWrite(READ);										//設置SST25V讀取命令
	SPIReadWrite(address>>16);								//設置讀取起始位址
	SPIReadWrite(address>>8);
	SPIReadWrite(address);
	do
	{	if(SPIReadWrite(0xFF)!=0xFF)
		{ 	fSucced=0;			
			break;
		}
//	} while(++address<(u32)4194304);						//每個位址均檢查(耗時)
	} while(++address<419430);								//僅檢查前十分之一位址
	SCS=1;	
	while(1)		
	{	eDisplayRet(10,104,60,12,Yellow);					//清除字串	
		if(fSucced) eDisplayStr(10,60,(u8*)"Erase OK...");
		else eDisplayStr(10,60,(u8*)"Erase Failed!!!");
		Delayms(500);										//延遲0.5秒	
	}	
}