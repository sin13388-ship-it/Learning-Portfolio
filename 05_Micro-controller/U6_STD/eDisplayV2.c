// PROPGRAM : e-Display.C 							2020.0326
// FUNCTION	: e-Display(I2C Interface) Library 		By Steven
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.h"

volatile u16 ForeColor=Yellow, BackColor=Blue;		//箇砞玡璉春肅︹20200325
volatile bit feDisplay5DigitNoSpace=0;				//箇砞陪ボ计玡ぇフ20200326

void eDisplayHex(u8 x, u8 y, u8 h)					//Font Size: 8x14	
{	u8 Buffer[8];
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=8;		//杆更㏑
	e_Command(Buffer);								//癳㏑搒
	Buffer[0]=x; Buffer[1]=y;						//杆更把计
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	Buffer[6]=((h>>4)<10)?(h>>4)+'0':(h>>4)+'7';
	Buffer[7]=((h&0x0F)<10)?(h&0x0F)+'0':(h&0x0F)+'7';
	e_DataRAM(Buffer,8);							//癳把计
	I2C_STOP();										//癳I2C STOP獺腹
}
void eDisplay5Digit(u8 x, u8 y,u16 data, u8 dp)		//20200326  ex: 123.45 (dp=3)
{	bit fLZ=1;										//dp=0 for no dp
	u8 i,ascii[]={0,0,0,0,0,0,0,0};
	u16 temp=10000;
	for(i=(dp==0)?1:0;i<6;i++)						//盢data锣传Θ计
	{	if(i==dp) 									//琌璶陪ボ计翴?
		{	ascii[i]='.';							//夹癘计翴竚 
			continue;
		}
		ascii[i]=data/temp; data%=temp;
		temp/=10;									//膀┏秸俱
	}	
	for(i=0;i<6;i++)								//盢计锣传ΘASCII┪フ(玡旧箂)
	{	if(dp!=0)									//琌Τ计翴?
		{	if(i==dp-1 && fLZ==1) 					//琌计翴玡计
			{	ascii[i]+='0';
				fLZ=0; 
				continue;
			}
			else if(i==dp) continue;				//玂痙计翴
		}
		if(fLZ==1 && ascii[i]==0) ascii[i]=' ';		//玡旧箂锣Θフ
		else
		{	fLZ=0;
			ascii[i]+='0';
		}
	}
	if(fLZ==1) ascii[5]='0';
	i=0;											//砞竚﹃癬﹍夹					
	if(feDisplay5DigitNoSpace)						//琌陪ボ计玡ぇフ
	{	while(1)									//计玡フ璝ぃ°		
		{	if(ascii[i]!=' ') break;
			i++;
		}
	}	
	eDisplayStr(x,y,&ascii[i]);
}
void eDisplayStr(u8 x, u8 y, u8 *ptr)				//Font Size: 8x14	
{	u8 i=6,Buffer[22];
	while(*ptr) {Buffer[i]=*ptr++;i++;};
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=i;		//杆更㏑
	e_Command(Buffer);								//癳㏑搒
	Buffer[0]=x; Buffer[1]=y;						//杆更把计
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	e_DataRAM(Buffer,i);							//癳把计
	I2C_STOP();										//癳I2C STOP獺腹
}
void eDisplayChar(u8 x, u8 y, u8 ch)				//Font Size: 8x14	
{	u8 Buffer[8];
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=7;		//杆更㏑
	e_Command(Buffer);								//癳㏑搒
	Buffer[0]=x; Buffer[1]=y;						//杆更把计
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	Buffer[6]=ch;
	e_DataRAM(Buffer,7);							//癳把计
	I2C_STOP();										//癳I2C STOP獺腹
}
void eDisplayDot(u8 x, u8 y, u16 color)
{	u8 Buffer[8]={cmdDOT,0,4,0,0,0,0,0};			//杆更㏑搒
	e_Command(Buffer);								//癳㏑搒
	Buffer[0]=x;									//杆更把计
	Buffer[1]=y;
	Buffer[2]=color>>8;	Buffer[3]=(u8)color;	
	e_DataRAM(Buffer,4);							//癳把计
	I2C_STOP();										//癳I2C STOP獺腹 
}
void eDisplayRet(u8 x, u8 xSize,u8 y, u8 ySize, u16 color)
{	u8 Buffer[8]={cmdRET,0,6,0,0,0,0,0};			//杆更㏑搒
	e_Command(Buffer);								//癳㏑搒
	Buffer[0]=x; Buffer[1]=xSize;					//杆更把计
	Buffer[2]=y; Buffer[3]=ySize;
	Buffer[4]=color>>8;	Buffer[5]=(u8)color;	
	e_DataRAM(Buffer,6);							//癳把计
	I2C_STOP();										//癳I2C STOP獺腹
}
void eDisplayPic(u8 x,u8 xSize, u8 y, u8 ySize, const u16* pptr)
{	u16 i;
	u8 Buffer[8]={cmdPIC,0,4,0,0,0,0,0};			//杆更㏑搒
	e_Command(Buffer);								//癳㏑
	Buffer[0]=x; Buffer[1]=xSize;					//杆更把计
	Buffer[2]=y; Buffer[3]=ySize;	
	e_DataRAM(Buffer,4);							//癳把计
	for(i=0;i<(xSize*ySize);i++)
	{	WriteByte(*pptr>>8); CheckACK();			//癳Hi-Byte单莱ACK
		WriteByte((u8)*pptr++); CheckACK();			//癳Lo-Byte单莱ACK
	}
	I2C_STOP();										//癳I2C STOP獺腹
}
void eDisplayClear(u8 x,u8 xSize,u8 y,u8 ySize)
{	u8 Buffer[8]={cmdCLR,0,4,0,0,0,0,0};			//杆更㏑搒
	e_Command(Buffer);								//癳e-Display睲埃㏑
	Buffer[0]=x; Buffer[1]=xSize;					//杆更把计
	Buffer[2]=y; Buffer[3]=ySize;
	e_DataRAM(Buffer,4);							//癳x/y畒夹癬翴の
	I2C_STOP();										//癳I2C STOP獺腹 
}
void eDisplayReset(void)							//Reset EDisplay and Initila SCL,SDA
{	peReset=0;  peResetC=0;
	Init_I2C();
	Delayms(1);
	peReset=1;
	Delayms(2800);
}
void e_Command(u8* ptr)
{	u8 i;
	//while(e_Read()==eBUSY); 						//浪琩e-DisplayΓ窵篈	
	e_Read();
	I2C_START();									//浪琩单e-Display挡Γ窵篈 !!!20211125穝	
	WriteByte(DeviceID|0); CheckACK();				//癳DeviceID_W单莱ACK
	for(i=0;i<8;i++)								//e-Display㏑㏕﹚8
	{	WriteByte(*ptr++); CheckACK();				//硋Byte癳㏑单莱ACK
	}
}
void e_DataRAM(u8* ptr,u8 Length)
{	u8 i;
	for(i=0;i<Length;i++)
	{	WriteByte(*ptr++); CheckACK();				//硋Byte癳RAM戈单莱ACK
	}
}
u8 e_Read(void)
{	u8 retval;
//	I2C_START();									//癳I2C START獺腹  
//	WriteByte(DeviceID|1); CheckACK();				//癳杆竚ID单莱ACK獺腹 
//	retval=ReadByte();								//弄杆竚肚麲
//	SendACK(1);										//癳NO_ACK獺腹
//	I2C_STOP();										//癳I2C STOP獺腹

	I2C_START();									//癳I2C START獺腹 
	WriteByte(DeviceID|1); CheckACK();				//癳杆竚ID单莱ACK獺腹 
	while(1)
	{	retval=ReadByte();							//弄杆竚肚麲
		if(retval!=eBUSY) break;					//杆竚璝ぃΓ玥铬while(1)
		SendACK(0);									//癳CK獺腹(膥尿弄)
		GCC_DELAY(500*FreqFactor); 					//┑筐琿丁
	}
	SendACK(1);										//癳NO_ACK獺腹
	I2C_STOP();										//癳I2C STOP獺腹
	return retval;
}
void Init_I2C(void)									//20200326
{		SCL=1; SDA=1;								//砞﹚ SCL=1, SDA=1
	SCLC=0; SDAC=0; 					   			//SCL/SDA块家Α
	SDAPU=1;
	I2C_STOP();										//癳I2C STOP獺腹
}
void I2C_START(void)
{	/*
	SDA=1; SDAC=0; 									//砞﹚SDA=1块家Α
	SCL=1; ePAUSE;									//SCL=1, SDA=ePAUSE
	SDA=0;											//SDA=0 			     						
	SCL=0;											//SCL=0
	*/
													//2021.11.25穝	
	SDA=1; SDAC=0; 									//砞﹚SDA=1块家Α
	SCL=1; GCC_DELAY(8*FreqFactor); 				//SCL=1
	SDA=0;											//SDA=0 			     						
	SCL=0;											//SCL=0
}
void I2C_STOP(void)
{	/*
	SDA=0; SDAC=0;									//砞﹚ SDA=0 块家Α
	SCL=1; GCC_DELAY(10*(fSYS/8000000));			//SCL=1
	SDA=1;								    		//SDA=1
	*/
													//2021.11.25穝		
	SDA=0; SDAC=0;									//砞﹚ SDA=0 块家Α
//	GCC_DELAY(20);									//!!!for LA to Capture STOP
	SCL=1; 											//SCL=1
//	GCC_DELAY(15);									//!!!for LA to Capture STOP
	SDA=1;		
}
/*void CheckACK(void)
{	u8 i=0; 										//2021.11.25穝
	SDAC=1;							     			//SDA 块家Α
	SCL=1; 											//砞﹚ SCL=1
	do 
	{//	GCC_NOP();
		if(SDA==0) break;							//璝SDA=0玥铬瞒while(1)
	} while(i++<254);
	SCL=0; 											//砞﹚ SCL=0
	GCC_DELAY(50*FreqFactor); 						//for eDISPLAY Access Time
}*/
_Bool CheckACK(void)
{	u8 i=0,retval=0; 								//2021.12.31穝
	SDAC=1;							     			//SDA 块家Α
	SCL=1; 											//砞﹚ SCL=1
	do 
	{//	GCC_NOP();
		if(SDA==0)
		{ 	retval=1;
			break;									//璝SDA=0玥铬瞒while(1)
		}
	} while(i++<254);
	SCL=0; 											//砞﹚ SCL=0
	GCC_DELAY(50*FreqFactor); 						//for eDISPLAY Access Time
	return retval;
}

void SendACK(_Bool ack)
{	/*
	SDAC=0;	SDA=ack; 								//猔種璝ぃ砏购よ,SDAッ秆弄NoACK
	SCL=1; 			
	GCC_DELAY(8*(fSYS/8000000));	
	SCL=0;
	*/
													//2021.11.2穝
	SDAC=0;	SDA=ack; 								//猔種璝ぃ砏购よ,SDAッ秆弄NoACK
	SCL=1; 			
	SCL=0;
	GCC_DELAY(15*FreqFactor); 
}
void WriteByte(u8 I2CData)
{	/*
	u8 temp=0b10000000;
	SDAC=0;											//SDA块家Α
	while(temp!=0)									//肚癳8じ					
	{	SDA=(I2CData & temp)?1:0; ePAUSE;			//砞﹚ SDA 非晉
		SCL=0;					
		SCL=1; temp>>=1; SCL=0;    					//玻ネ SCL Clock
	}												//じ
	*/
													//2021.11.25穝	
	u8 temp;
	SDAC=0;											//SDA块家Α
	for(temp=0;temp<8;temp++)						//肚癳8じ	
	{	if(I2CData & (1<<7)) SDA=1; else SDA=0; 	//砞﹚ SDA 非
		SCL=1; I2CData<<=1;	SCL=0;					//玻ネ SCL Clock
	}												//じ	
}
u8 ReadByte(void)
{	/*
	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				//砞﹚ SDA 块家Α
	while(temp!=0)									//钡Μ8じ
	{	SCL=1; ePAUSE;								//砞﹚ SCL=1
		if(SDA) I2CData|=temp;						//钡Μじ
		temp>>=1;									//じ
		SCL=0;										//砞﹚ SCL=0
	} 
	return I2CData;
	*/
													//2021.11.25穝
	u8 I2CData=0, temp;	
	SDAC=1;							 				//砞﹚ SDA 块家Α
	for(temp=0;temp<8;temp++)						//钡Μ8じ
	{	SCL=1; 										//砞﹚ SCL=1
		I2CData<<=1;								//じ
		if(SDA) I2CData+=1; else I2CData+=0;		//钡Μじ
		SCL=0;										//砞﹚ SCL=0
	} 
	return I2CData;	
}
void Delayms(u16 i)						
{	u16 j;
	for (j=0;j<i;j++) GCC_DELAY(fSYS/4000);			//Delay i*mS 
}
