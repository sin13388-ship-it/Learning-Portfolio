// PROGRAM	: DotMatrixV3.c							2019.0306
// FUNCTION	: 8*8 Dot Matrix LED Display String 	By Steven
#include <HT66F2390.h>
#include "DotMatrix.H"
#include "MyType.H"
#include "MatrixFont.H"
volatile u8 ScanCode,Buffer[16];
volatile u8 volatile *ptr;
const u8 string[]={"Hello World! "};
void Delayms(u16 del);
void Copy2Buffer(const u8* ptr);
void DisplayChar(u8 ms);
void ShiftUp(void);
void ShiftDown(void);
void main()
{	const u8 *pstr;
	u8 i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;						//Config ScanPort as O/P
	DotPort=0; DotPortC=0;							//Config DotPort as O/P
	_psc0r=0x01; _tb0c=0x04; _tb0e=1;				//fPSC0=fSYS/4,週期=4096*(1/fPSC0),致能TB0中斷
	ptr=Buffer; ScanCode=0b00000001;				//Initila Pointer and ScanCode
	_emi=1;											//致能EMI
 	while(1)
	{	for(i=0;i<16;i++) Buffer[i]=0;				//清除Buffer
		pstr=string;
		while(*pstr!=0)
		{	Copy2Buffer(&font[*pstr-' '][0]);		//複製字型
			pstr++;									//指向下一個字
			for(i=0;i<8;i++)
			{	ptr=Buffer;							//Initial Pointer			
				DisplayChar(40);
				ShiftUp();
			}
		}
	}
}
void DisplayChar(u8 ms)
{	_tb0on=1; Delayms(ms);							//Satrt TB0 & Delay 50ms					
	while(ScanCode!=1);								//等待完整Frame掃描完成
	_tb0on=0; DotPort=0x00;							//Stop TB0
}
void Copy2Buffer(const u8 *cptr)
{	u8 i;
	for(i=0;i<8;i++)								
	{	//Buffer[i]=0;								//Clear Buffer[0]~Buffer[7]
		Buffer[i+8]=*cptr++;						//Copy Pattern to Buffer[8]~Buffer[15]
	}
}
void ShiftUp(void)
{	u8 i,temp;	
	ptr=Buffer;										//Initial Pointer
	temp=*ptr;										//Backup Buffer[0]
	for(i=0;i<15;i++) {*ptr=*(ptr+1); ptr++;}		//Buffer Shift
	*ptr=temp;										//Reload temp to Buffer[15]
}
void ShiftDown(void)
{	u8 i,temp;	
	ptr=Buffer+15;									//Initial Pointer
	temp=*ptr;										//Backup Buffer[0]
	for(i=0;i<15;i++) {*ptr=*(ptr-1); ptr--;}		//Buffer Shift
	*ptr=temp;										//Reload temp to Buffer[0]
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