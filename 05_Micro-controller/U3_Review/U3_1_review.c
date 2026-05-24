//複習	2026.05.24
//ref: U3_1.C

#include "HT66F2390.h"
#include "MyType.h"

#define SegPort _pg		//7段輸出port
#define SegPortC _pgc		//7段I/O port control
#define ScanPort _pe		//scan port
#define ScanPortC _pec 		//scan I/O port control

//7-seg patterns
const u8 SEG_TAB[] = {			   				//七段顯示碼建表區(共陰)
				0x3F,0x06,0x5B,0x4F,0x66,
			   	0x6D,0x7D,0x07,0x7F,0x67};

//global variables
volatile u8 *ptr, Buffer[4], ScanCode;

void main()
{
	//Disable wdtc
	_wdtc=0b10101111;
	//initialize segport, segportc (output)
	SegPort=0; SegPortC=0; 
	//initialize scancode, scanportc
	ScanPort &=0xF0; ScanPortC&=0xF0;
	//points pointer to buffer
	ptr=Buffer;
	//Scancode reset
	ScanCode=0b00000001;
	//設定Timebase 
	_psc0r=0x01; //fsys/4
	_tb0c=0x85; //8192
	_psc1r=0x02; //fsub
	_tb1c=0x87; //32767	
	//Buffer init
	u8 i,j;
	for(i=0; i<4;i++) Buffer[i]=0;	
	_emi=1; //Enable interrupt
	_tb0e=1;
	j=0;
	while(1){
		//跑馬燈內容
		for(i=3;i!=0;i--) Buffer[i]=Buffer[i-1];
		Buffer[0]=j++;
		if(j>=9) j=0;
		//TB1 as delay
		while(!_tb1f);
		_tb1f=0;		
	}

} 			  

DEFINE_ISR(ISR_TB0, 0x24)
{
	//負責刷新Scancode、7段顯示器的碼

	SegPort = 0; //要先清除Segport避免鬼影
	ScanPort = ScanCode;
	SegPort = SEG_TAB[*ptr++];
	
	GCC_RL(ScanCode);
	if (ScanCode==0b00010000){
		//Reset	
		ScanCode=0b00000001;
		ptr=Buffer;
	}

}