// PROGRAM	: BMTouchV3_eDisplay.c						2020.0513
// FUNCTION	: BM8-Key Touch Module(INT)					By Steven
// LIBRARY	: eDisplay.c
// Hardwired: PF6->SDA(eDisplay,BM Module), PF5->eDisplay RES  
//			  PF7->SCL(eDisplay,BM Module), PA1->BM Module INT
// NOTE 	: Define BMTouch in eDisplay.h	
//			: 只要手指在觸控按鍵上INT即維持於低電位,必須放開再按才能更新Key值！
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
volatile u8 key=0xFF;
void main()
{	u8 i,prekey=0xFF;
	_wdtc=0b10101111;										//關閉看們狗計時器
	eDisplayReset();
	eDisplayRet(0,128,0,128,Blue);
	eDisplayStr(5,18,(u8*)"BM 8-Key Module");
	eDisplayStr(4,64,(u8*)"0 1 2 3 4 5 6 7 ");
 	pINT=1;													//PA1 Pull-high Enable
	_integ=0x02;											//Select INTO Falling Trigger
	_int0ps=0;												//INT0 PIN-->PA1
	_int0e=1; _emi=1;										//Enable INTO/Master Interrupt
	ForeColor=White;
	while(1)
	{	if(key!=prekey)										//按鍵狀態改變?	
		{	_emi=0;
			prekey=key;										//是,更新按鍵值
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
			_emi=1;
		}
	}		
}
DEFINE_ISR(INT0,0x04)
{	GCC_DELAY(200);
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|0); CheckACK();						//送出裝置ID+寫入
	WriteByte(TouchCMD); CheckACK();						//送出裝置Command
	I2C_START();											//送出I2C START信號 
	WriteByte(TouchID|1); CheckACK();						//送出裝置ID+讀取
	key=ReadByte();
	SendACK(1);				 								//送出NO_ACK信號	
	I2C_STOP();												//送出I2C STOP信號
}