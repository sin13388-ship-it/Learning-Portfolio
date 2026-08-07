#define	SCS		_pf0										//-->SST25VF /CE
#define	SCSC	_pfc0
#define	MISO	_pf2										//-->SST25VF SDI
enum { WRSR=1,READ=3,WRDI,RDSR,WREN,EWSR=0x50,				//SST25VF命令
	   ERASE32K=0x52,EBSY=0x70,DBSY=0x80,
	   PP=02,												//for ZB25V
	   AAIPROGRAM=0xAD,CHIPERASE=0x60}; 
u16 AAIProgram(u32,const u16*,u16);							//for DB25VQ
u16 PageProgram(u32 address,const u16* ptr, u16 count);		//for SST25V
void Erase(u32,u8);
void ChipErase(void);
u8 ReadStatus(void);
void WriteStatus(u8 status);
u8 SPIReadWrite(u8 data);
u8 eDisplayFlash(u8 x,u8 y,u32 address);