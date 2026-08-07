// PROGRAM	: U6_4_2.c								2017.0526
// FUNCTION	: I2C Slave Mode/Wake-up Control Demo 	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define  SEGPort	_pg
#define  SEGPortC	_pgc
#define	 SCLC		_pfc3
#define	 SDAC		_pfc2
#define	 SCL		_pf3
#define	 SDA		_pf2
#define	 SCLPU		_pfpu3
#define	 SDAPU		_pfpu2
#define	 SlaveID	0x1F					//Slave裝置ID
void Delayms(u16);	
volatile bit RxFlag;
volatile u8 RxData;
void main()
{	u8 count; 	
	_wdtc=0b10101111;						//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;					//清除Port並規劃為輸出屬性
	SCLPU=1; SDAPU=1;						//致能提升電阻
	_fhiden=0; _fsiden=0;					//HALT後，進入SLEEP模式	
	_ifs2=0b00110000;						//PF2->SDA,PF3->SCK
	_pfs0=0b10100000;						//PF2->SDA,PF3->SCL
	_sima=SlaveID<<1;						//設置Slave ID
	_simc0=0b11000000;						//選定SIM為I2C Slave Mode
	_simf=0; _mf3f=0; _mf3e=1; _sime=1; 	//清除旗標並致能SIM中斷
	_simen=1; _emi=1;						//致能SIM功能及EMI
	while(1)
	{	RxFlag=0;							//清除RxFlag旗標	
		count=0; SEGPort=0b00000001;		//點亮七段LED A節段
		while(1)
		{	Delayms(100);					//延遲100ms
			if(RxFlag) break;				//若接收到資料則跳離迴圈
			if(count++>50)					//是否已達5秒未收到資料?
			{	SEGPort=0;					//是，熄滅七段LED
			 	_simf=0; _mf3f=0; 			//清除中斷旗標
			 	_iamwu=1;					//致能Address Match Wake-up	
			 	GCC_HALT();					//進入SLEEP模式
			 	_iamwu=0;					//禁能Address Match Wake-up	
				while(!RxFlag);				//喚醒時等待資料接收完成					
			 	break;						//跳離迴圈
			}
			if(SEGPort&(1<<5)) SEGPort=1;	//若F節段已亮重新由A節段亮起
			else GCC_RL(SEGPort);			//否則亮下一節段
		}
		SEGPort=RxData; Delayms(1000);  	//顯示接收資料並延遲1.0秒
	}	
}
DEFINE_ISR(ISR_ISM,0x2C)					//MF3 ISR
{	static u8 TxData=1; 
	if(_haas)								//是否為位址吻合引發之中斷?
	{	if(_srw)							//是，Master是否要讀取資料?
		{	_htx=1; 						//是，設置為傳送模式
			_simd=TxData++;					//載入資料並加一
		}
		else								//否
		{	_htx=0; _txak=0;				//設置為接收模式並回應ACK
		 	_simd|=1;						//Dummy Read
		}											
	}
	else									//否，中斷是因傳送或接收完成所引起
 	{	if(_htx)							//是否為傳送或接收完成所引起?
		{	if(_rxak)						//是，是否Master要繼續讀資料?
			{	_htx=0; _txak=0;			//否，設置為接收模式並回應ACK
		 		_simd|=1;					//Dummy Read
			}
			else _simd=TxData++;			//Master要繼續讀資料，繼續送出資料並加一
		}
		else								//中斷是因接收完成所引起
		{	RxData=_simd; RxFlag=1;			//取得資料並設置RxFlag旗標
		}
	}
	if(TxData>9) TxData=0;					//若TxData>9則歸零
	_simf=0;								//清除SIMF(注意：此為共享型中斷)
}
void Delayms(u16 del)						//@fSYS=8MH,延遲del*ms				
{	u16 i;							
	for(i=0;i<del;i++) GCC_DELAY(2000);		//延遲del*2000指令週期			
}