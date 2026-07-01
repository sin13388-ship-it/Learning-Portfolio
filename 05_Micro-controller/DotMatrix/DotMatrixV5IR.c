// PROGRAM	: DotMatrixV5IR.c							2019.1206
// FUNCTION	: 8*8 Dot Matrix LED Dynamic Control 		By Steven
//			: Use NEC_IR Controller to Change Shift Direction
//			: PB3 -> NEC IR  
#include <HT66F2390.h>
#include "DotMatrix.H"
#include "MyType.H"
#include "MatrixFont.H"
volatile u8 ScanCode;
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
volatile u8 state=255;
volatile u16 adrs,cmd;
void main()
{	const u8 *pstr;
	u8 i;u16 index=0;
	_wdtc=0b10101111;								//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;						//Config ScanPort as O/P
	DotPort=0; DotPortC=0;							//Config DotPort as O/P
	_psc0r=0x01; _tb0c=0x04; _tb0e=1;				//fPSC0=fSYS/4,週期=4096*(1/fPSC0),致能TB0中斷
	ptr=Buffer; ScanCode=0b00000001;				//Initila Pointer and ScanCode
	_ptm2c0=0b00001000;								//fINT=fSYS(8MHz)/4 (0.5us),PT2ON=1
	_ptm2c1=0b01010000;								//輸入捕捉模式(負緣)
	_ptp2ips=1;	_pbpu3=1;							//PTP2I==>PB3
	_ptm2af=0; _mf2f=0;	_ptm2ae=1; _mf2e=1;			//致能PTM2AE
	_emi=1;											//致能EMI
 	while(1)
	{	for(i=0;i<16;i++) Buffer[i]=0;				//清除Buffer
		pstr=string;
		while(*pstr!=0)
		{	if(state==2 && adrs==CID) index=cmd;
			/*switch(cmd)	 						//若保留此段程式，按未定義的按鍵將不影響字型的移動；
				{	case LED0:						//註解此段，則按未定義的按鍵將停止顯示！	
					case LED1:
					case LED2:
					case LED3:
					case LED0_:
					case LED1_:
					case LED2_:
					case LED3_:	index=cmd;
				}
			*/
			if(state!=255)
			{	state=255; _ptm2af=0; 
				_ptm2ae=1; _pt2on=1;				//重新啟動捕捉	
			}
			switch (index)
			{	case LED0:	
					Copy2Q3(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer
						DisplayChar(40);
						ShiftDown();
					}
					break;
				case LED0_:	
					Copy2Q3(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer
						DisplayChar(40);
						ShiftUp();
					}
					break;		
				case LED1: 
					Copy2Q1(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(40);
						ShiftLeft();
					}
					break;
				case LED1_: 
					Copy2Q1(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(40);
						ShiftRight();
					}
					break;					
				case LED2:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftLeft();
						ShiftDown();
					}
					break;
				case LED2_:	
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftRight();
						ShiftDown();
					}
					break;
				case LED3:
					Copy2Q2(&font[*pstr-' '][0]);	//複製字型
					pstr++;							//指向下一個字
					for(i=0;i<8;i++)
					{	ptr=Buffer;					//Initial Pointer			
						DisplayChar(50);
						ShiftLeft();
						ShiftUp();
					}
					break;
				case LED3_:	
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
DEFINE_ISR(PTM2A,0x20)
{	u32 temp=0,temp1=1; u16 TCnt;					//Time Tick Counter, Address
	_ptm2ae=0; _pt2on=0;							//禁能PTM2A中斷清除PTM2D
	_emi=1;											//允許Nest Interrupt
	_ptm2pf=0; _ptm2af=0;							//清除PTM2AF、PTM2PF旗標
	_ptm2c1=0b01000000;								//輸入捕捉模式(正緣)
	_pt2on=1;										//開始計數
	_ptm2rpl=(u8)20000; _ptm2rph=20000>>8;			//20000*fINT=10ms(計數最大限制)
	while(!_ptm2af)									//等待STRAT信號結束
	{	if(_ptm2pf)
		{	state=0;								//若超過最大計數限制，回傳0
			_ptm2c1=0b01010000; return;				//恢復負緣輸入捕捉模式
		}		
	}
	_pt2on=0; _ptm2af=0; _ptm2pf=0;  				//停止PTM2(清除PTM2D), 清除PTM2AFF、PTM2PF
	TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;			//取得START信號之時間長度
	if(TCnt<16000)
	{	state=0; 									//若Start<8ms，回傳0
		_ptm2c1=0b01010000; return;					//恢復負緣輸入捕捉模式
	}			
	_ptm2c1=0b01010000;								//輸入捕捉模式(負緣)
	_ptm2rpl=(u8)9600; _ptm0rph=9600>>8;			//9600*fINT=4.8ms(計數最大限制)
	_pt2on=1; 
	while(!_ptm2af)									//等待SYNC信號結束
	{	if(_ptm2pf) { state=0; return;}				//若超過最大計數限制，回傳0
	}
	_pt2on=0; _ptm2af=0; 			 				//停止PTM2(清除PTM2D), 清除PTM2AF
	TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;			//取得SYNC信號之時間長度
	if(TCnt<4000) { state=0; return;}				//若SYNC<2.0ms回傳0
	if(TCnt<6000) { state=1; return;}				//若2ms<SYNC<3ms為重複碼，回傳1
	while(temp1!=0)									//接收資料位元
	{	_pt2on=1;									//啟動計數
		while(!_ptm2af);							//等待位元時間結束;
		TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;		//取得位元時間
		_pt2on=0; _ptm2af=0;						//停止PTM2(清除PTM2D), 清除PTM2AF
		if(TCnt>3000) temp=temp|temp1;				//若位元時間>1500us,則位元為1 
		temp1<<=1; 
	}	 
	adrs=(u16)temp;									//取得Custom Code
	cmd=temp>>16; 									//取得Command
	state=2; 										//正確START_SYNC，回傳2
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}