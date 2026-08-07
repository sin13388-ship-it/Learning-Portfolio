// PROGRAM	: BMTouchV1_eDisplay.c							2020.0513
// FUNCTION	: BM 8-Key Touch Module(Poll)					By Steven
// LIBRARY	: eDisplay.c
// Hardwired: PF6->SDA(eDisplay,BM Module), PF5->eDisplay RES  
//			  PF7->SCL(eDisplay,BM Module) 
// NOTE 	: Define BMTouch in eDisplay.h	
// 注意		: eDisplay.h中的ePAUSE的定義若<65，圓盤型的會當機，
//	     	  長條型的不得小於60!!! 
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.H"
#define TouchID  (0x50<<1)									//Best Module Touch Module Device ID
#define TouchCMD 0x0D
u8 ScanTouch(void);
void main()
{	u8 i,key;
	_wdtc=0b10101111;										//關閉看們狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,Blue);
	eDisplayStr(5,18,(u8*)"BM 8-Key Module");
	eDisplayStr(4,64,(u8*)"0 1 2 3 4 5 6 7 ");
	ForeColor=White;
	while(1)
	{	do key=ScanTouch(); while(key>8);					//Wait for Touching
		eDisplayChar(60,40,key+'0');						//轉成ASCII顯示
		for(i=0;i<8;i++)
		{	if(key==i) eDisplayRet(3+(i<<4),10,80,10,Red);
			else eDisplayRet(3+(i<<4),10,80,10,Green);
		}
	}
}
u8 ScanTouch(void)
{	u8 keyNum;
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|0); CheckACK();						//送出裝置ID+寫入
	WriteByte(TouchCMD); CheckACK();						//送出裝置Command
	I2C_STOP();
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|1); CheckACK();						//送出裝置ID+讀取
	keyNum=ReadByte();
	SendACK(1);												//送出NO_ACK信號
	I2C_STOP(); 											//送出I2C STOP信號
	return keyNum;
}