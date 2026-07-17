// PROGRAM	: U4_2.c								2017.0428
// FUNCTION	: STM Compare Match O/P Mode Control   	By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	SEGPort		_pg
#define	SEGPortC	_pgc
#define KeyPort		_pc
#define KeyPortC	_pcc
#define KeyPortPU	_pcpu
//#define fSYS   8000000								//fSYS=8MHz
#define fSYS    11059200							
const u8 SEG_TAB[] = { 0x3F,0x06,					//7-Segment Table(0~F)
		0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
		0x67,0x77,0x7C,0x58,0x5E,0x79,0x71};
const u16 Pitch_TAB[] = {			      			//音調常數建表區
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

#if fSYS==11059200
	
	_pbs1=0xF0;										//Set PB6/PB7 as OSC1/2 Function
	_hxtm=1;										//Set Mode, ESK303 XTAL=11.059MHz>10MHz
	_hxten=1;										//Enable HXT
	while(!_hxtf);									//Wait Stable
	_fhs=1;											//Switch to HXT
	_hircen=0;										//Disable LIRC	
	
#endif
	
	SEGPort=0; SEGPortC=0;							//清除SEGPort並規劃為輸出屬性
	_ptm2c0=0; _ptm2c1=0b00110001;					//PTM2:比對吻合輸出模式,CCRA吻合清除
	_pds0=0x10;										//設定PD2為PTP2功能	
	_sledc1=0xC0;									//設置PD[6:4]源流為Level 3	
	while(1)
	{	SEGPort=1<<7;								//點亮七段顯示器h節段，其餘節段熄滅
		do
		{ 	Key=ScanKey();
			GCC_DELAY(200000);  					//延遲 100ms
			SEGPort^=(1<<7);						//七段顯示器h節段亮滅切換
		} while(Key==16);	   						//等待按壓按鍵
		SEGPort=SEG_TAB[Key];				      	//查表並顯示按鍵值

//		_ptm2al=Pitch_TAB[Key];		         		//取得計數時間常數
//		_ptm2ah=Pitch_TAB[Key]>>8;          

		_ptm2ah=Pitch_TAB[Key]>>8;          		//Write Hi-byte First
		_ptm2al=Pitch_TAB[Key];		         		//then write  Lo-byte !!!

		_pt2on=1;									//啟動STM2計數
		while (ScanKey()!=16);	                  	//等待按鍵釋放
		Delayms(300); _pt2on=0; 					//延遲300mS,停止計數
	}
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
{	u16 i;

	#if fSYS==11059200
		for(i=0;i<del;i++) GCC_DELAY(2000);				//@fSYS=8MH,延遲del*1ms
	#endif									
	
	for(i=0;i<del;i++) GCC_DELAY(fSYS/4000);		//@fSYS,延遲del*1ms
}	