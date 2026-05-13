// PROGRAM	: U3_2.c										2017.0427
// FUNCTION	: Dot Matrix LED with Source Current Control 	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	 DotPort	_pg									//Connect to ESK-200 PD
#define  DotPortC	_pgc
#define	 ScanPort	_pf									//Connect to ESK-200 PE
#define	 ScanPortC	_pfc
void Delayms(u16);
const u8 TabStop[8] ={0x18,0x18,0x3C,0x5A,0x5A,0x24,0x24,0x66};
const u8 TabWalk1[8]={0x3C,0x1C,0x08,0x0C,0x1A,0x28,0x14,0x14};
const u8 TabWalk2[8]={0x78,0x38,0x10,0x3E,0x4B,0xC8,0x16,0x63};
const u8 TabWalk3[8]={0x78,0x38,0x10,0x18,0x18,0x18,0x18,0x38};		  	 
const u8 TabWalk4[8]={0x78,0x38,0x10,0x18,0x2C,0x28,0x14,0x14};
const u8 TabWalk5[8]={0x3C,0x1C,0x08,0x3C,0x6A,0x4B,0x34,0x22};
volatile u8 ScanCode;
const u8 *ptr,*ptrbk;									//指標變數宣告
void main()
{	u8 i,j,TabIndex;
	_wdtc=0b10101111;									//關閉看們狗計時器
	ScanPort=0; ScanPortC=0;							//規劃ScanPort為輸出屬性並清除
	DotPort=0; DotPortC=0;								//規劃DotPort為輸出屬性並清除
	_psc0r=0x01; _tb0c=0x04; _tb0e=1;					//fPSC0=fSYS/4,週期=8192*(1/fPSC0),致能TB0中斷
	_emi=1;												//致能EMI	
	ScanCode=0b00000001;								//ScanCode初值設定
	while(1)
	{	ptrbk=TabStop; ptr=TabStop;						//指標變數指向TabStop[]起始位址				
		_tb0on=1;										//啟動TB0計數
		for(i=0;i<30;i++)
		{	Delayms(300);								//延遲0.3 Sec
			_sledc2^=0xF0; _sledc3^=0x0F;				//PG, PF源流 Level 0/3切換
		}
		_tb0on=0; DotPort=0;							//暫停TB0計數
		for(j=0;j<20;j++)
		{	TabIndex=0;									//TabIndex初值設定
			while(TabIndex++ < 6)						//是否TabIndex<6 ?
			{	switch(TabIndex)						//根據TabIndex內容將ptrbk指向各陣列起始位址
				{	case 1:	ptrbk=TabWalk1;				//ptrbk指向TabWalk1陣列起始位址
							break;
					case 2:	ptrbk=TabWalk2;				//ptrbk指向TabWalk2陣列起始位址
							break;
					case 3:	ptrbk=TabWalk3;				//ptrbk指向TabWalk3陣列起始位址
							break;
					case 4:	ptrbk=TabWalk4;				//ptrbk指向TabWalk4陣列起始位址
							break;
					case 5:	ptrbk=TabWalk5;				//ptrbk指向TabWalk5陣列起始位址
							break;
				}		
				ptr=ptrbk; ScanCode=0b00000001;			//ptr指向陣列起始位址並設定ScanCode初值
				if(j<10) i=150; else i=60;
				_tb0on=1; Delayms(i);					//啟動TB0計數並延遲 i ms
				_tb0on=0; DotPort=0;					//暫停TB0計數並清除DotPort
			}			
		}
	}
}
DEFINE_ISR(ISR_TB0,0x24)
{	DotPort=0;											//清除DotPort
	ScanPort=ScanCode; DotPort=*ptr++;					//切換掃描與資料，同時進行指標遞增
	GCC_RL(ScanCode);									//更新掃描碼
	if(ScanCode==0b00000001) ptr=ptrbk;					//若已掃完八行重新設定指標	
}
void Delayms(u16 del)
{	u16 i;												//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}