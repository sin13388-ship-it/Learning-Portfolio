// PROGRAM	: U4_3_2.c								2017.0501
// FUNCTION	: STM PWM DAC Demo Program 				By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort			_pg
#define	SEGPortC		_pgc
#define	SW_FreqUpPU		_pcpu0	
#define	SW_FreqUp		_pc0	
#define	SW_FreqUpC		_pcc0	
#define	SW_FreqDownPU	_pcpu1		
#define	SW_FreqDown		_pc1	
#define	SW_FreqDownC	_pcc1	
#define	SW_WavePU		_pcpu2	
#define	SW_Wave			_pc2	
#define	SW_WaveC		_pcc2	
const u8 Sin_TAB[] = {								//SIN PWM常數建表區
		128,203,250,250,203,128, 53,  6,  6, 53};
const u8 Tri_TAB[] = {								//Triangle PWM常數建表區
		  0, 50,100,150,200,250,200,150,100, 50};
const u8* ptr=Sin_TAB;	  
bit fgWave=1;  
void Delayms(u16);									//函式原型宣告
void main()
{	u16 sample=512;								
	_wdtc=0b10101111;								//關閉看們狗計時器
	SW_FreqUpC=1; SW_FreqUpPU=1;			   		//規劃按鍵腳位為輸入屬性並啟用提升電阻
	SW_FreqDownC=1; SW_FreqDownPU=1;		   	
	SW_WaveC=1; SW_WavePU=1;		   	
	_pes0=0x08;										//PE1為STP0功能
	_stm0rp=1; 										//PWM 週期=256/fIN
	_stm0c0=0b00011000;								//fINT=fSYS(8MHz),起始STM0計數
	_stm0c1=0b10101000;								//PWM, Active High,STM0RP控制週期
	_stm2al=sample; _stm2ah=sample>>8; 				//設定取樣週期參數
	_stm2c0=0x18; _stm2c1=0b11000001;               //fINT=fSYS,計時/計數模式，A吻合清除
	_stm2ae=1; _mf4e=1; _emi=1;						//致能T2A中斷,EMI總開關
	while(1)
	{	Delayms(200);								//延遲200ms
		while(1)
		{	if(!SW_FreqUp)							//升頻鍵是否按下?
			{	sample-=32;							//是，取樣時間參數降低
				if(sample<128) sample=128;			//下限值偵測
				_stm2al=sample; _stm2ah=sample>>8; 	//設定取樣時間參數			
				break;   	
			}
			else if(!SW_FreqDown) 					//降頻鍵是否按下?
			{	sample+=32;							//是，取樣時間參數增加
				if(sample>2048) sample=2048;		//上限值偵測
				_stm2al=sample; _stm2ah=sample>>8;  //設定取樣時間參數				
				break;   	
			}
			else if(!SW_Wave) 						//波行切換是否按下?
			{	fgWave=!fgWave;						//是，旗標反態
				break;
			}
		}
	}
}
DEFINE_ISR(ISR_STM2,0x38)
{	static u8 index=0;
	_stm0al=*ptr++; _stm0ah=0;						//取得Duty參數
	if(++index>=10)									//表格範圍檢測
	{ 	index=0;									//若超過範圍則回到初值
		ptr=(fgWave)? Sin_TAB : Tri_TAB;			//取得建表資料起始位址
	}
	_stm2af=0;										//清除STM2AF
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}