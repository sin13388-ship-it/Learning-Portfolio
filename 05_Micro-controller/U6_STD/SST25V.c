// PROPGRAM : SST25V.C 							2026.0213
// FUNCTION	: SST25V32B Library 				By Steven
// Library  : eDisplay.C(for eDisplayFlash())
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.h"
#include "SST25V.h"
u16 AAIProgram(u32 address,const u16* ptr, u16 count)
{	u16 i;
	_crcdh=0; _crcdl=0;								//清除CCRDH/L SFRs	
//	SCS=0; SPIReadWrite(EBSY); SCS=1;				//Enable Busy(When Using Hardware Check BUSY)
	SCS=0; SPIReadWrite(WREN); SCS=1;				//Write Enable
	SCS=0;
	SPIReadWrite(AAIPROGRAM);						//AAI寫入模式
	SPIReadWrite(address>>16);						//設定24-Bit起始位址
	SPIReadWrite(address>>8);
	SPIReadWrite(address);
	_crcin=*ptr>>8; _crcin=(u8)*ptr;				//Hi-Byte先
	SPIReadWrite(*ptr>>8); SPIReadWrite(*ptr++);	//寫入D0、D1(Hi-Byte先)
	SCS=1;			
//	Hardware Check Busy
//	_simen=0; SCS=0;								//禁能SIM
//	while(!MISO);									//等待寫入完成
//	SCS=1; _simen=1;								//致能SIM
	while (ReadStatus()&1);							//Wait for BUSY=0	
	for(i=0;i<count-1;i++)							
	{ 	SCS=0;	
		SPIReadWrite(AAIPROGRAM);					//AAI寫入模式
		_crcin=*ptr>>8; _crcin=(u8)*ptr;
		SPIReadWrite(*ptr>>8); SPIReadWrite(*ptr++);//寫入Dn、Dn-1
		SCS=1;			
//		_simen=0; SCS=0;							//禁能SIM
//		while(!MISO);								//等待寫入完成
//		SCS=1; _simen=1;							//致能SIM
		while (ReadStatus()&1);						//Wait for BUSY=0	
	}	
	SCS=0; SPIReadWrite(WRDI); SCS=1;				//Write Disable
//	SCS=0; SPIReadWrite(DBSY); SCS=1;				//Disable Busy
	return ((u16)_crcdh<<8)|_crcdl;	
}
u16 PageProgram(u32 address,const u16* ptr, u16 count)
{	u16 i;  
	_crcdh=0; _crcdl=0;								//清除CCRDH/L SFRs	
	for(i=0;i<count;i++)							
	{ 	if((u8)address==0)							//Page Boundary
		{	SCS=0; SPIReadWrite(WREN); SCS=1;		//Write Enable
			SCS=0;	
			SPIReadWrite(PP);						//Page Program for DB25V
			SPIReadWrite(address>>16);				//設定24-Bit起始位址
			SPIReadWrite(address>>8);
			SPIReadWrite(address);
		}
		_crcin=*ptr>>8; _crcin=(u8)*ptr;
		SPIReadWrite(*ptr>>8); SPIReadWrite(*ptr++);//寫入Dn、Dn-1(Hi-Byte先)
		address+=2;
		if((u8)address==0)							//Page Boundary
		{	SCS=1;			
			while (ReadStatus()&1);					//Wait for BUSY=0
		}
	}
	SCS=1;			
	while (ReadStatus()&1);							//Wait for BUSY=0	
	return ((u16)_crcdh<<8)|_crcdl;	
}

void Erase(u32 address, u8 sizecode)
{	SCS=0; SPIReadWrite(WREN); SCS=1;				//Write Enable
	SCS=0;
	SPIReadWrite(sizecode);							//設置清除區塊大小命令
	SPIReadWrite(address>>16);						//設定24-Bit起始位址
	SPIReadWrite(address>>8);
	SPIReadWrite(address);
	SCS=1;			
	while(ReadStatus()&0x01);						//等待清除完成
}
void ChipErase(void)
{	SCS=0; SPIReadWrite(WREN); SCS=1;				//Write Enable
	SCS=0;
	SPIReadWrite(CHIPERASE);						//設置全部清除命令
	SCS=1;			
	while(ReadStatus()&0x01);						//等待清除完成
}
u8 ReadStatus(void)
{	u8 temp;
	SCS=0;
	SPIReadWrite(RDSR);								//Status讀取命令
	temp=SPIReadWrite(0xFF);						//讀取
	SCS=1;		
	return temp; 
}
void WriteStatus(u8 status)
{	SCS=0; SPIReadWrite(EWSR); SCS=1;				//Enable Write Status;
	SCS=0;
	SPIReadWrite(WRSR);								//Status寫入命令
	SPIReadWrite(status);							//寫入
	SCS=1;			
}
u8 SPIReadWrite(u8 data)
{	do
	{	_trf=0;
		_wcol=0;									//清除WCOL
		_simd=data;									//Master端，直接送七段碼
	} while(_wcol);									//若發生衝撞，重送
	while(!_trf);									//等待傳輸完成
	return _simd;
}
u8 eDisplayFlash(u8 x,u8 y,u32 address)
{	u16 i; u8 xSize,ySize;
	u8 Buffer[8]={cmdPIC,0,4,0,0,0,0,0};			//裝載命令
	SCS=0;											//設置/CE=0
	SPIReadWrite(READ);								//送出SST25V READ命令
	SPIReadWrite(address>>16);						//送出欲讀取之起始位址(24-Bit)
	SPIReadWrite(address>>8);
	SPIReadWrite(address);
	SPIReadWrite(0xFF);	xSize=SPIReadWrite(0xFF);	//Get xSize
	SPIReadWrite(0xFF);	ySize=SPIReadWrite(0xFF);	//Get ySize
	if((xSize>128) | (ySize>128))
	{	SCS=1;										//設置/CE=1
		return 0;									//Error Code
	}
	e_Command(Buffer);								//送出命令
	if((x>127) | (y>127))							//若不指定正確座標
	{	x=64-(xSize>>1);							//強制置中
		y=64-(ySize>>1);
	}
	Buffer[0]=x; Buffer[1]=xSize;					//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;	
	e_DataRAM(Buffer,4);							//送出參數
	for(i=0;i<(xSize*ySize);i++)
	{	WriteByte(SPIReadWrite(0xFF));				//送出Hi-Byte並等待回應ACK
		CheckACK();
		WriteByte(SPIReadWrite(0xFF));				//送出Lo-Byte並等待回應ACK
		CheckACK();
	}	
	SCS=1;											//設置/CE=1
	I2C_STOP();										//送出I2C STOP信號 
	return 1;										//Success
}