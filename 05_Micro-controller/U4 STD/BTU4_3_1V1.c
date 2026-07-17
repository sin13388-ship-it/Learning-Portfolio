// PROGRAM	: BTU4_3_1V1.c 							2021.0526
// FUNCTION	: PTM PWM Motro Control with H-Bridge 	By Steven
//            BT with USB Fan Uni-direction Control 
//			  APP: Fans	
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort			_pg
#define	SEGPortC		_pgc
#define	fH		8000000								//MCU HIRC Frequency
#define BR		19200								//Baud Rate(Must Match with HC-05)
void Delayms(u16);									//函式原型宣告		 
void main()
{	volatile u16 pwm=0;		
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0; 							//規劃SEGPort為輸出屬性,並輸出0

	_pas1=0b00110000;								//設置RX0->PA6
	_u0cr1=0b10000000;								//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b01100000;								///RXEN0/BRGH0////	
	_brg0=fH/((u32)16*BR)-1;						//BRGH0=1

	_pb2=0; _pbc2=0; _pd4=0; _pdc4=0;				//規劃PB2/PD4為輸出屬性並輸出0
	_pbs0=0x30; _pds1=0x00;							//PB2為PTP3功能、PD4為I/O功能
	_sledc0=0x30;									//PB[3:0] Current Level 3
	_ptm3rpl=(u8)4608; _ptm3rph=4608>>8;			//PWM 週期=4608/fINT
	_ptm3c0=0b00111000;								//fINT=fSYS(8MHz)/64(8us),起始PTM3計數
	_ptm3c1=0b10101000;								//PWM Mode, Active High
	while(1)
	{	while(1)
		{	while(!_rxif0);							//等待UR接收到資料
			pwm=_txr_rxr0;							//取得接收資料
			pwm<<=8;
			while(!_rxif0);							//等待UR接收到資料
			pwm|=_txr_rxr0;
			if(pwm<=4608) break;
			while(!_rxif0);							//等待UR接收到資料
			pwm=_txr_rxr0;							//Dummy Read
		}
		SEGPort^=1<<6;
		_ptm3al=(u8)pwm; 							//取得佔空比參數
		_ptm3ah=pwm>>8;
	}
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}