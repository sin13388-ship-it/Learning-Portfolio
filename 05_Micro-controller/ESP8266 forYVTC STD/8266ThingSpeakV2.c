// PROGRAM	: 8266ThingSpeakV2.c									2026.0225
// FUNCTION	: ESP8266 Command Test for HT66F23xx(@11.059)			By Steven
//   Note   : 非固定IP,故欲控制的PC或手機與ESP01必須屬同一網域
//			  手機熱點分享，iOS請開啟最大相容性、Android請關閉WiFi連線	

#define	SSID	"VeraiPhone"										//改成自己的手機熱點
#define	PSWD	"44445555"									//改成自己的手機熱點密碼

#define ConIP	"api.thingspeak.com"								//欲連線的IP
#define UPDATE	"GET /update?key=4LD8L3Z46DZKS6YQ"				//改成自己的Channel Write API Key
//*** ====================================================================

#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "eDisplayV2.H"
#include <string.h>
#include <math.h>
extern volatile u8  Wait,*ptrBuf,RxCount;
extern volatile u16 CmdLen,rxTotalCnt;
DEFINE_SFR(u8, TxBuf[BufLen], 0xA80);								//Bank A:80h~FFh
void main()
{	u8 i,*ptr; s16 temp;
	u8	ASCII[7];													//符號+5位數數值+NULL
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
	eDisplayStr(10,10,(u8*)"ThingSpeak V2");
	_mf5e=1; _ur1e=1;												//致能UART0中斷
	_emi=1;															//致能中斷
	CmdLen=0;
	while(!ATE0());													//停止命令ECHO
	while(!UART_CUR(BRH));											//暫時提升ESP01 Baud Rate
	_brg1=fH/((u32)16*BRH)-1;										//BRGH1=1	
	eDisplayStr(6,35,(u8*)"Wait SSID......");
	while(!SetWiFiMode(STA));										//Station Mode	
	while(!SetConnectionMode(SINGLE));								//Single Mode
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
	eDisplayStr(10,60,(u8*)"Field1=");
	eDisplayStr(10,76,(u8*)"Field2=");
	eDisplayStr(10,99,(u8*)"RspCnt:");								//Response Count
	while(1)
	{	for(i=0;i<255;i+=8)
		{	if(SetUpConnection(0,0,(u8*)"TCP",(u8*)ConIP,80)!=0)
			{	strcpy((char*)TxBuf,UPDATE);
				strcat((char*)TxBuf,"&field1=");
		    	Word2String(i,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    	eDisplayStr(70,60,(u8*)"   ");						//清除先前顯示資料
				eDisplayStr(70,60,(u8*)ASCII);						//顯示filed1資料	
		    	strcat((char*)TxBuf,(char*)"&field2=");
		    	temp=1500*sin(2*PI*i/255);
		    	Word2String(temp,ASCII); strcat((char*)TxBuf,(char*)ASCII);
		    	eDisplayStr(70,77,(u8*)"     ");					//清除先前顯示資料
				eDisplayStr(70,77,(u8*)ASCII);						//顯示filed2資料
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
//				CloseConnection(0,0);
			}
			Delayms(16000);
		}
	}
}