// PROGRAM	: DotMatrixV1.c							2019.0306
// FUNCTION	: 8*8 Dot Matrix LED Static Control 	By Steven
#include <HT66F2390.h>
#include "DotMatrix.H"
#include "MyType.H"
const u8 TAB1[8] ={
     0x18,0x18,0x3C,0x7E,0xFF,0x18,0x18,0x18};
const u8 TAB3[8] ={
     0x00,0x66,0x99,0x81,0x81,0x42,0x24,0x18};     
const u8 TAB2[8] ={
     0x10,0x18,0x1C,0xFF,0xFF,0x1C,0x18,0x10};
const u8 TAB4[8] ={
     0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18};     
void Delayms(u16 del);
volatile u8 ScanCode,Buffer[8];
volatile u8 volatile *ptr;
void main()
{	u8	i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;						//規劃ScanPort為輸出屬性並清除
	DotPort=0; DotPortC=0;							//規劃DotPort為輸出屬性並清除
	_psc0r=0x01; _tb0c=0x04; _tb0e=1;				//fPSC0=fSYS/4,週期=4096*(1/fPSC0),致能TB0中斷
	ptr=Buffer; ScanCode=0b00000001;				//Initila Pointer and ScanCode
	_emi=1;											//致能EMI	

	while(1)
	{	for(i=0;i<8;i++) Buffer[i]=TAB3[i];	      	//Copy First Pattern			
		_tb0on=1; Delayms(2000);					//Satrt TB0 & Delay 2 Sec					
		_tb0on=0; DotPort=0x00;						//Stop TB0
		for(i=0;i<8;i++) Buffer[i]=TAB4[i];       	//Copy Second Pattern			
		_tb0on=1; Delayms(2000);					//Satrt TB0 & Delay 2 Sec					
		_tb0on=0; DotPort=0x00;						//Stop TB0
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0;										//清除DotPort
	ScanPort=ScanCode; DotPort=*ptr++;				//切換掃描與資料，同時進行指標遞增
	GCC_RL(ScanCode);								//更新掃描碼
	if(ScanCode==0b00000001) ptr=Buffer;			//若已掃完八行重新設定指標	
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}	