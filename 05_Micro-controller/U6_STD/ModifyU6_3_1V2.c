// PROGRAM	: ModifyU6_3_1V2.c				2022.0904
// FUNCTION	: SPI Master Demo Program		By Steven
// Library	: eDisplay.c
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.H"
#define  KeyPort	_pg			
#define  KeyPortC	_pgc
#define  KeyPortPU	_pgpu
u8 SPIReadWrite(u8);
u8 ScanKey(void);
void main()
{	u8 RxData,Key;
	_wdtc=0b10101111;						//關閉看們狗計時器
	eDisplayReset();						//Reset eDisplay
	eDisplayRet( 0,128, 0,128,Blue);		//繪製矩形區域
	eDisplayStr(32, 5,(u8*)"U6_3_1V2");
	eDisplayStr(24,25,(u8*)"SPI Master");
	eDisplayStr(20,90,(u8*)"TRX. Cnt:0");
	_simc0=0b00000000;						//SPI Master(fSYS/4)
	_simc2=0b00111100;						//CKPOL/CKEG/MLS/CSEN/WCOL/TRF=11100
	_pfs0=0b10101010;						//PF1->SDO, PF2->SDI,PF3->SCK,PF0->/SCS
	_sdisdaps=1;							//PF2->SDI
	_simen=1;								//致能SIMEN			
	while(1)
	{	do
		{ 	Key=ScanKey();
			Delayms(100);  					//延遲 100ms
			eDisplayStr(4,60,(u8*)"Press Keypad...");
			ForeColor=~ForeColor;
		} while(Key==16);	   				//等待按壓按鍵
		Key+=(Key<10)?'0':'7';				//ASCII轉換
		ForeColor=Yellow;
		eDisplayRet(4,124,60,14,BackColor);	//清除Press Keypad...字串
		eDisplayChar(60,60,Key);			//顯示按鍵值
		RxData=SPIReadWrite(Key);			//傳送鍵值顯示碼並取得接收值
		eDisplayChar(92,90,RxData+'0');		//顯示接收值
		Delayms(1000);
	}	
}	
u8 SPIReadWrite(u8 data)
{	do
	{	_trf=0;	_wcol=0;					//清除TRF、WCOL
		_simd=data;							//寫資料至SIMD
	} while(_wcol);							//若發生衝撞，重送
	while(!_trf);							//等待傳輸完成
	return _simd;							//回傳接收值
}
u8 ScanKey(void)
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					 	//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)						//依序檢查四列
	{	if(!(KeyPort & 1<<7)) break;		//檢查第0行(KeyPort[4])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;		//檢查第1行(KeyPort[5])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;		//檢查第2行(KeyPort[6])是否按下
		key++;								//否，按鍵值+1
		if(!(KeyPort & 1<<4)) break;		//檢查第3行(KeyPort[7])是否按下
		key++;								//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;	//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}
