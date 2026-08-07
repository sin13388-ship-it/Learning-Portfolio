// PROGRAM	: U7_2.c							2020.0526
// FUNCTION	: UART Data Receive Demo Program 	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	fH		8000000							//MCU HIRC Frequency
#define BR		19200							//Baud Rate(Must Match with HC-05)

#if BR>38400 && fH!=11059200
#error Baud Rate Error !!!
#warning "BR Exceed 38400, must use 11.059MHz HXT as fH to Reduce Baud Rate Deviation."
#endif

enum {Red=1, Green, Blue, Alpha};				//常數定義
void main()
{	u16 temp;
	u8 index,rR=0,rG=0,rB=0,rA=128;
	_wdtc=0b10101111;							//關閉看門狗計時器
#if BR>38400									//當BR>38400,需啟用外部11.059MHz的HXT
	_pbs1=0xF0; _hxtm=1;						//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);					//致能HXT並等待穩定
#endif											//注意ESK303 OSC1/2 Jumper之設定

	_pas1=0b00110000;							//設置RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b01100000;							///RXEN0/BRGH0////	
	_brg0=fH/((u32)16*BR)-1;					//BRGH0=1
	
	_pds0=0x12; _pds1=0x02;						//PD0->STP1(R),PD2->PTP2(G),PD4->PTP3(B)
	_stm1al=0; _stm1ah=0;						//Duty=0	
	_stm1rp=0;									//PWM 週期=65536/fINT
	_stm1c0=0b00011000;							//fINT=fSYS(8MHz),ST1ON=1
	_stm1c1=0b10101000;							//PWM模式,Active High,STM1RP控制週期
	_ptm2al=0; _ptm2ah=0;						//Duty=0
	_ptm2rpl=0; _ptm2rph=0;						//PWM 週期=65536/fINT
	_ptm2c0=0b00011000;							//fINT=fSYS(8MHz),PT2ON=1
	_ptm2c1=0b10101000;							//PWM模式, Active High
	_ptm3al=0; _ptm3ah=0;						//Duty=0
	_ptm3rpl=0; _ptm3rph=0;						//PWM 週期=65536/fINT
	_ptm3c0=0b00011000;							//fINT=fSYS(8MHz),PT3ON=1
	_ptm3c1=0b10101000;							//PWM模式, Active High
	while(1)
	{	while(!_rxif0);							//等待UR接收到資料
		index=_txr_rxr0;						//取得接收資料
		switch(index)
		{	case Red:
				while(!_rxif0);  				//等待色彩資料
				rR=_txr_rxr0;					//取得接收資料
				temp=(u16)rR*rA;				//結合顏色及亮度	
				_stm1al=temp; _stm1ah=temp>>8;	//Update Duty(R)
				break;
			case Green:
				while(!_rxif0);  				//等待色彩資料
				rG=_txr_rxr0;					//取得接收資料
				temp=(u16)rG*rA;;				//結合顏色及亮度
				_ptm2al=temp; _ptm2ah=temp>>8;	//Update Duty(G)
				break;
			case Blue:
				while(!_rxif0);  				//等待色彩資料
				rB=_txr_rxr0;					//取得接收資料
				temp=(u16)rB*rA;;				//結合顏色及亮度
				_ptm3al=temp; _ptm3ah=temp>>8;	//Update Duty(B)
				break;
			case Alpha:
				while(!_rxif0);					//等待亮度資料
				rA=_txr_rxr0;					//取得接收資料
				temp=(u16)rR*rA;;				//結合顏色及亮度
				_stm1al=temp; _stm1ah=temp>>8;	//Update Duty(R)
				temp=(u16)rG*rA;;				//結合顏色及亮度
				_ptm2al=temp; _ptm2ah=temp>>8;	//Update Duty(G)
				temp=(u16)rB*rA;;				//結合顏色及亮度
				_ptm3al=temp; _ptm3ah=temp>>8;	//Update Duty(B)
				break;
		}				
	}
}