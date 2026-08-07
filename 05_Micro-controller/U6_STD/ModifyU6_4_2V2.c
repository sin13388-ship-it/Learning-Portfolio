// PROGRAM	: ModifyU6_4_2V2.c						2022.0904
// FUNCTION	: I2C Slave Mode/Wake-up Control Demo 	By Steven
// Library	: eDisplaV2y.c
#include <HT66F2390.h>
#include "MyType.H"
#include "eDisplayV2.H"
#define	 SlaveID	0x1F					//Slave裝置ID
#if (SlaveID>0x1F)
#error "Slave ID must Less Then 0x20 !!!"
#endif
volatile bit RxFlag;
volatile u8 RxData,	TxData=1;
void main()
{	u8 count; 	
	_wdtc=0b10101111;						//關閉看們狗計時器
	SCLPU=1; SDAPU=1;						//致能提升電阻
	_fhiden=0; _fsiden=0;					//HALT後，進入SLEEP模式	
	eDisplayReset();						//Reset eDisplay(含I2C_Init())
	eDisplayRet( 0,128, 0,128,Blue);		//繪製矩形區域
	eDisplayStr(32, 5,(u8*)"U6_4_2V2");
	eDisplayStr(28,25,(u8*)"IIC Slave");
	eDisplayStr(20,90,(u8*)"TRX. Cnt:0");
	_ifs2=0b00110000;						//PF2->SDA,PF3->SCK
	_pfs0=0b10100000;						//PF2->SDA,PF3->SCL
	_sima=SlaveID<<1;						//設置Slave ID
	_simc0=0b11000000;						//選定SIM為I2C Slave Mode
	_simf=0; _mf3f=0; _mf3e=1; _sime=1; 	//清除旗標並致能SIM中斷
	_simen=1; _emi=1;						//致能SIM功能及EMI
	while(1)
	{	RxFlag=0; count=0;					//清除RxFlag旗標與count
		while(1)
		{	Delayms(100);					//延遲100ms
			eDisplayStr(4,60,(u8*)"Wait for Data..");
			ForeColor=~ForeColor;
			if(RxFlag) break;				//若接收到資料則跳離迴圈
			if(count++>50)					//是否已達5秒未收到資料?
			{	eDisplayStr(4,60,(u8*)"Enter SLEEP...");
			 	_simf=0; _mf3f=0; 			//清除中斷旗標
			 	_iamwu=1;					//致能Address Match Wake-up	
			 	GCC_HALT();					//進入SLEEP模式
			 	_iamwu=0;					//禁能Address Match Wake-up	
				while(!RxFlag);				//喚醒時等待資料接收完成					
			 	break;						//跳離迴圈
			}
		}
		ForeColor=Yellow;
		eDisplayRet(4,124,60,14,BackColor);	//清除Wait for Data..字串
		eDisplayChar(60,60,_simd);			//顯示接收值(Master傳的是ASCII Char)
		eDisplayChar(92,90,TxData+'0');		//顯示已傳送字元數
		Delayms(1000);						//延遲一秒
	}	
}
DEFINE_ISR(IIC,0x2C)					//MF3 ISR
{	if(_haas)								//是否為位址吻合引發之中斷?
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
			else _simd=TxData++;			//Master要繼續讀資料，繼續送出資料並加一(傳0~9數值)
		}
		else								//中斷是因接收完成所引起
		{	RxData=_simd; RxFlag=1;			//取得資料並設置RxFlag旗標
		}
	}
	if(TxData>9) TxData=0;					//若TxData>9則歸零
	_simf=0;								//清除SIMF(注意：此為共享型中斷)
}
