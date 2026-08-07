// PROGRAM	: ModifyU6_1.c								2020.0511
// FUNCTION	: e-Display I2C Demo Program (Lib. Manager)	By Steven
// LIBRARY	: eDisplayV2.c
// NOTE		: PF5->/RES, PF6->SDA, PF7->SCL (eDisplay)
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.h"
#include "Kitty1_64.H"									//注意檔頭無包含X,Y Size資訊
//#include "Kitty2_64.H"									//注意檔頭無包含X,Y Size資訊

#include "monstera_icon.H"									//注意檔頭無包含X,Y Size資訊	
//#include "Puppy.H"
void main()
 {	_wdtc=0b10101111;									//關閉看門狗計時器
 	#if (fSYS == 16000000)
 		_hirc1=1; while(!_hircf);						//頻率若有改變並須更改eDisplayV2.h中fSYS之定義值(16000000)
 	#elif (fSYS == 12000000)
 		_hirc0=1; while(!_hircf);						//頻率若有改變並須更改eDisplayV2.h中fSYS之定義值(12000000)
 	#endif
  	eDisplayReset();									//Reset eDisplay
 	eDisplayClear(0,128,0,128);							//清除螢幕
	eDisplayRet(12,104,12,104,Blue); 					//繪製矩形區域
	while(1)
	{	eDisplayRet(22,84,22,84,Cyanh);					//繪製矩形區域
		eDisplayPic(32,64,32,64,Kitty1);				//顯示Kitty1
		Delayms(2000);									//延遲2秒
		eDisplayRet(22,84,22,84,Yellow);				//繪製矩形區域
		//eDisplayPic(32,64,32,64,Kitty2);				//顯示Kitty2
		eDisplayPic(32,64,32,63,monstera_icon);					//顯示monstera
		Delayms(2000);									//延遲2秒
	}
}