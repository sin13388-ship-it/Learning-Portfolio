// Ver 2020.0406
#include <HT66F2390.h>
#include "MyType.h"
/*****************************************************************************
fSYS's Definition should be Modified According to HT66F2390 FHS Bit Seeting,
and the Frequency Selection of HIRCC SFR(FHS=0), HTX Oscillator's Frequency(FHS=1). 
As well as the CKS[2:0] Setting of SCC SFR.
*******************************************************************************/
#define fSYS 	11059200							//System Frequency
#if (fSYS > 12000000)
	#define FreqFactor	 ((fSYS/8000000)+3)			//16MHz
#elif (fSYS > 8000000)
	#define FreqFactor	 ((fSYS/8000000)+2)			//12MHz
#else
	#define FreqFactor	 ((fSYS/8000000)+1)			// 8MHz
#endif
/******************************************************************************/
#define	 SCL		_pf7							//e-Display SCL -> PF7
#define	 SDA		_pf6							//e-Display SDA -> PF6
#define	 SCLC		_pfc7							//PFC7
#define	 SDAC		_pfc6							//PFC6
#define	 SCLPU		_pfpu7							//e-Display SCL -> PF7
#define	 SDAPU		_pfpu6							//e-Display SDA -> PF6
#define	 peReset	_pf5						
#define	 peResetC	_pfc5						
extern volatile u16 ForeColor,BackColor;
extern volatile bit feDisplay5DigitNoSpace;
#define	 DeviceID	(0x2D<<1)						//e-Display I2C 裝置位址
enum { cmdASC=1,cmdRET,cmdDOT,cmdCLR,cmdPIC,		//e-Display命令定義			
	   eBUSY=0x55};
enum { White=0xFFFF,Black=0x0000,Red=0xF800, 		//e-Display顏色定義
	   Green=0x07E0,Blue=0x001F,Yellow=0xFFE0,
	   Magenta=0xF81F,Cyanh=0x7FFF,Peach=65334,
	   Pale_Blue=32217,Cyan=2047,Orange=64518}; 
void Init_I2C(void);
void I2C_START(void);
void I2C_STOP(void);
_Bool CheckACK(void);
void SendACK(_Bool ack);
u8 e_Read(void);
void e_Command(u8*);
void eDisplayReset(void);
void eDisplayClear(u8,u8,u8,u8);
void eDisplayRet(u8,u8,u8,u8,u16);
void eDisplayPic(u8,u8,u8,u8,const u16*);
void eDisplayDot(u8 x, u8 xSize, u16 color);
void eDisplayStr(u8 x, u8 y,u8 *ptr);
void eDisplayChar(u8 x, u8 y,u8 ch);	
void eDisplay5Digit(u8 x, u8 y,u16 data, u8 dp);	//20171221
void eDisplayHex(u8 x, u8 y, u8 h);					//20200427 Font Size: 8x14	
void eDisplayBin(u8 x, u8 y, u8 h);					//Font Size: 8x14	
void e_DataRAM(u8*,u8);
void WriteByte(u8);
u8 ReadByte(void);
void Delayms(u16);