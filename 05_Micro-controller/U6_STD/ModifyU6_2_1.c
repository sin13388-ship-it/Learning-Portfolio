// PROGRAM	: ModifyU6_2_1.c						2026.0213
// FUNCTION	: SavePicture to SST25VF032B(CRC Demo) 	By Steven
// LIBRARY	: eDisplayV2.c,SST25V.c 
// NOTE		: PF5->/RES, PF6->SDA, PF7->SCL (eDisplay)
//			  PF0->SCS, PF1->MOSI, PF2->MISO, PF3->SCK
// ******	: According Flash Memory Tpye is SST25V or BD25VQ 
// 			  to Select	AAIProgram() or PageProgram() Functi			
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.h"
#include "SST25V.h"
//#include "MKitty2_128.h"							//**改檔名(注意檔頭必須包含X,Y Size資訊)
//#include "MKitty1_128.h"							//**改檔名(注意檔頭必須包含X,Y Size資訊)
//#include "prayer_plant.h"							//**改檔名(注意檔頭必須包含X,Y Size資訊)
//#include "MPuppy.h"									//**改檔名(注意檔頭必須包含X,Y Size資訊)
#define  NUM	(u32)1								//**改編號
void CRCDisplay(u8 x,u8 y,u16 CRC);
void main()
{	u16 i,WrCRC,RdCRC; u32 address=NUM<<15;
	_wdtc=0b10101111;								//關閉看們狗計時器
	eDisplayReset();								//Reset eDisplay
	_pfs0=0b10101000;								//PF1->SDO, PF2->SDI,PF3->SCK
	_sdisdaps=1;									//PF2->SDI 		
	SCS=1; SCSC=0;									//SCS O/P (PE0)
	_simc0=0b00000010;								//SPI Master(fSYS/4), 致能SIMEN
	_simc2=0b00111000;								//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	_poly=0;										//選定CRC-CCITT
	eDisplayClear(0,128,0,128);						//清除螢幕
	BackColor=White;
	ForeColor=Black;
	eDisplayStr(5,25,(u8*)"SST25 Protected");		//顯示保護狀態
	do
	{	WriteStatus(0);								//取消保護
	} while (ReadStatus());							//若無法取消保護,持續迴圈
	Erase(address,ERASE32K);						//起始位址，清除32K-Byte
	ForeColor=Red;
	eDisplayStr(5,25,(u8*)"  ..Writting.. ");		//顯示字串
	WrCRC=AAIProgram(address,PIC,sizeof(PIC)>>1);	//**寫至Flash SST25V使用這ㄧ行
//	WrCRC=PageProgram(address,PIC,sizeof(PIC)>>1);	//**寫至Flash ZB25VQ使用這ㄧ行
	ForeColor=Blue;
	eDisplayStr(5,45,(u8*)"Orignal CRC: ");			//顯示字串
	CRCDisplay(50,60,WrCRC);						//顯示CRC
	ForeColor=Red;
	eDisplayStr(5,25,(u8*)"  ..Reading..   ");		//顯示字串
	_crcdh=0; _crcdl=0;								//清除CCRDH/L SFRs	
	SCS=0;
	SPIReadWrite(READ);								//設置SST25V讀取命令
	SPIReadWrite(address>>16);						//設置讀取起始位址
	SPIReadWrite(address>>8);
	SPIReadWrite(address);
	for(i=0;i<sizeof(PIC);i++)						//逐Byte取回資料
		_crcin=SPIReadWrite(0xFF);					//計算CRC
	SCS=1;		
	RdCRC=((u16)_crcdh<<8)|_crcdl;					//取得CRC
	ForeColor=Magenta;
	eDisplayStr(5,80,(u8*)"Read Out CRC: ");		//顯示CRC
	CRCDisplay(50,95,RdCRC);						//顯示CRC
	Delayms(2000);									//延遲兩秒
	while(1)
	{	eDisplayClear(0,128,0,128);
		if(WrCRC==RdCRC) 							//判定CRC是否一致
		{	ForeColor=Black;
			eDisplayStr(10,60,(u8*)"Verify OK...");
		}
		else	
		{	ForeColor=Red;
			eDisplayStr(10,60,(u8*)"Error !!!");
		}
		Delayms(500);								//延遲0.5秒	
	}	
}
void CRCDisplay(u8 x,u8 y,u16 CRC)
{	u8	i,crc[5]={0};
	crc[0]=CRC>>12;  crc[1]=(CRC>>8)&0x0F;			//以4-Bit為單位分別取出CRC
	crc[2]=(CRC>>4)&0x0F; crc[3]=CRC&0x0F;
	for(i=0;i<4;i++) crc[i]+=(crc[i]<10)? '0':'7';	//轉為ASCII碼
	eDisplayStr(x,y,crc);							//顯示CRC
}