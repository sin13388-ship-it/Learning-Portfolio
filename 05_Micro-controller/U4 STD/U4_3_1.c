// PROGRAM	: U4_3_1.c								2017.0501
// FUNCTION	: PTM PWM Motro Control with H-Bridge 	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort			_pg
#define	SEGPortC		_pgc
#define	SW_SpeedUpPU	_pcpu0	
#define	SW_SpeedUp		_pc0	
#define	SW_SpeedUpC		_pcc0	
#define	SW_SpeedDownPU	_pcpu1		
#define	SW_SpeedDown	_pc1	
#define	SW_SpeedDownC	_pcc1	
#define	SW_DirectionPU	_pcpu2	
#define	SW_Direction	_pc2	
#define	SW_DirectionC	_pcc2	
const u8 SEG_TAB[] = {0x3F,0x06,0x5B,0x4F,0x66,		//七段顯示碼建表區(共陰)
			 		  0x6D,0x7D,0x07,0x7F,0x67};
const u16 PWM_TAB[] = {0,512,1024,1536,2048,		//PWM常數建表區
			 		   2560,3072,3584,4096,4608};
void Delayms(u16);									//函式原型宣告		 
void main()
{	s8 Index=0;								
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0; 							//規劃SEGPort為輸出屬性,並輸出0
	SW_SpeedUpC=1; SW_SpeedUpPU=1;			   		//規劃按鍵腳位為輸入屬性並啟用提升電阻
	SW_SpeedDownC=1; SW_SpeedDownPU=1;		   	
	SW_DirectionC=1; SW_DirectionPU=1;		   	
	_pb2=0; _pbc2=0; _pd4=0; _pdc4=0;				//規劃PB2/PD4為輸出屬性並輸出0
	_pbs0=0x30; _pds1=0x00;							//PB2為PTP3功能、PD4為I/O功能
	_ptm3rpl=(u8)4608; _ptm3rph=4608>>8;			//PWM 週期=4608/fINT
	_ptm3c0=0b00111000;								//fINT=fSYS(8MHz)/64(8us),起始PTM3計數
	_ptm3c1=0b10101000;								//PWM Mode, Active High
	while(1)
	{	SEGPort=SEG_TAB[Index];
		if(_pds1==0x02) SEGPort|=1<<7;				//反轉時顯示dp節段
		_ptm3al=(u8)PWM_TAB[Index]; 				//取得佔空比參數
		_ptm3ah=PWM_TAB[Index]>>8;
		Delayms(250);								//延遲250ms
		while(1)
		{	if(!SW_SpeedUp)
			{	if(++Index>9) Index=9;				//若按下加速鍵,指標遞增(上限9) 
				break;   	
			}
			else if(!SW_SpeedDown) 					//若按下減速鍵,指標遞減(下限0) 
			{	if(--Index<0) Index=0;
				break;   	
			}
			else if(!SW_Direction)
			{	if(_pds1==0)						//是否為正轉?
				{	_pbs0=0x00; _pds1=0x02;			//是,PB2為I/O功能、PD4為PTP3功能
				}
				else								//否
				{	_pbs0=0x30; _pds1=0x00;			//PB2為PTP3功能、PD4為I/O功能
				}
				break;
			}
		}
	}
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}