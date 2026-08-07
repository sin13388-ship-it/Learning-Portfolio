// PROGRAM	: BMTouchV4_PWMLED.c							2020.0513
// FUNCTION	: Best Module Corp. 8-Key Touch Module			By Steven
// LIBRARY	: eDisplay.c
// Hardwired: PF6->SDA(BM Module), PF5->eDisplay RES  
//			  PF7->SCL(BM Module), PA1->BM Module INT
//			  PD0(STP1)->RGB-R	
// NOTE 	: Define BMTouch in eDisplay.h	
// 注意		: eDisplay.h中的ePAUSE的定義若<65，圓盤型的會當機，
//	     	  長條型的不得小於60!!! 
#include <HT66F2390.h>
#include <stdlib.h>
#include "MyType.H"
#include "eDisplayV2.H"
#define TouchID  (0x50<<1)									//Best Module Touch Module Device ID
#define TouchCMD 0x0D
#define pINT	 _pa1
#define pINTC	 _pac1
#define pINTPU	 _papu1
u8 ScanTouch(void);
void main()
{	u8 prekey=3,key; s8 factor; s16 duty=0;
	_wdtc=0b10101111;										//關閉看們狗計時器
	Init_I2C();												//注意未呼叫eDisplayReset()必須先以Init_I2C()規劃腳位
 	pINTC=1; pINTPU=1;										//I/P and Pull-high Enable
	_stm1c0=0b00011000;										//fINT=fSYS(8MHz),ST1ON=1
	_stm1c1=0b10101000;										//PWM模式,Active High,STM1RP控制週期
	_stm1rp=128;											//PWM 週期=32768/fINT
	_stm1al=0; _stm1ah=0;									//Duty=0	
	_pds0=0x02;												//PD0->STP1(R)
	while(1)
	{	while(pINT);										//等待按壓觸控	
		key=ScanTouch();
		factor=prekey-key;									//計算兩次感測按鍵之距離
		if(abs(factor)<3 && factor!=0)						//若過大表示重刷感測板
		{	duty+=factor*750;								//調整Duty
			if(duty<0) duty=(factor>0)?32768:0;				//若小於0則調整至上、下限值
			_stm1al=duty; _stm1ah=duty>>8;
		}
		prekey=key;											//更新prekay
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