// PROGRAM	: ESP8266V9.c												2024.04.18
// FUNCTION	: ESP8266 Command  for HT66F2390							By Steven
/*	2024.0421 顯示傳輸狀態的LEDs改接至eDdisplay LED1~3(PF0,1,2),控制LED改為RGB LED(PC2,4,6)
	2024.0416 增加skip控制位元,以利UART1 ISR是否捨棄捨棄\r與\n
	2024.0413 修改UART_CUR()函式,將BRH轉成字串後設置 
	2024.0328 為提升反應速度,TB1時脈改為fSYS/4,psr=1(約185us中斷一次.Wait改為u16!!!
	注意：有關getResponse等讀取的相關判斷式尚未修改與測試,現只更改sendData與sendCommand等函式中的判斷式
*/
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include <string.h>
vu8 RxCount;															//記錄RX實際接收並存至指定Buffer的字元數
vu8 *ptrBuf;															//指向UART ISR接收資料存放區起始位址
vu16 CmdLen=0;															//設置不存於Buffer的字元數
vu16 Wait;																//ESP01命令回應等待時間累積器(unit:視TB1C、PSC1R設置)
vu16 rxTotalCnt;														//記錄所有接收的字元數(含\r\n)
volatile bit skip=1;													//是否捨棄\r與\n的控制位元(MQTT應用需求)
//=====================================================================================
DEFINE_ISR(UART1,0x3C)
//第二版                                            					//2021.0424
{	
//	rxTotalCnt++; 														//記錄所有UART接收的字元數(含\r\n)

/*
	_pa6=0;
	if(CmdLen) { CmdLen--; *ptrBuf=_txr_rxr1;}							//是否已跨過捨棄接收之字元數，讀取以免產生UART滿溢中斷
//	else if(_txr_rxr1!='\r' && _txr_rxr1!='\n')							//若不收\r\n
	else if((!skip) && _txr_rxr1!='\r' && _txr_rxr1!='\n')				//若不收\r\n
	{	*ptrBuf++=_txr_rxr1;											//取得接收資料
		RxCount++;														//接收且儲存之資料個數加1
//		if(((u16)ptrBuf&0xFF)==0) ptrBuf+=128;							//防止跨越Sector(HTTP測試用,可省略,但MQTT不得省略！)
		*ptrBuf=NULL;													//補NULL
	}
*/	
//第三版																//2024.0416   
	*ptrBuf=_txr_rxr1;													//取得接收資料(CmdLen!=0時亦需讀取以免產生UART滿溢中斷)
	if(CmdLen) CmdLen--; 												//是否已跨過捨棄接收之字元數
	else
	{	switch(skip) 
		{	case 1:	if(*ptrBuf=='\r' || *ptrBuf=='\n') break;			//捨棄\r與\n
			case 0:	ptrBuf++;											//ptrBuf指向下一位址			
					RxCount++;											//接收且儲存之資料個數加1
//					if(((u16)ptrBuf& 0x00FF)==0) ptrBuf+=128;			//防止跨越Sector(HTTP測試用,可省略,但MQTT不得省略！),此寫法會引發溢位!!!
//					if(RxCount==128) ptrBuf+=128;						//防止跨越Sector(HTTP測試用,可省略,但MQTT不得省略！)
		}
	}
	*ptrBuf=NULL;														//補NULL		
	Wait=0;																//清除超時計數器		
	_ur1f=0;															//清除UR1F旗標(共享型)	
	_int0f=0;															//for Zero-cross Processing Case!!!
}
u8 ATE0(void)
{	u8 cmdptr[15]="ATE0\r\n";
	return LEDControl(SendCommand(cmdptr,(u8*)"OK"));
}
u8 HardRESET8266(_Bool delay)
{	pESPReset=0; pESPResetc=0;											//ESP8266 Hard Reaet
	Delayms(5);	pESPReset=1;											//Wait 5mS
	if(delay) Delayms(1200);											//若搭配eDisplay的Reset程序,可省略延遲
	return 1;
}
u8 SoftRESET8266(void)
{	u8* cmdptr=(u8*)"AT+RST\r\n";
	pGLED=1; pRLED=1;													//亮燈
	while(*cmdptr!=0) 
	{	_txr_rxr1=*cmdptr++;											//送出資料至TXR
		while(!_txif1);													//等待資料送至TSR
	}
	Delayms(4000);														//Wait 4S
	pGLED=0; pRLED=0;													//滅燈
	return 1;
}
u8 AutoConnection(u8 connect)
{	u8 cmdptr[20]="AT+CWAUTOCONN=";										//Enabel(1)/Disable(0) Auto Connection
	connect+='0';														//轉成ASCII
	strncat((char*)cmdptr,(char*)&connect,(u8)1);
	strcat((char*)cmdptr,(char*)"\r\n");
	return LEDControl(SendCommand(cmdptr,(u8*)"OK"));
}
u8 UART_CUR(u32 baudRate)												//2024.0413 設置ESP01 UART傳輸速率
{	u8 baudstr[8],cmdptr[35]; 
	strcpy((char*)cmdptr,"AT+UART_CUR=");
	baud2String(baudRate,baudstr);										//將baudRate轉成字串
	strcat((char*)cmdptr,(char*)baudstr);
	strcat((char*)cmdptr,",8,1,0,0\r\n");								//2024.0417設置成功後似乎須一定時間方能切換鮑率
	return LEDControl(SendCommand(cmdptr,(u8*)"OK"));					//所以LDEControl的時間至少2ms!!!
}
u8 SetConnectionMode(u8 mode)
{	u8 cmdptr[15]="AT+CIPMUX=";
	mode+='0'; strncat((char*)cmdptr,(char*)&mode,(u8)1);
	strcat((char*)cmdptr,(char*)"\r\n");
	return  LEDControl(SendCommand(cmdptr,(u8*)"OK"));
}
u8 SetWiFiMode(u8 mode)
{	u8 cmdptr[15]="AT+CWMODE=";
	mode+='0'; strncat((char*)cmdptr,(char*)&mode,1);
	strcat((char*)cmdptr,(char*)"\r\n");
	return  LEDControl(SendCommand(cmdptr,(u8*)"OK"));
}
u8 CWJAP_(u8* ssid)														//詢問是否已加入SSID
{	u8 cmdptr[15]="AT+CWJAP?\r\n",error;								//
	SendCommand(cmdptr,(u8*)"OK");
	error=(strstr((char*)RxBuf0,(char*)ssid))? 1:0;	
	return   LEDControl(error);
}
u8 QuitAP(void)															//2023.09.10
{	u8 cmdptr[15]="AT+CWQAP\r\n",error=0;								
	if(SendCommand(cmdptr,(u8*)"OK")) error=1;							//未連線時若下達離線命令,回應OK
	else if(SendCommand(cmdptr,(u8*)"DISCONNECT")) error=1;				//連線時下達離線命令,回應WIFI DISCONNECT
	return   LEDControl(error);
}
u8 JointAP(u8* ssid, u8* pswd)											//2024.0112
{	u8 cmdptr[50]="AT+CWJAP_CUR=\"",error;
	strcat((char*)cmdptr,(char*)ssid); strcat((char*)cmdptr,(char*)"\"");
	strcat((char*)cmdptr,(char*)",\"");
	strcat((char*)cmdptr,(char*)pswd); strcat((char*)cmdptr,(char*)"\""); 
	strcat((char*)cmdptr,(char*)"\r\n");
	_psc1r=0x02;														//fTB1=fSUB,(1/fSUB)*1024(資料接收等待單位時間32ms)
	error=SendCommand(cmdptr,(u8*)"OK");
	_psc1r=0x01;														//fTB1=fSYS/4,(1/fSYS)*1024(資料接收等待單位時間222us)
	return LEDControl(error);
}
u8 GetIP(void)
{	u8 error=0,cmdptr[15]="AT+CIFSR\r\n";
	SendCommand(cmdptr,(u8*)"OK");
	error=(strstr((char*)RxBuf0,(char*)"0.0.0.0"))?0:1;
	return LEDControl(error);
}
u8 SetUpConnection(u8 mode,u8 id,u8* type,u8* conip,u16 port)			//20200624
{	u8 cmdptr[50]="AT+CIPSTART=",temp[6];
	if(mode==1)
	{	id+='0'; strncat((char*)cmdptr,(char*)&id,1);
		strcat((char*)cmdptr,(char*)",");
	}
	strcat((char*)cmdptr,(char*)"\"");
	strcat((char*)cmdptr,(char*)type); strcat((char*)cmdptr,(char*)"\",\"");
	strcat((char*)cmdptr,(char*)conip); strcat((char*)cmdptr,(char*)"\",");
	Word2String(port,temp);	strcat((char*)cmdptr,(char*)temp);
	strcat((char*)cmdptr,(char*)"\r\n");
	if(SendCommand(cmdptr,(u8*)"OK")) return 1;							
	if(strstr((char*)RxBuf0,(char*)"CONNECT")) return 1;				
	return 0;	
}
u8 CIPSend(u8 mode,u8 id,u8* ptr)
{	u8 cmdptr[20]="AT+CIPSEND=",temp[6];
	u16 length;
	CmdLen=0;
	if(mode==MULTIPLE)
	{	strncat((char*)cmdptr,(char*)&id,1);
		strcat((char*)cmdptr,(char*)",");
	}
	length=strlen((char*)ptr);
	Word2String(length,temp);
	strcat((char*)cmdptr,(char*)temp); strcat((char*)cmdptr,(char*)"\r\n");
	return SendCommand(cmdptr,(u8*)">");	
}
u8 CIPSendLen(u8 mode,u8 id, u16 length)								//length:Packet Length	
{	u8 cmdptr[20]="AT+CIPSEND=", temp[6];
	if(mode==MULTIPLE)
	{	strncat((char*)cmdptr,(char*)&id,1);
		strcat((char*)cmdptr,(char*)",");
	}
	Word2String((s16)length,temp);
	strcat((char*)cmdptr,(char*)temp); strcat((char*)cmdptr,(char*)"\r\n");
	return SendCommand(cmdptr,(u8*)">");	
}
u8 CloseConnection(u8 mode,u8 id)
{	u8 cmdptr[20]="AT+CIPCLOSE";
	if(mode==1)
	{	strcat((char*)cmdptr,(char*)"=");
		strncat((char*)cmdptr,(char*)&id,1);
	}
	strcat((char*)cmdptr,(char*)"\r\n");
	return SendCommand(cmdptr,(u8*)"OK");	
}
u8 ConfigTcpServer(u8 mode,u16 port)									//Only for CIPMUX=1
{	u8 cmdptr[30]="AT+CIPSERVER=",temp[6],error;
	mode+='0'; strncat((char*)cmdptr,(char*)&mode,1);
	if(mode=='1')
	{	strcat((char*)cmdptr,(char*)",");//e改strchr??
		Word2String(port,temp); strcat((char*)cmdptr,(char*)temp);
	}		
	strcat((char*)cmdptr,(char*)"\r\n");
	if(SendCommand(cmdptr,(u8*)"OK")) return LEDControl(1);
	error=(strstr((char*)RxBuf0,"no change"))? 1 : 0;
	return LEDControl(error);
}
u8 SendCommand(u8* ptr,u8* echo)										//2023.09.10.(送出命令閃爍BLED提示等待回應字串中)
{	u8 error=FALSE,f=TRUE;												//0表示錯誤
	ptrBuf=RxBuf0; *ptrBuf=0; RxCount=0;
	while(*ptr!=0) 
	{	_txr_rxr1=*ptr++;												//送出資料至TXR
		while(!_txif1);													//等待資料送至TSR
//		while(!_tidle1);												//等待資料送至TSR .....
	}
	_rxen1=1;															//啟動UART接收
	Wait=0; _tb1on=1;													//超時未收到資料機制啟動
//	while(Wait<3200)														//若未超時(視主程式中TB1C設置),尋找是否有指定之回應字串2024.0328
	while(Wait<10000)														//若未超時(視主程式中TB1C設置),尋找是否有指定之回應字串2024.0328
	{	////if(strstr((char*)RxBuf0,(char*)echo)!=0) 
		if(myFindStr((u8*)RxBuf0,(u8*)echo,RxCount)!=0) 
		{	error=TRUE;													//找到指定回應字串,設定正確旗標
//			LEDControl(9);												//RGB亮燈應用
			if(!f) LEDControl(9);										//一般應用
			break;														//跳離while(Wait<800)迴圈
		}
//		if(Wait>250 && f) LEDControl(3);								//超過一定時間BLED快閃,表示等待中(注意CWJAP是以128ms為單位)
		if(Wait>500 && f) LEDControl(3);								//超過一定時間BLED快閃,表示等待中(注意CWJAP是以128ms為單位)
		if(RxCount>23 && f)												//for JWAP command: WIFI CONNECTED(14)與WIFI GOT IP(9)
		{	if(myFindStr((u8*)RxBuf0+18,(u8*)"GOT",RxCount)!=0)			//for JWAP command
			{	LEDControl('B');										//已收到GOT,亮藍燈
				Wait=0;													//延長接收時間
				f=FALSE;
			}
		}
		if(myFindStr((u8*)RxBuf0,(u8*)"FAIL",RxCount)!=0) break;	
	}
	_tb1on=0; 	_rxen1=0;												//關閉超時計數器,關閉UART接收
	return error;
}
u8 SendData(u8* txptr,u8 *rxptr,u8* echo)					//2023.09.29.(送出資料，搭配CIPSendLen;ech0=NULL表示尚需接續其他資料)
{	u8 error=FALSE;											//0表示錯誤
 	while(*txptr!=0) 
	{	_txr_rxr1=*txptr++;									//送出資料至TXR
		while(!_txif1);										//等待資料送至TSR
	}
//	while(!_tidle1);										//等待TSR傳送完畢
	if(*echo==NULL) return TRUE;							//若非為最後一筆緩衝區資料
	ptrBuf=rxptr; *ptrBuf=0; RxCount=0;
	_rxen1=1;												//啟動UART接收
	Wait=0; _tb1on=1;										//超時未收到資料機制啟動
//	while(Wait<250)											//若未超時(視主程式中TB1C設置),尋找是否有指定之回應字串
	while(Wait<2000)										//若未超時(視主程式中TB1C設置),尋找是否有指定之回應字串2024.0328
	{	if(strstr((char*)rxptr,(char*)echo)!=0) 			//SEND OK	
		{	error=TRUE;										//找到指定回應字串,設定正確旗標
			break;											//跳離while(Wait<10)迴圈
		}
//		if(Wait>200) LEDControl(3);							//超過一定時間BLED快閃,表示等待中
	}
	_tb1on=0; 												//關閉超時計數器
	_rxen1=0;												//關閉UART接收
	return error;
}
u8 SendDataGetRes(u8* txptr,u8 *rxptr,u8* echo)				//2023.09.29.(送出資料並確認收到RESPONSE，搭配CIPSendLen;ech0=NULL表示尚需接續其他資料)
{	u8 error=FALSE;											//0表示錯誤
    u8 *ptr;
	u8 base=1; u16 len=0;

 	while(*txptr!=0) 
	{	_txr_rxr1=*txptr++;									//送出資料至TXR
		while(!_txif1);										//等待資料送至TSR
	}
//	while(!_tidle1);										//等待TSR傳送完畢
	if(*echo==NULL) return TRUE;							//若非為最後一筆緩衝區資料
	ptrBuf=rxptr; *ptrBuf=0; RxCount=0;
	_rxen1=1;												//啟動UART接收
	Wait=0; _tb1on=1;										//超時未收到資料機制啟動
	while(Wait<1600)										//若未超時(視主程式中TB1C設置),尋找是否有指定之回應字串
	{	if(strstr((char*)rxptr,(char*)echo)!=0) 			//SEND OK	
		{	error=TRUE;										//找到指定回應字串,設定正確旗標
			break;											//跳離while(Wait<10)迴圈
		}
	}
	if(error==FALSE) return error;
	ptr=rxptr; ptrBuf=rxptr; *ptrBuf=NULL;					//準備接收HTTP RESPONSE
	error=FALSE; RxCount=0; Wait=0;
	while(RxCount<50 || Wait<3)								//while(CmdLen!=0 || Wait<3)
	{	if(len==0)									
		{	if(RxCount>12)									//接收+IPD,xxx:....;此一計算過程仍會繼續接收字元
			{ 	ptr=(u8*)strchr((char*)rxptr,(char)':');	//
				while(ptr==NULL)							//2023.09.28
				{	_tb1on=0; _rxen1=0; 					//2023.09.28
					return 4;								//2023.09.28
				}				
				while(*--ptr!=',')							//計算HTTP Response字元總數
				{	len+=(*ptr-'0')*base;
					base*=10;
				}
				CmdLen=len-65;								//僅保留最65個字元
				error=TRUE;									//只要有收到+IPD=xxx即回傳TRUE 2023.09.26
			}	
		}
		if(Wait>120) break;									//2023.09.29
	}
	if(error)												//2023.09.29一定等到CLOSED
	{	do ptr=(u8*)strstr((char*)rxptr,(char*)"CLOSED");	//若發送成功並收到RESPONSE,等收到CLOSED才返回
		while(ptr==NULL);
	}										
	_tb1on=0; 												//關閉超時計數器
	_rxen1=0;												//關閉UART接收
	return error;						
}
u8 NetRxData(u8 *ptrbak)		
{	u8 base=1,*ptr; u16 len=0;
//	CmdLen=8;												//"x,CONECT"								
	ptr=ptrbak; ptrBuf=ptrbak; *ptrBuf=NULL; RxCount=0;
	_rxen1=1;												//啟動UART接收
	while(RxCount==0);										//等待資料接收
	Wait=0; _tb1on=1;										//一旦收到資料，超時未收到資料機制啟動											
	while(RxCount<50 || Wait<(2<<3))						//while(CmdLen!=0 || Wait<3)
//	while(RxCount<50 || Wait<(2<<8))						//while(CmdLen!=0 || Wait<3)
	{	if(len==0)											//GET/POST接收判斷
		{	if(RxCount>30)									//接收Link+IPD,0,xxx:....
			{ 	ptr=(u8*)strchr((char*)ptrbak,(char)':');
				if(ptr==NULL) { pERLED=!LEDOn; while(1);}	//死圈
				while(*--ptr!=',')							//計算HTTP Request字元總數
				{	len+=(*ptr-'0')*base;
					base*=10;
				}
				CmdLen=len-60;								//僅保留最60個字元
			}	
		}
	} 			
	_tb1on=0; 												//關閉超時計數器
	_rxen1=0;												//關閉UART接收
	if(strstr((char*)ptrbak,"GET")) return GET;
	if(strstr((char*)ptrbak,"POST")) return HTTP;
	return 0;						
}
u8 getHttpResponse(u8 *ptrbak)								//2023.09.29	
{	u8 base=1, error=FALSE, *ptr; u16 len=0;
	ptr=ptrbak; ptrBuf=ptrbak; *ptrBuf=NULL; RxCount=0;
	_rxen1=1;												//啟動UART接收
	while(RxCount==0);										//等待資料接收
	Wait=0; _tb1on=1;										//一旦收到資料，超時未收到資料機制啟動											
	while(RxCount<50 || Wait<(5<<3))								//while(CmdLen!=0 || Wait<3)
	{	if(len==0)									
		{	if(RxCount>10)									//接收+IPD,xxx:....;此一計算過程仍會繼續接收字元
			{ //	ptr=(u8*)strchr((char*)RxBuf2,(char)':');	//
				ptr=(u8*)strchr((char*)ptrbak,(char)':');	//必須保證接收完"200 OK"才會回傳TRUE
				while(ptr==NULL)							//2023.09.28
				{	_tb1on=0; _rxen1=0; 					//2023.09.28
					return 4;								//2023.09.28
				}				
				while(*--ptr!=',')							//計算HTTP Response字元總數
				{	len+=(*ptr-'0')*base;
					base*=10;
				}
				CmdLen=len-65;								//僅保留最65個字元
				error=TRUE;									//只要有收到+IPD=xxx即回傳TRUE 2023.09.26
			}	
		}
		if(Wait>50) break;									//2023.09.29
	}
	if(error)												//2023.09.29一定等到CLOSED
	{	do ptr=(u8*)strstr((char*)ptrbak,(char*)"CLOSED");	
		while(ptr==NULL);
	}										
	_tb1on=0; 												//關閉超時計數器
	_rxen1=0;												//關閉UART接收
	return error;						
}
DEFINE_ISR(ISR_TB1,0x28)
{	_emi=1;
	Wait++;																	//Wait+1
}
void baud2String(u32 bdr,u8 *ptr)											//轉換BRH為字串(115200/230400)
{	u32 base=1000000; u8 i; bit flag=1;
	for(i=0;i<7;i++)
	{	*ptr=bdr/base; bdr%=base;
		if(flag!=1 || *ptr!=0)
		{	*ptr+='0';	ptr++;												//轉成ASCII
			flag=0;
		}
		base/=10;
	}
	*ptr=NULL;																//字串結束
}
void Word2String(s16 data,u8 *ptr)											//轉換signed Word為字串
{	u16 base=10000; u8 i; bit flag=1;
	if(data==0)  *ptr++='0';
	else
	{	if(data<0) {data=-data; *ptr++='-';}								//取得符號
		for(i=0;i<5;i++)
		{	*ptr=data/base; data%=base;
			if(flag!=1 || *ptr!=0)
			{	*ptr+='0';	ptr++;											//轉成ASCII
				flag=0;
			}
			base/=10;
		}
	}
	*ptr=NULL;																//字串結束
}
void Word2StringFloat(s16 data,u8 *ptr, u8 dp)								//2023.09.26
{	u16 base=10000; bit flag=1,fz;											//Word轉字串含小數點位置
	u8 i, ascii[8], digCnt=0, s=0, index=0;									//Sign+Data(5 Digit)+'.'+NULL
	fz=(data) ? 0 : 1;														//if data=0 then fz=1									
	if(data<0) {data=-data; *ptr='-'; digCnt++;}							//正負數判斷
	if(data<10)	{*(ptr+digCnt)=data+'0'; digCnt++;}							//Convert to ASCII
	else
	{	for(i=0;i<5;i++)													//依序取得各個位數
		{	*(ptr+digCnt)=data/base; data%=base;
			if(flag!=1 || *(ptr+digCnt)!=0)
			{	*(ptr+digCnt)+='0';	digCnt++;								//Convert to ASCII
				flag=0; 
			}
			base/=10;
		}
	}
	*(ptr+digCnt)=NULL;														//塞入結束字元
	if(fz || dp==0 || dp>4) return;											//無小數點
	if(*ptr=='-')
	{	ascii[s++]=*(ptr+index++);											//取得符號
		digCnt--;															//digCnt為整數個數(不含符號)
	}
	if(digCnt>dp)
	{	for(i=0;i<digCnt;i++)
		{	if(i==(digCnt-dp)) ascii[i+s++]='.';							//補小數點	
			ascii[s+i]=*(ptr+index++);
		}
		ascii[s+i]=NULL;													//塞入結束字元
	}
	else
	{	ascii[s++]='0';														//補小數點前的0	
		ascii[s++]='.';														//補小數點	
		for(i=1;i<=(dp-digCnt);i++) ascii[s++]='0';							//補小數點後的0	
		for(i=0;i<=digCnt;i++) ascii[s+i]=*(ptr+index++);
		ascii[s+i]=NULL;													//塞入結束字元		
	}
	i=0;
	do *(ptr+i)=*(ascii+i); while(*(ascii+i++)!=NULL);						//複製字串
}
void word2string(u8* ptr,s16 value,u8 dotpos)						//2024.0418 16-Bit整數化為浮點數(指定小數點位置)
{	u8 i,idx; u16 base=10000; bit fLZ=1;							//前導零轉為空白,最終再移除空白()
	if(value==0)
	{	ptr[0]='0';
		ptr[1]=0;
		return;
	}
	if(value<0) 													//符號判別處裡
	{	*ptr++='-';
		value=-value;		
	}
	if(dotpos>4) dotpos=0;
	if(dotpos) idx=6; else idx=5;
	for(i=0;i<idx;i++)												//將data轉換成各個位數
	{	if(i==dotpos && dotpos!=0) 									//是否要顯示小數點?
		{	ptr[i]='.';												//標記小數點位置 
			continue;
		}
		ptr[i]=value/base; value%=base;
		base/=10;													//基底調整
	}	
	for(i=0;i<idx;i++)												//將各個位數轉換成ASCII或空白(前導零)
	{	if(dotpos!=0)												//是否有小數點?
		{	if(i==dotpos-1 && fLZ==1) 								//是否為小數點前一位數
			{	ptr[i]+='0';
				fLZ=0; 
				continue;
			}
			else if(i==dotpos) continue;							//保留小數點
		}
		if(fLZ==1 && ptr[i]==0) ptr[i]=' ';							//前導零轉成空白
		else
		{	fLZ=0;
			ptr[i]+='0';
		}
	}
	if(fLZ==1) ptr[i++]='0';	
	ptr[i]=0;														//塞入結數字元
//================================================================	//以下程式用於去除空白
	dotpos=0; 
	while(dotpos<idx)
	{	if(ptr[dotpos]!=' ') break;									//尋找非' '的字元
		dotpos++;													//' '個數加一
	}
	if(dotpos!=0)													//非' '資料移位
	{	for(i=0;i<idx;i++) ptr[i]=ptr[i+dotpos];
	}
}
u8 *FindString(u8* ptrsrc, u8* ptrfind, u8 srclen)					//跨Section尋找指定字串
{	u8 i=0,cnt,findlen;												//for MQTT Payload KEY Search
	u8* ptr;														//注意：會自動在 *ptrfind前後補上"
	DEFINE_SFR(u8, str[30], 0x1280);								//Bank 18:80h~FFh
	str[0]='\"';str[1]=NULL;										//補"
	strcat((char*)str,(char*)ptrfind);								//串接 *ptrfind
	strcat((char*)str,(char*)"\"");									//補"
	findlen=strlen((char*)str);										//str字串長度
	do
	{	ptr=ptrsrc;
		for(cnt=0;cnt<findlen;cnt++)
		{	if(*ptr!=*(str+cnt)) break;
			ptr++;
			if(((u16)ptr&0xFF)==0) ptr+=128;						//跨Section處理 
		}
		if(cnt==findlen) return ptrsrc;
		ptrsrc++;i++;
		if(((u16)ptrsrc&0xFF)==0) ptrsrc+=128;						//跨Section處理 
	} while(i<=(srclen-findlen));
	return NULL;
}
u8* myFindStr(u8* ptrsrc, u8* ptrfind, u8 srclen)							//尋找指定字串(ptrsrc不以NULL為結束而是指定長度)無跨Section限定
{	u8 i=0,cnt,findlen;
	findlen=strlen((char*)ptrfind);											//字串長度
	if(srclen<findlen) return NULL;
/*	do
	{	ptr=ptrsrc;
		for(cnt=0;cnt<findlen;cnt++)										//字串字元逐一比對
		{	if(*ptr!=*(ptrfind+cnt)) break;
			ptr++;
		}
		if(cnt==findlen) return ptrsrc;										//找到符合字串,回傳位址
		ptrsrc++; i++;
	} while(i<=(srclen-findlen));

*/
	do
	{	for(cnt=0;cnt<findlen;cnt++)										//字串字元逐一比對
		{	if(ptrsrc[cnt]!=*(ptrfind+cnt)) break;
		}
		if(cnt==findlen) return ptrsrc;										//找到符合字串,回傳位址
		ptrsrc++; i++;
	}while(i<=(srclen-findlen));											//while((srclen-i)>=findlen);
	return NULL;
}
u8 *FindStringHMQ(u8* ptrsrc, u8* ptrfind, u8 srclen)						//跨Section尋找指定字串 for HMQ(不以NULL為結束)
{	u8 i=0,cnt,findlen;														//for MQTT Payload KEY Search
	u8* ptr;																//注意：會自動在 *ptrfind前後補上"
	DEFINE_SFR(u8, str[30], 0x1280);										//Bank 18:80h~FFh
	str[0]=NULL;															//補"
	strcat((char*)str,(char*)ptrfind);										//串接 *ptrfind
	strcat((char*)str,(char*)"=");											//補"
	findlen=strlen((char*)str);												//str字串長度
	do
	{	ptr=ptrsrc;
		for(cnt=0;cnt<findlen;cnt++)
		{	if(*ptr!=*(str+cnt)) break;
			ptr++;
			if(((u16)ptr&0xFF)==0) ptr+=128;								//跨Section處理 
		}
		if(cnt==findlen) return ptrsrc;
		ptrsrc++;i++;
		if(((u16)ptrsrc&0xFF)==0) ptrsrc+=128;								//跨Section處理 
	} while(i<=(srclen-findlen));
	return NULL;
}
u8 LEDControl(u8 error)
{	switch (error)
	{	case 0: pERLED=!LEDOn; Delayms(300); pERLED=!LEDOff; break;
		case 1: pEGLED=!LEDOn; Delayms(  2); pEGLED=!LEDOff; break;
		case 2: pEBLED=!LEDOn; Delayms(  2); pEBLED=!LEDOff; break;
		case 3: pEBLED=!LEDOn; Delayms(  4); pEBLED=!LEDOff; Delayms(30); break;//2023.09.10
		case 4: pERLED=!LEDOn; Delayms(500); pERLED=!LEDOff; break;			//2023.09.28
		case 5: pERLED=!LEDOn; pEGLED=!LEDOn; Delayms(1);						//2024.01.11
				pERLED=!LEDOff; pEGLED=!LEDOff; Delayms(4);break;
				
		case 9: pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff; break;
		case 'R': pERLED=!LEDOn; break;										//2024.03.09
		case 'G': pEGLED=!LEDOn; break;										//2024.03.09
		case 'B': pEBLED=!LEDOn; break;										//2024.03.09
		case 'r': pERLED=!LEDOn; GCC_DELAY(80); pERLED=!LEDOff; break;
		case 'g': pEGLED=!LEDOn; GCC_DELAY(80); pEGLED=!LEDOff; break;
		case 'b': pEBLED=!LEDOn; GCC_DELAY(80); pEBLED=!LEDOff; break;
	}	
	return error;
}