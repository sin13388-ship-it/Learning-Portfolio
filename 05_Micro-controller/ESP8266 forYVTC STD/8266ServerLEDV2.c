// PROGRAM	: 8266ServerLEDV2.c								   	2026.0225
// FUNCTION	: ESP8266 Command Test  for HT66F23xx(@11.059)		By Steven
//   Note   : 非固定IP,故欲控制的PC或手機與ESP01必須屬同一網域
//			  手機熱點分享，iOS請開啟最大相容性、Android請關閉WiFi連線	

#define	SSID	"thmrb311"										
#define	PSWD	"thmrbthmrb"

							

//*** =========================================================
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "eDisplayV2.H"
#include "WebPage.H"
#include <string.h>
void HTTPResponse(u8 LEDState);
extern volatile u8 *ptrBuf,RxCount;
extern volatile u16 CmdLen,rxTotalCnt, Wait;
DEFINE_SFR(u8, RxBuf2[BufLen], 0x0C80);							//Bank B:80h~FFh
void main()
{	volatile u8 LED=0,State,*ptr;
	_wdtc=0b10101111;											//關閉WDT
	_pbs1=0xF0; _hxtm=1;										//指定PB[7:6]為OSC功能
	_rstc=0xAA;													//PB5 as Reset Pin
	_hxten=1; while(!_hxtf);									//致能HXT並等待穩定
	_fhs=1; _hircen=0;											//選擇fH為HXT,關閉HIRC
	pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff;				//eDisplay LED Control Pin(Active Low!!!)
	pERLEDC=0; 		pEGLEDC=0; 		pEBLEDC=0;	
	pRLED=LEDOff; pGLED=LEDOff; pBLED=LEDOff;					//ESK310 RGB LED
	pRLEDC=0; pGLEDC=0; pBLEDC=0;	
	_pds0=0x28;	_rx1ps=0;										//設置腳位功能 TX1->PD2,RX1->PD1
	_u1cr1=0b10000000;											//UARTEN1/8-Bit/No_parity//1 Stop Bit///
	_u1cr2=0b10100100;											//TXEN1/RXEN1/BRGH1/RIE1//	
	_brg1=fH/((u32)16*BR)-1;									//BRGH1=1
 	_psc1r=0x01; _tb1c=0x00; _tb1f=0; _tb1e=1;					//fTB1=fSYS/4,(4/fSYS)*256 (資料接收等待單位時間92.5us) 
   
 	HardRESET8266(0);											//RESET 8266後才能致能中斷,避開RESET階段回送之訊息
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	eDisplayStr(10,10,(u8*)"ServerLED V2");
	_mf5e=1; _ur1e=1; _emi=1;									//致能UART1中斷,致能中斷
	CmdLen=0;
	while(!ATE0());
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;									//BRGH1=1
	eDisplayStr(6,35,(u8*)"Wait SSID......");
	while(!SetWiFiMode(STA));					
	while(!SetConnectionMode(MULTIPLE));
	while(!ConfigTcpServer(1,80));								//Only for CIPMUX=1	
	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
//		GCC_NOP(); 
	}					
	eDisplayRet(0,128,35,12,BackColor);							//清除"Wait SSID......"
 	while(!GetIP());											//設置斷點查詢IP	

	eDisplayRet(2,124,64,62,Black);	

  	ptr=(u8*)strichr((char*)RxBuf0,(int)'\"');					//找第一個"位址
 	ptr=(u8*)strichr((char*)(ptr+1),(int)'\"');					//找第二個"位址
 	*ptr=0;														//塞入結束字元
 	ptr=(u8*)strichr((char*)RxBuf0,(int)'\"');					//找第一個"位址
	eDisplayStr(10,35,(u8*)(ptr+1));							//顯示分配之IP	
	while(1)
	{	State=NetRxData((u8*)RxBuf2); 
		switch (State)
		{	case HTTP:
				LED=0;
				if(strstr((char*)RxBuf2,(char*)"R1"))
				{	LED=1;
					eDisplayRet(7,30,86,30,Red);
				}
				else eDisplayRet(8,28,87,28,Black);
				
				if(strstr((char*)RxBuf2,(char*)"G1"))
				{	LED|=2;
					eDisplayRet(49,30,86,30,Green);
				}
				else eDisplayRet(50,28,87,28,Black);
				
				if(strstr((char*)RxBuf2,(char*)"B1"))
				{	LED|=4;
					eDisplayRet(90,30,86,30,Blue);
				}
				else eDisplayRet(91,28,87,28,Black);
				pRLED=(LED & 1<<0)? LEDOn : LEDOff;
				pGLED=(LED & 1<<1)? LEDOn : LEDOff;
				pBLED=(LED & 1<<2)? LEDOn : LEDOff;
			case GET:
				HTTPResponse(LED);	
				break;
		}
	}
}
void HTTPResponse(u8 LEDState)			
{	u8 ch; u16 packetlen=0;
	const char *ptr[6];		
	ptr[0]=HTTPHeader; ptr[1]=WebPage1; ptr[5]=WebPage5;
	ptr[2]=(LEDState & (1<<0))? WebPage2_1:WebPage2;
	ptr[3]=(LEDState & (1<<1))? WebPage3_1:WebPage3;
	ptr[4]=(LEDState & (1<<2))? WebPage4_1:WebPage4;		
	for(ch=0;ch<6;ch++) packetlen+=strlen(ptr[ch]);				//計算傳送至8266的字元長度	
	while(packetlen>2048) LEDControl(1);						//超過長度終極死圈(8266 每個Packet上限2048)	
	ch=*(strstr((char*)RxBuf2,"IPD,")+4);						//取得Channel ID
	while(CIPSendLen(MULTIPLE,ch,packetlen)!=1);				//ESP-01當成Server時,ID由Client決定,此時需判定+IPD後之字元
	for(ch=0;ch<6;ch++)											//送出表頭及HTML內容
	{	while(*ptr[ch]!=NULL) 
		{	while(!_txif1);										//等待資料送至TSR
			_txr_rxr1=*ptr[ch]++;								//送出資料至TXR
		}
	}
	ptrBuf=RxBuf2; *ptrBuf=NULL; RxCount=0; Wait=0;
	_rxen1=1;													//啟動UART接收
	while(RxCount==0);											//等待資料接收
	 _tb1on=1;													//一旦收到資料，超時未收到資料機制啟動				
	while(Wait<20*8)											//若未超時,尋找是否有指定之回應字串
	{	if(strstr((char*)RxBuf2,(char*)"CLOSED")!=NULL) 
			break;												//跳離while(Wait<10)迴圈
	}
	_tb1on=0; 	
	_rxen1=0;													//關閉UART接收
}