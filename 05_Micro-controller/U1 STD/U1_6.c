// PROGRAM	: U1_6.c								2017.0418
// FUNCTION	: 4X4 MATRIX KEYPAD DEMO PROGRAM		By Steven
#include <HT66F2390.h>
#include "MyType.h"
#define		SEGPort		_pg
#define		SEGPortC	_pgc
#define 	KeyPort		_pc			
#define 	KeyPortC	_pcc
#define 	KeyPortPU	_pcpu
const u8 SEG_TAB[] = {0x3F,0x06,					//7-Segment Table(0~F)
			0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
			0x67,0x77,0x7C,0x58,0x5E,0x79,0x71};
u8 ScanKey(void);
void main()
{	u8 i,Key;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;							//清除Port並規劃為輸出屬性
	while(1)
	{	SEGPort=1<<7;								//點亮七段顯示器h節段，其餘節段熄滅
		do
		{ 	Key=ScanKey();
			GCC_DELAY(200000);  					//延遲 100ms
			SEGPort^=(1<<7);						//七段顯示器h節段亮滅切換
		} while(Key==16);	   						//等待按壓按鍵
		SEGPort=SEG_TAB[Key];				      	//查表並顯示按鍵值
		for(i=0;i<10;i++) GCC_DELAY(200000);  		//延遲 1 Sec
	}	
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					         	//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)								//依序檢查四列
	{	if(!(KeyPort & 1<<4)) break;		      	//檢查第0行(KeyPort[4])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;			   	//檢查第1行(KeyPort[5])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;			   	//檢查第2行(KeyPort[6])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<7)) break;			   	//檢查第3行(KeyPort[7])是否按下
		key++;										//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;	   		//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}