// PROGRAM	: U4_2_2.c					       	2017.0505
// FUNCTION	: NEC IR Decoder Demo Program		By Steven
#include <HT66F2390.h>
#include "MyType.H"
#define	pLCMEN		_pe2	
#define	pLCMRW		_pe1	
#define	pLCMRS		_pe0	
#define	pLCMENC		_pec2	
#define	pLCMRWC		_pec1	
#define	pLCMRSC		_pec0	
#define	LCMData		_pg
#define	LCMDataC	_pgc
#define	IR_Pin	_pb3	
u8 IRDecoder(u16*,u16*);
void LCMInit(void);
u8 LCMWrite(_Bool, u8);
void Delayms(u16);
void Display(u16*);
const u8 STR1[]={"CUS. ID:"};						//字串建表
const u8 STR2[]={"Command:"};						//字串建表
void main()
{	u16 adrs, cmd; u8 state,i;
	_wdtc=0b10101111;								//關閉看門狗計時器
	_stm2c0=0; _stm2c1=0b00110001;					//STM2:比對吻合輸出模式,CCRA吻合清除
	_stm2al=500&0xFF; _stm2ah=500>>8;				//設定比對吻合週期=250us
	_pds1=0x20;										//設定PD6為STP2功能
	_sledc1=0xC0;									//設置PD[6:4]源流為Level 3
	_ptm2c0=0b00000000;								//fINT=fSYS(8MHz)/4 (0.5us)
	_ptp2ips=1;										//PTP2I==>PB3
	LCMInit();
	LCMWrite(0,0x80); i=0;							//第一列
	while(STR1[i]!=0) LCMWrite(1,STR1[i++]);		//顯示STR1[]字串
	LCMWrite(0,0xC0);i=0;							//第二列
	while(STR2[i]!=0) LCMWrite(1,STR2[i++]);		//顯示STR2[]字串
	while(1)
	{	state=IRDecoder(&adrs,&cmd);				//讀取IR信號
		switch (state)
		{	case 0: 
				LCMWrite(0,0xCF); LCMWrite(1,'.');	//非NEC格式
				break;
			case 1:
				LCMWrite(0,0x8F); LCMWrite(1,'R');	//重複碼(Repeat Code)
				break;	
			case 2:
				LCMWrite(0,0x89); Display(&adrs);	//第一列，顯示ID
				LCMWrite(0,0xC9); Display(&cmd);	//第二列，顯示命令
				break;
		}	
		_st2on=1; Delayms(30); _st2on=0; Delayms(20);//輸出2KHz方波並維持30ms
		_st2on=1; Delayms(60); _st2on=0; Delayms(20);//輸出2KHz方波並維持60ms
		LCMWrite(0,0x8F); LCMWrite(1,' ');
		LCMWrite(0,0xCF); LCMWrite(1,' ');
	}
}
void Display(u16* ptr)
{	u16	x=0xF000;
	u8 tmp,i=3;
	do
	{	tmp=(*ptr & x)>>(4*i--);					//取得4-Bit
		tmp=(tmp>9)? tmp+'7': tmp+'0';				//轉換為ASCII Code
		LCMWrite(1,tmp);							//LCM顯示	
	} while((x>>=4)!=0);							//下4-Bit
}		
u8 IRDecoder(u16 *ptradrs,u16 *ptrcmd)
{	u32 temp=0,temp1=1;
	u16 TCnt;										//Time Tick Counter, Address
	_ptm2c1=0b01000000;								//輸入捕捉模式(正緣)
	_ptm2rpl=(u8)20000; _ptm2rph=20000>>8;			//20000*fINT=10ms(計數最大限制)
	_ptm2pf=0; _ptm2af=0;							//清除PTM2AF、PTM2PF旗標
	while(IR_Pin);									//等待Start Bit
	_pt2on=1;										//開始計數
	while(!_ptm2af)									//等待STRAT信號結束
	{	if(_ptm2pf) {_pt2on=0;	return 0; }			//若超過最大計數限制，回傳0
	}
	_pt2on=0; _ptm2af=0; _ptm2pf=0;  				//停止PTM2, 清除PTM2AF、PTM2PF
	TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;			//取得START信號之時間長度
	if(TCnt<16000) return 0;						//若Start<8ms，回傳0
	_ptm2c1=0b01010000;								//輸入捕捉模式(負緣)
	_ptm2rpl=(u8)10000; _ptm2rph=10000>>8;			//9600*fINT=5ms(計數最大限制)
	_pt2on=1; 
	while(!_ptm2af)									//等待SYNC信號結束
	{	if(_ptm2pf) {_pt2on=0;	return 0; }			//若超過最大計數限制，回傳0
	}
	_pt2on=0; _ptm2af=0; _ptm2pf=0; 				//停止PTM2, 清除PTM2AF
	TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;			//取得SYNC信號之時間長度
	if(TCnt<4000) return 0; 						//若SYNC<2.0ms回傳0
	if(TCnt<5000) return 1;							//若2ms<SYNC<2.5ms為重複碼，回傳1
	while(temp1!=0)									//接收資料位元
	{	_pt2on=1;									//啟動計數
		while(!_ptm2af);							//等待位元時間結束;
		TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;		//取得位元時間
		_pt2on=0; _ptm2af=0;						//停止PTM2, 清除PTM2AF
		if(TCnt>3375) temp|=temp1;					//若位元時間>1.6875ms,則位元為1 
		temp1<<=1; 
	}	 
	_pt2on=0; 										//停止PTM2 
	*ptradrs=(u16)temp;								//取得Custom Code
	*ptrcmd=temp>>16; 								//取得Command
	return 2;										//正確，回傳2
}
void LCMInit(void)
{	pLCMEN=0; pLCMRW=0; pLCMRS=0;	        		//設定EN/RW/RS腳位為低電位
	pLCMENC=0; pLCMRWC=0; pLCMRSC=0;	  			//設定EN/RW/RS腳位為輸出模式
	Delayms(40);									//LCM Power-On Time
	LCMWrite(0,0x38);								//功能設定:8-Bit, 2-Line, 5*7
	LCMWrite(0,0x0C);								//顯示控制:Display on, No Cursor
	LCMWrite(0,0x06);								//進入模式:Increse, Not Shift
	LCMWrite(0,0x01);								//清除LCM
}
u8 LCMWrite(_Bool fgCD,u8 CD)
{	u8 BusyAC;
	LCMDataC=0b11111111;							//規劃Port為輸入模式
	pLCMRS=0; pLCMRW=1;								//RS=0,RW=1 (Read IR)
	GCC_NOP(); 										//tAS
	do
	{	pLCMEN=1; GCC_NOP();						//EN=1,tDDR
		BusyAC=LCMData;								//讀取LCM IR
		pLCMEN=0;									//EN=0	
	} while (BusyAC & 1<<7);						//若LCM忙碌,再次讀取
	LCMDataC=0;										//規劃Port為輸出模式
	pLCMRW=0;										//RW=0 (Write)
	pLCMRS=fgCD;									//依fgCD值設置 RS腳位狀態
	LCMData=CD;										//送出資料或命令
	pLCMEN=1; GCC_NOP(); pLCMEN=0; 					//EN=1,tPW,EN=0
	return BusyAC;									//回傳Address Counter
}
void Delayms(u16 del)
{	u16 i;											//@fSYS=8MH,延遲del*1ms
	for(i=0;i<del;i++) GCC_DELAY(2000);
}