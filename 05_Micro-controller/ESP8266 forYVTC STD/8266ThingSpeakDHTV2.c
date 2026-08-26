// PROGRAM	: 8266ThingSpeakDHTV2.c									2026.0225
// FUNCTION	: ESP8266 Command Test for HT66Fxx(@11.059)				By Steven
//   Note   : DHT-22 Sugnal->PB3
//          : 非固定IP,故欲控制的PC或手機與ESP01必須屬同一網域
//			  手機熱點分享，iOS請開啟最大相容性、Android請關閉WiFi連線	

#define	SSID	"VeraiPhone"										//改成自己的手機熱點
#define	PSWD	"44445555"									//改成自己的手機熱點密碼
#define 	ConIP	"api.thingspeak.com"							//欲連線的IP
#define 	UPDATE	"GET /update?key=4LD8L3Z46DZKS6YQ"				//改成自己的Channel Write API Key

//*** ====================================================================
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "eDisplayV2.H"
#include "DHTSeries.h"
#include <string.h>
#include <math.h>
extern volatile u8  Wait,*ptrBuf,RxCount;
extern volatile u16 CmdLen,rxTotalCnt;
DEFINE_SFR(u8, TxBuf[BufLen], 0xA80);								//Bank A:80h~FFh
u8 ReadDHT(u16* h,u16* t);
void THtoString(u16 data,u8 *dptr);
void main()
 {	u8 ASCII[7],*ptr; u8 i; s16 temp;
	u16 h,t;
	_wdtc=0b10101111;												//關閉WDT
	_pbs1=0xF0; _hxtm=1;											//指定PB[7:6]為OSC功能
	_rstc=0xAA;														//PB5 as Reset Pin
	_hxten=1; while(!_hxtf);										//致能HXT並等待穩定
	_fhs=1; _hircen=0;												//選擇fH為HXT,關閉HIRC
	pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff;					//eDisplay LED Control Pin(Active Low!!!)
	pERLEDC=0; 		pEGLEDC=0; 		pEBLEDC=0;	
	_pds0=0x28;	_rx1ps=0;											//設置腳位功能 TX1->PD2,RX1->PD1
	_u1cr1=0b10000000;												//UARTEN1/8-Bit/No_parity//1 Stop Bit///
	_u1cr2=0b10100100;												//TXEN1/RXEN1/BRGH1/RIE1//	
	_brg1=fH/((u32)16*BR)-1;										//BRGH1=1
 	_psc1r=0x01; _tb1c=0x00; _tb1f=0; _tb1e=1;						//fTB1=fSYS/4,(4/fSYS)*256 (資料接收等待單位時間92.5us)  	
	HardRESET8266(0);												//RESET 8266後才能致能中斷,避開RESET階段回送之訊息
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	eDisplayStr(10,10,(u8*)"ThingSpeak DHT");
	_mf5e=1; _ur1e=1;												//致能UART0中斷
	_emi=1;															//致能中斷
	CmdLen=0;
	while(!ATE0());
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;										//BRGH1=1	
	eDisplayStr(6,35,(u8*)"Wait SSID......");
	while(!SetWiFiMode(STA));									
	while(!SetConnectionMode(SINGLE));	
	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
//		GCC_NOP(); 
	}
	eDisplayRet(0,128,35,12,BackColor);								//清除"Wait SSID......"
 	while(!GetIP());
 	ptr=(u8*)strichr((char*)RxBuf0,(int)'\"');						//找第一個"位址
 	ptr=(u8*)strichr((char*)(ptr+1),(int)'\"');						//找第二個"位址
 	*ptr=0;															//塞入結束字元
 	ptr=(u8*)strichr((char*)RxBuf0,(int)'\"');						//找第一個"位址
	eDisplayStr(10,35,(u8*)(ptr+1));								//顯示分配之IP	
	eDisplayStr(10,60,(u8*)"Temp.=");
	eDisplayStr(10,76,(u8*)"Humi.=");
	eDisplayStr(10,99,(u8*)"RspCnt:");								//Response Count		
	while(1)
	{	for(i=0;i<255;i+=8)
		{	if(SetUpConnection(0,0,(u8*)"TCP",(u8*)ConIP,80)!=0)
			{	strcpy((char*)TxBuf,UPDATE);
				strcat((char*)TxBuf,"&field1=");
		    	Word2String(i,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    	strcat((char*)TxBuf,(char*)"&field2=");
		    	temp=1500*sin(2*PI*i/255);
		    	Word2String(temp,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    	if(ReadDHT(&h,&t)==1)
				{	strcat((char*)TxBuf,"&field3=");
					THtoString(t,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    		eDisplayStr(70,60,(u8*)"   ");					//清除先前顯示資料
					eDisplayStr(70,60,(u8*)ASCII);					//顯示溫度資料	
					strcat((char*)TxBuf,"&field4=");
					THtoString(h,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    		eDisplayStr(70,77,(u8*)"     ");				//清除先前顯示資料
					eDisplayStr(70,77,(u8*)ASCII);					//顯示濕度資料
				}		    	
		  		strcat((char*)TxBuf,(char*)"\r\n");
				LEDControl(CIPSend(SINGLE,NULL,(u8*)TxBuf));
				LEDControl(SendCommand((u8*)TxBuf,(u8*)"CLOSED"));
			    eDisplayStr(70,99,(u8*)"     ");					//清除先前顯示回應資料
				ptr=(u8*)strstr((char*)RxBuf0,(char*)"IPD");
				if(ptr) 
				{	*ASCII=*(ptr+4)-'0';							//+IPD,n:abc...(n由ASCII轉數值,代表接收之字元總數)
					ptr=ptr+6;										//指向接收資料起點(a)
					*(ptr+*ASCII)=NULL;								//塞入字串結束字元
					eDisplayStr(70,99,ptr);							//顯示ThingSpeak回應資料
				}
			}
			Delayms(15000);
		}
	}
}
void THtoString(u16 data,u8 *dptr)
{	*dptr++=data/100+'0'; data%=100;
	*dptr++=data/10+'0'; data%=10;
	*dptr++='.';
	*dptr++=data+'0';
	*dptr=NULL;
}
u8 ReadDHT(u16* ptrh,u16* ptrt)
{	u32 temp=0,temp1=(u32)1<<31;
	u16 TCnt; u8 parity=0;
	_ptm2c0=0;														//fINT=fSYS/4
	_ptm2c1=0b10110000;												//Single-Pulse/Active Low
	_ptm2al=(u8)StartTC; _ptm2ah=StartTC>>8;						//Start Signal
	_pbs0=0xC0;														//PB3==>PTP2		
	_ptm2af=0; _pt2on=1; 											//開始輸出
	while(!_ptm2af); 												//等待Start Signal結束
	_pbs0&=0x3F;													//PB3==>I/O
	_ptm2rpl=(u8)TresMax; _ptm2rph=TresMax>>8;						//設置捕捉值上限(Response=80+80us)
	_ptm2c1=0b01010000;												//Capture I/P,負緣捕捉 
	_ptp2ips=1;														//PTP2I -> PB3 (IFS1)	
 	_ptm2af=0; _ptm2pf=0; 											//清除旗標
 	while(pDHT);													//等待DHT Pull-low
	_pt2on=1; 														//啟動Capture
	while(!_ptm2af)													//等待DHT結束Response	
	{	if(_ptm2pf) { _pt2on=0;	 return 0;}							//超過時間未回應,讀取錯誤
	} 
	_pt2on=0;
	TCnt=_ptm2ah; TCnt=(TCnt<<8)|_ptm2al;							//取得捕捉值
	if(TCnt<TresMin) return 0;										//Response信號過短,讀取錯誤 
	while(temp1!=0)													//取得32-Bit資料
	{	_ptm2af=0; _pt2on=1;										//啟動Capture
		while(!_ptm2af);											//等待負緣捕捉		
		_pt2on=0;
		TCnt=(u16)_ptm2ah<<8; TCnt|=_ptm2al;						//取得捕捉值	
		if(TCnt>Tbit) temp|=temp1;									//0:78us, 1:120us
		temp1>>=1;
	}
	temp1=(u32)1<<7;	 											//取得Check Sum
	while(temp1!=0)
	{	_ptm2af=0; _pt2on=1;										//啟動Capture
		while(!_ptm2af);											//等待負緣捕捉
		_pt2on=0;
		TCnt=(u16)_ptm2ah<<8; TCnt|=_ptm2al;						//取得捕捉值	
		if(TCnt>Tbit) parity|=temp1;
		temp1>>=1;
	}
	while(!pDHT);													//等待End Signal結束
	TCnt=(u8)temp;													//計算 Checksum
	TCnt+=temp>>8;
	TCnt+=temp>>16;
	TCnt+=temp>>24;
	if((u8)TCnt!=parity) return 0;									//Checksum Error
	*ptrt=temp; *ptrh=temp>>16;										//取得溫度、濕度
	return 1;														//回傳1(正確讀取)
}