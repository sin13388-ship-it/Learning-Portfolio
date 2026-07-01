// PROGRAM	: DotMatrixV5.c								2019.0306
// FUNCTION	: 8*8 Dot Matrix LED Dynamic Control 		By Steven
//			: Use INT0(PA1) to Change Shift Direction
#include <HT66F2390.h>
#include "DotMatrix.H"
#include "MyType.H"
#include "MatrixFont.H"
volatile u8 ScanCode,index;
volatile u16 Buffer[16];
volatile u16 volatile *ptr;
const u8 string[]={"Hello World! "};
void Delayms(u16 del);
void DisplayChar(u8 ms);
void Copy2Q3(const u8 *cptr);
void Copy2Q2(const u8 *cptr);
void Copy2Q1(const u8 *cptr);
void ShiftUp(void);
void ShiftDown(void);
void ShiftLeft(void);
void ShiftRight(void);
void main()
{	const u8 *pstr;
	u8 i;
	_wdtc=0b10101111;								//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;						//Config ScanPort as O/P
	DotPort=0; DotPortC=0;							//Config DotPort as O/P
	_psc0r=0x01; _tb0c=0x04; _tb0e=1;				//fPSC0=fSYS/4,週期=4096*(1/fPSC0),致能TB0中斷
	ptr=Buffer; ScanCode=0b00000001;				//Initila Pointer and ScanCode
	_papu1=1; _int0ps=0;							//Set INT0 at PA1,Enable PA1 Pull-up
	_integ=0b00000010; _int0e=1; 					//Select INT0 Falling Edge Trigger,Enable INT0 Interrupt
	index=0;
	_emi=1;											//致能EMI
 	while(1)
	{	for(i=0;i<16;i++) Buffer[i]=0;				//清除Buffer
		pstr=string;
		while(*pstr!=0)
		{	switch (index)
			{	case 0:	
					Copy2Q3(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer
						DisplayChar(40);
						ShiftDown();
					}
					break;
				case 1:	
					Copy2Q3(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer
						DisplayChar(40);
						ShiftUp();
					}
					break;		
				case 2: 
					Copy2Q1(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(40);
						ShiftLeft();
					}
					break;
				case 3: 
					Copy2Q1(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(40);
						ShiftRight();
					}
					break;					
				case 4:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftLeft();
						ShiftDown();
					}
					break;
				case 5:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftRight();
						ShiftDown();
					}
					break;
				case 6:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftLeft();
						ShiftUp();
					}
					break;
				case 7:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftRight();
						ShiftUp();
					}
					break;
			}					
		}
	}
}
void DisplayChar(u8 ms)
{	_tb0on=1; Delayms(ms);							//Satrt TB0 & Delay 50ms					
	while(ScanCode!=1);								//等待完整Frame掃描完成
	_tb0on=0; DotPort=0x00;							//Stop TB0
}
void Copy2Q3(const u8 *cptr)
{	u8 i;
	for(i=0;i<8;i++) Buffer[i+8]=*cptr++;			//Copy Pattern to Buffer[8]~Buffer[15](Bit7:0])
}
void Copy2Q1(const u8 *cptr)
{	u8 i;
	for(i=0;i<8;i++)
	{	Buffer[i]&=0x00FF;
		Buffer[i]|=(((u16)*cptr++)<<8);				//Copy Pattern to Buffer[7]~Buffer[0](Bit15:8])
	}
}
void Copy2Q2(const u8 *cptr)
{	u8 i;
	for(i=0;i<8;i++)
	{	Buffer[i+8]&=0x00FF;
		Buffer[i+8]|=(((u16)*cptr++)<<8);			//Copy Pattern to Buffer[7]~Buffer[0](Bit15:8])
	}
}
void ShiftUp(void)
{	u8 i; u16 temp;	
	ptr=Buffer;										//Initial Pointer
	temp=*ptr;										//Backup Buffer[0]
	for(i=0;i<15;i++) {*ptr=*(ptr+1); ptr++;}		//Buffer Shift
	*ptr=temp;										//Reload temp to Buffer[15]
}
void ShiftDown(void)
{	u8 i; u16 temp;	
	ptr=Buffer+15;									//Initial Pointer
	temp=*ptr;										//Backup Buffer[0]
	for(i=0;i<15;i++) {*ptr=*(ptr-1); ptr--;}		//Buffer Shift
	*ptr=temp;										//Reload temp to Buffer[0]
}
void ShiftRight(void)
{	u8 i; bit msb;	
	ptr=Buffer;										//Initial Pointer
	for(i=0;i<16;i++)
	{	msb=(*ptr&(1<<15))? 1: 0 ;					//Get MSB
		*ptr<<=1; 									//Buffer Shift
		if(msb) *ptr|=(1<<0);						//MSB Shift to LSB
		ptr++;
	}										
}
void ShiftLeft(void)
{	u8 i; bit lsb;	
	ptr=Buffer;										//Initial Pointer
	for(i=0;i<16;i++)
	{	lsb=(*ptr&(1<<0))? 1: 0 ;					//Get LSB
		*ptr>>=1; 									//Buffer Shift
		if(lsb) *ptr|=(1<<15);						//LSB Shift to MSB
		ptr++;
	}										
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0;										//清除DotPort
	ScanPort=ScanCode; DotPort=*ptr++;				//切換掃描與資料，同時進行指標遞增
	GCC_RL(ScanCode);								//更新掃描碼
	if(ScanCode==0b00000001) ptr=Buffer;			//若已掃完八行重新設定指標	
}
DEFINE_ISR(ISR_ExtInt0,0x04)
{	_int0e=0;										//Disable INT0	
	_emi=1;											//Enable Nest Interrupt
	if(++index>7) index=0;	
	GCC_DELAY(250000);								//125ms
	GCC_DELAY(250000);								//125ms
	_int0f=0;										//Avoid Bouncing!
	_int0e=1;
}

void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}