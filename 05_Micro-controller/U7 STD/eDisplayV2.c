// PROPGRAM : e-Display.C 							2020.0326
// FUNCTION	: e-Display(I2C Interface) Library 		By Steven
#include <HT66F2390.h>
#include "MyType.h"
#include "eDisplayV2.h"

volatile u16 ForeColor=Yellow, BackColor=Blue;		//預設字型前、背景顏色20200325
volatile bit feDisplay5DigitNoSpace=0;				//預設顯示數字前之空白20200326

void eDisplayHex(u8 x, u8 y, u8 h)					//Font Size: 8x14	
{	u8 Buffer[8];
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=8;		//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=y;						//裝載參數
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	Buffer[6]=((h>>4)<10)?(h>>4)+'0':(h>>4)+'7';
	Buffer[7]=((h&0x0F)<10)?(h&0x0F)+'0':(h&0x0F)+'7';
	e_DataRAM(Buffer,8);							//送出參數
	I2C_STOP();										//送出I2C STOP信號
}
void eDisplay5Digit(u8 x, u8 y,u16 data, u8 dp)		//20200326  ex: 123.45 (dp=3)
{	bit fLZ=1;										//dp=0 for no dp
	u8 i,ascii[]={0,0,0,0,0,0,0,0};
	u16 temp=10000;
	for(i=(dp==0)?1:0;i<6;i++)						//將data轉換成各個位數
	{	if(i==dp) 									//是否要顯示小數點?
		{	ascii[i]='.';							//標記小數點位置 
			continue;
		}
		ascii[i]=data/temp; data%=temp;
		temp/=10;									//基底調整
	}	
	for(i=0;i<6;i++)								//將各個位數轉換成ASCII或空白(前導零)
	{	if(dp!=0)									//是否有小數點?
		{	if(i==dp-1 && fLZ==1) 					//是否為小數點前一位數
			{	ascii[i]+='0';
				fLZ=0; 
				continue;
			}
			else if(i==dp) continue;				//保留小數點
		}
		if(fLZ==1 && ascii[i]==0) ascii[i]=' ';		//前導零轉成空白
		else
		{	fLZ=0;
			ascii[i]+='0';
		}
	}
	if(fLZ==1) ascii[5]='0';
	i=0;											//設置字串起始指標					
	if(feDisplay5DigitNoSpace)						//是否顯示數字前之空白
	{	while(1)									//數字前空白若不列印～		
		{	if(ascii[i]!=' ') break;
			i++;
		}
	}	
	eDisplayStr(x,y,&ascii[i]);
}
void eDisplayStr(u8 x, u8 y, u8 *ptr)				//Font Size: 8x14	
{	u8 i=6,Buffer[22];
	while(*ptr) {Buffer[i]=*ptr++;i++;};
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=i;		//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=y;						//裝載參數
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	e_DataRAM(Buffer,i);							//送出參數
	I2C_STOP();										//送出I2C STOP信號
}
void eDisplayChar(u8 x, u8 y, u8 ch)				//Font Size: 8x14	
{	u8 Buffer[8];
	Buffer[0]=cmdASC; Buffer[1]=0; Buffer[2]=7;		//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=y;						//裝載參數
	Buffer[2]=ForeColor>>8;	Buffer[3]=(u8)ForeColor;
	Buffer[4]=BackColor>>8;	Buffer[5]=(u8)BackColor;
	Buffer[6]=ch;
	e_DataRAM(Buffer,7);							//送出參數
	I2C_STOP();										//送出I2C STOP信號
}
void eDisplayDot(u8 x, u8 y, u16 color)
{	u8 Buffer[8]={cmdDOT,0,4,0,0,0,0,0};			//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x;									//裝載參數
	Buffer[1]=y;
	Buffer[2]=color>>8;	Buffer[3]=(u8)color;	
	e_DataRAM(Buffer,4);							//送出參數
	I2C_STOP();										//送出I2C STOP信號 
}
void eDisplayRet(u8 x, u8 xSize,u8 y, u8 ySize, u16 color)
{	u8 Buffer[8]={cmdRET,0,6,0,0,0,0,0};			//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=xSize;					//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;
	Buffer[4]=color>>8;	Buffer[5]=(u8)color;	
	e_DataRAM(Buffer,6);							//送出參數
	I2C_STOP();										//送出I2C STOP信號
}
void eDisplayPic(u8 x,u8 xSize, u8 y, u8 ySize, const u16* pptr)
{	u16 i;
	u8 Buffer[8]={cmdPIC,0,4,0,0,0,0,0};			//裝載命令
	e_Command(Buffer);								//送出命令
	Buffer[0]=x; Buffer[1]=xSize;					//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;	
	e_DataRAM(Buffer,4);							//送出參數
	for(i=0;i<(xSize*ySize);i++)
	{	WriteByte(*pptr>>8); CheckACK();			//送出Hi-Byte並等待回應ACK
		WriteByte((u8)*pptr++); CheckACK();			//送出Lo-Byte並等待回應ACK
	}
	I2C_STOP();										//送出I2C STOP信號
}
void eDisplayClear(u8 x,u8 xSize,u8 y,u8 ySize)
{	u8 Buffer[8]={cmdCLR,0,4,0,0,0,0,0};			//裝載命令
	e_Command(Buffer);								//送出e-Display清除命令
	Buffer[0]=x; Buffer[1]=xSize;					//裝載參數
	Buffer[2]=y; Buffer[3]=ySize;
	e_DataRAM(Buffer,4);							//送出x/y座標起點及長度
	I2C_STOP();										//送出I2C STOP信號 
}
void eDisplayReset(void)							//Reset EDisplay and Initila SCL,SDA
{	peReset=0;  peResetC=0;
	Init_I2C();
	Delayms(1);
	peReset=1;
	Delayms(2600);
}
void e_Command(u8* ptr)
{	u8 i;
	//while(e_Read()==eBUSY); 						//檢查e-Display忙碌狀態	
	e_Read();
	I2C_START();									//檢查並等待e-Display結束忙碌狀態 !!!20211125更新	
	WriteByte(DeviceID|0); CheckACK();				//送出DeviceID_W並等待回應ACK
	for(i=0;i<8;i++)								//e-Display命令長度固定為8
	{	WriteByte(*ptr++); CheckACK();				//逐Byte送出命令並等待回應ACK
	}
}
void e_DataRAM(u8* ptr,u8 Length)
{	u8 i;
	for(i=0;i<Length;i++)
	{	WriteByte(*ptr++); CheckACK();				//逐Byte送出RAM資料並等待回應ACK
	}
}
u8 e_Read(void)
{	u8 retval;
//	I2C_START();									//送出I2C START信號  
//	WriteByte(DeviceID|1); CheckACK();				//送裝置ID並等待回應ACK信號 
//	retval=ReadByte();								//讀取裝置回傳值
//	SendACK(1);										//送出NO_ACK信號
//	I2C_STOP();										//送出I2C STOP信號

	I2C_START();									//送出I2C START信號 
	WriteByte(DeviceID|1); CheckACK();				//送裝置ID並等待回應ACK信號 
	while(1)
	{	retval=ReadByte();							//讀取裝置回傳值
		if(retval!=eBUSY) break;					//裝置若不忙則跳出while(1)
		SendACK(0);									//送出CK信號(表明繼續讀取)
		GCC_DELAY(500*FreqFactor); 					//延遲一段時間
	}
	SendACK(1);										//送出NO_ACK信號
	I2C_STOP();										//送出I2C STOP信號
	return retval;
}
void Init_I2C(void)									//20200326
{		SCL=1; SDA=1;								//設定 SCL=1, SDA=1
	SCLC=0; SDAC=0; 					   			//SCL/SDA為輸出模式
	SDAPU=1;
	I2C_STOP();										//送出I2C STOP信號
}
void I2C_START(void)
{	/*
	SDA=1; SDAC=0; 									//設定SDA=1並為輸出模式
	SCL=1; ePAUSE;									//SCL=1, SDA=ePAUSE
	SDA=0;											//SDA=0 			     						
	SCL=0;											//SCL=0
	*/
													//2021.11.25更新	
	SDA=1; SDAC=0; 									//設定SDA=1並為輸出模式
	SCL=1; GCC_DELAY(8*FreqFactor); 				//SCL=1
	SDA=0;											//SDA=0 			     						
	SCL=0;											//SCL=0
}
void I2C_STOP(void)
{	/*
	SDA=0; SDAC=0;									//設定 SDA=0 並為輸出模式
	SCL=1; GCC_DELAY(10*(fSYS/8000000));			//SCL=1
	SDA=1;								    		//SDA=1
	*/
													//2021.11.25更新		
	SDA=0; SDAC=0;									//設定 SDA=0 並為輸出模式
//	GCC_DELAY(20);									//!!!for LA to Capture STOP
	SCL=1; 											//SCL=1
//	GCC_DELAY(15);									//!!!for LA to Capture STOP
	SDA=1;		
}
/*void CheckACK(void)
{	u8 i=0; 										//2021.11.25更新
	SDAC=1;							     			//SDA 為輸入模式
	SCL=1; 											//設定 SCL=1
	do 
	{//	GCC_NOP();
		if(SDA==0) break;							//若SDA=0則跳離while(1)
	} while(i++<254);
	SCL=0; 											//設定 SCL=0
	GCC_DELAY(50*FreqFactor); 						//for eDISPLAY Access Time
}*/
_Bool CheckACK(void)
{	u8 i=0,retval=0; 								//2021.12.31更新
	SDAC=1;							     			//SDA 為輸入模式
	SCL=1; 											//設定 SCL=1
	do 
	{//	GCC_NOP();
		if(SDA==0)
		{ 	retval=1;
			break;									//若SDA=0則跳離while(1)
		}
	} while(i++<254);
	SCL=0; 											//設定 SCL=0
	GCC_DELAY(50*FreqFactor); 						//for eDISPLAY Access Time
	return retval;
}

void SendACK(_Bool ack)
{	/*
	SDAC=0;	SDA=ack; 								//注意：若不先規劃方向,SDA似乎永解讀為NoACK
	SCL=1; 			
	GCC_DELAY(8*(fSYS/8000000));	
	SCL=0;
	*/
													//2021.11.2更新
	SDAC=0;	SDA=ack; 								//注意：若不先規劃方向,SDA似乎永解讀為NoACK
	SCL=1; 			
	SCL=0;
	GCC_DELAY(15*FreqFactor); 
}
void WriteByte(u8 I2CData)
{	/*
	u8 temp=0b10000000;
	SDAC=0;											//SDA為輸出模式
	while(temp!=0)									//傳送8個位元					
	{	SDA=(I2CData & temp)?1:0; ePAUSE;			//設定 SDA 準位
		SCL=0;					
		SCL=1; temp>>=1; SCL=0;    					//產生 SCL Clock
	}												//下一位元
	*/
													//2021.11.25更新	
	u8 temp;
	SDAC=0;											//SDA為輸出模式
	for(temp=0;temp<8;temp++)						//傳送8個位元	
	{	if(I2CData & (1<<7)) SDA=1; else SDA=0; 	//設定 SDA 準位
		SCL=1; I2CData<<=1;	SCL=0;					//產生 SCL Clock
	}												//下一位元	
}
u8 ReadByte(void)
{	/*
	u8 I2CData=0, temp=0b10000000;
	SDAC=1;							 				//設定 SDA 為輸入模式
	while(temp!=0)									//接收8個位元
	{	SCL=1; ePAUSE;								//設定 SCL=1
		if(SDA) I2CData|=temp;						//接收位元值
		temp>>=1;									//下一位元
		SCL=0;										//設定 SCL=0
	} 
	return I2CData;
	*/
													//2021.11.25更新
	u8 I2CData=0, temp;	
	SDAC=1;							 				//設定 SDA 為輸入模式
	for(temp=0;temp<8;temp++)						//接收8個位元
	{	SCL=1; 										//設定 SCL=1
		I2CData<<=1;								//下一位元
		if(SDA) I2CData+=1; else I2CData+=0;		//接收位元值
		SCL=0;										//設定 SCL=0
	} 
	return I2CData;	
}
void Delayms(u16 i)						
{	u16 j;
	for (j=0;j<i;j++) GCC_DELAY(fSYS/4000);			//Delay i*mS 
}
