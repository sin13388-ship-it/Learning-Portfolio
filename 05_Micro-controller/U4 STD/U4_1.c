// PROGRAM	: U4_1.c								2017.0428
// FUNCTION	: STM T/C Mode Int. Control with KeyPad	By Steven       
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort		_pg
#define	SEGPortC	_pgc
#define KeyPort		_pc
#define KeyPortC	_pcc
#define KeyPortPU	_pcpu
#define	pSPK		_pd6
#define	pSPKC		_pdc6
#define fSYS   8000000								//fSYS=8MHz
const u8 SEG_TAB[] = { 0x3F,0x06,					//7-Segment Table(0~F)
		0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
		0x67,0x77,0x7C,0x58,0x5E,0x79,0x71};
		
const u16 Pitch_TAB[] = {			      			//音調常數建表區
		
		//half period =1/2*taget
		//counts =half period/clock
		   fSYS/(523*2*4),fSYS/(587*2*4),fSYS/(659*2*4),
		   fSYS/(698*2*4),fSYS/(785*2*4),fSYS/(880*2*4),
		   fSYS/(998*2*4),fSYS/(523*4*4),fSYS/(587*4*4),
		   fSYS/(659*4*4),fSYS/(698*4*4),fSYS/(785*4*4),
		   fSYS/(880*4*4),fSYS/(998*4*4),fSYS/(523*8*4),
		   fSYS/(587*8*4)};
void Delayms(u16);		
u8 ScanKey(void);
void main()
{	u8 Key;
	_wdtc=0b10101111;								//關閉看們狗計時器
	SEGPort=0; SEGPortC=0;							//清除SEGPort並規劃為輸出屬性	
	pSPKC=0;						            	//規劃pSPK為輸出屬性
	_sledc1=0xc0;									//設置PD[6:4]源流為Level 3
	_stm2c0=0; _stm2c1=0b11000001;                 	//STM2相關控制暫存器規劃
													//stm2c0: 繼續計數，clock fsys/4, PTMon=off
													//stm2c1: Timer/Counter mode, pwm dont care, A match clear	
	_stm2ae=1; _mf4e=1; _emi=1;						//致能ST2A中斷,EMI總開關
 	while(1)
	{	SEGPort=1<<7;								//點亮七段顯示器h節段，其餘節段熄滅
		do
		{ 	Key=ScanKey();
			GCC_DELAY(200000);  					//延遲 100ms
			SEGPort^=(1<<7);						//七段顯示器h節段亮滅切換
		} while(Key==16);	   						//等待按壓按鍵
		SEGPort=SEG_TAB[Key];				      	//查表並顯示按鍵值
		
		_stm2al=Pitch_TAB[Key];		         		//取得計數時間常數     
		_stm2ah=Pitch_TAB[Key]>>8; 
		
		_st2on=1; Delayms(400);						//啟動STM2計數並延遲400mS	
		_st2on=0; 									//停止STM2計數
	}
}
DEFINE_ISR(ISR_STM2,0x38)
{	pSPK=!pSPK;								   		//pSPK狀態反向一次
	_stm2af=0;										//清除STM2AF
}
u8 ScanKey()
{	u8 i,key=0;
	KeyPortC=0xF0; KeyPortPU=0xF0;			   		//規劃KeyPort[7:4]/[3:0]為輸入/輸出屬性，並致能KeyPort[7:4]提升電阻
	KeyPort=0b11111110;					         	//送出掃描碼KeyPort[3:0]=1110
	for(i=0;i<=3;i++)								//依序檢查四列
	{	if(!(KeyPort & 1<<4)) break;		      	//檢查第0行(KeyPort[4])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<5)) break;			   	//檢查第1行(KeyPort[5])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<6)) break;			   	//檢查第2行(KeyPort[6])是否按下
		key++;										//否，按鍵值+1
		if(!(KeyPort & 1<<7)) break;			   	//檢查第3行(KeyPort[7])是否按下
		key++;										//否，按鍵值+1
		KeyPort<<=1; KeyPort|=0b00000001;	   		//更新掃描碼，並確保KeyPort[3:0]只有一個位元為0
	}
	return key;	
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}