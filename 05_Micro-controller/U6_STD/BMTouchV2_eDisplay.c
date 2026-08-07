// PROGRAM	: BMTouchV1_eDisplay.c							2020.0513
// FUNCTION	: BM 8-Key Touch Module(Poll pINT)				By Steven
// LIBRARY	: eDisplay.c
// Hardwired: PF6->SDA(eDisplay,BM Module), PF5->eDisplay RES  
//			  PF7->SCL(eDisplay,BM Module), PA1->BM Module INT
// NOTE 	: Define BMTouch in eDisplay.h	
// 注意		: eDisplay.h中的ePAUSE的定義若<65，圓盤型的會當機，
//	     	  長條型的不得小於60!!! 
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.H"
#define TouchID  (0x50<<1)									//Best Module Touch Module Device ID
#define TouchCMD 0x0D
#define pINT	 _pa1
#define pINTC	 _pac1
#define pINTPU	 _papu1
u8 ScanTouch(void);
void main()
{	u8 i,key,prekey=0xFF;
	_wdtc=0b10101111;										//關閉看們狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,Blue);
	eDisplayStr(5,18,(u8*)"BM 8-Key Module");
	eDisplayStr(4,64,(u8*)"0 1 2 3 4 5 6 7 ");
 	pINTC=1; pINTPU=1;										//I/P and Pull-high Enable
	ForeColor=White;
	while(1)
	{	if(pINT) key=0xFF;									//Key not Touch
		else key=ScanTouch();								//Read Touch Key
		if(key!=prekey)										//按鍵狀態改變?	
		{	prekey=key;										//是,更新按鍵值
			if(key==0xFF)									//觸控鍵釋放?
			{ 	eDisplayRet(60,8,40,14,BackColor);			//是,清除
				eDisplayRet(0,128,80,10,BackColor);
			}
			else											//觸控鍵按壓											
			{	eDisplayChar(60,40,key+'0');				//轉成ASCII顯示
				for(i=0;i<8;i++)
				{	if(key==i) eDisplayRet(3+(i<<4),10,80,10,Red);
					else eDisplayRet(3+(i<<4),10,80,10,Green);
				}
			}
		}
		GCC_DELAY(200);
	}
}
u8 ScanTouch(void)
{	u8 keyNum;
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|0); CheckACK();						//送出裝置ID+寫入
	WriteByte(TouchCMD); CheckACK();						//送出裝置Command
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|1); CheckACK();						//送出裝置ID+讀取
	keyNum=ReadByte();
	SendACK(1);												//送出NO_ACK信號
	I2C_STOP(); 											//送出I2C STOP信號
	return keyNum;
}