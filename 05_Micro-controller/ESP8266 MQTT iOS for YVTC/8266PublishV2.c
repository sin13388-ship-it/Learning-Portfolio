// PROGRAM	: 8266PublishV2.c										2024.0506
// FUNCTION	: Publish to ThingSpeak(@11.059)						By Steven
// NOTE		: UAR1 is used, ESP Firmware AT Version:1.2.0.0 
//			: for Iot MQTT APP, 
// HARDWARE	: PF0->eDisplay LED1, PF1->eDisplay LED2, PF2->eDisplay LED3
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "MQTT.H"
#include "eDisplayV2.H"
#include <string.h>
#include <math.h>
const s8* clientID=NULL;                       						//用戶端ID,搭配Broker設置
const s8* mqttUser=NULL;											//搭配Broker設置
const s8* mqttPswd=NULL;											//搭配Broker設置

#define	topicR	"/YVTCxxx/led/r"									//Publish Topic(1),搭配IoT MQTT設置，修正xxx為自己的學號
#define	topicG	"/YVTCxxx/led/g"									//Publish Topic(2),搭配IoT MQTT設置，修正xxx為自己的學號
#define	topicB	"/YVTCxxx/led/b"									//Publish Topic(3),搭配IoT MQTT設置，修正xxx為自己的學號
#define	TopicCNT	3												//Sensor ID
const u8 sensorID[TopicCNT][25]={topicR,topicG,topicB};				//
const u16 colorTab[3]={Red,Green,Blue};		

#define	pBtnR	_pe2
#define	pBtnG	_pe1
#define	pBtnB	_pe0
#define	pBtnRC	_pec2
#define	pBtnGC	_pec1
#define	pBtnBC	_pec0
#define	pBtnRPU	_pepu2
#define	pBtnGPU	_pepu1
#define	pBtnBPU	_pepu0
extern u8 aliveCnt;
void main()
{	u8 btnState=0,btn,i;
	_wdtc=0xAA; _rstc=0xAA;											//關閉看門狗計時器,PB5 as RESET
	_pbs1=0xF0; _hxtm=1;											//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);										//致能HXT並等待穩定
	_fhs=1; _hircen=0;												//選擇fH為HXT,關閉HIRC
	pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff;					//eDisplay LED Control Pin(Active Low!!!)
	pERLEDC=0; 		pEGLEDC=0; 		pEBLEDC=0;	
	pBtnRC=1; pBtnGC=1; pBtnBC=1; pBtnRPU=1; pBtnGPU=1; pBtnBPU=1;  	

	_u1cr1=0b10000000;												//UARTEN1/8-Bit/No_parity//1 Stop Bit///
	_u1cr2=0b10100100;												//TXEN1/RXEN1/BRGH1/RIE1//	
	_brg1=fH/((u32)16*BR)-1;										//BRGH1=1,19200
 	_pds0=0x28;	_rx1ps=0;											//設置腳位功能 TX1->PD2,RX1->PD1
 	_psc1r=0x01; _tb1c=0x01; _tb1f=0; _tb1e=1;						//fTB1=fSYS/4,(4/fSYS)*512 (資料接收等待單位時間185us) 	
  	_psc0r=0x02; _tb0c=0x07; _tb0f=0; _tb0e=1;						//fTB0=fSUB,(1/fSUB)*2^15(KeepAlive等待單位時間1.024s)
	HardRESET8266(0);												//RESET 8266後才能致能中斷,避開RESET階段回送之訊息
	eDisplayReset(); 
	eDisplayRet(0,128,0,128,BackColor); 
	eDisplayStr(16,10,(u8*)"MQTT PUBLISH");
	_mf5e=1; _ur1e=1;												//致能UART0中斷
	_emi=1;															//致能中斷
	CmdLen=0;
	while(!ATE0());													//設置ESP-01不回應命令
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;										//BRGH1=1,230400	
	while(!SetWiFiMode(STA));										//設置ESP-01為Station模式								
	while(!SetConnectionMode(SINGLE));								//設置ESP-01為單點傳輸	
	eDisplayStr(6,35,(u8*)"Wait SSID......");
	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
//		GCC_NOP(); 
	}
	while(!GetIP());												//取得分配之IP
	eDisplayStr(6,35,(u8*)"Wait Broker....");
	while(!SetUpConnection(0,0,(u8*)"TCP",(u8*)mqttServer,1883));	
	eDisplayStr(6,35,(u8*)"Broker Connect!");
	mqttConnect();
	aliveCnt=0;	_tb0on=1; 											//啟動Alive Time Unit Counter(1 Sec)
	BackColor=Black; eDisplayRet(0,128,52,128,BackColor);	
	eDisplayStr(30, 60,(u8*)"RLED:");								//設定初始狀態 OFF
	eDisplayStr(30, 80,(u8*)"GLED:");	
	eDisplayStr(30,100,(u8*)"BLED:");
	LEDControl(mqttPublishIotMqtt((u8*)topicR,(u8*)"0"));			//發布初始狀態 OFF
	LEDControl(mqttPublishIotMqtt((u8*)topicG,(u8*)"0"));
	LEDControl(mqttPublishIotMqtt((u8*)topicB,(u8*)"0"));
	while(1)
	{	if(!(pBtnR && pBtnG && pBtnB))								//任一鍵被按
		{	Delayms(80);											//同時接受多個按鍵(80ms內)
			btn=(pBtnR<<2)|(pBtnG<<1)|(pBtnB<<0);					//取得按鍵狀態
			for(i=0;i<TopicCNT;i++)
			{	if(!(btn & (1<<(2-i))))								//順序:pBtnx(x=R,G,B)按下?
				{	btnState^=(1<<(2-i));									//改變對應按鍵之狀態
					if(btnState & (1<<(2-i)))
					{	LEDControl(mqttPublishIotMqtt((u8*)&sensorID[i][0],(u8*)"1"));
						eDisplayRet(75,24,59+(i*20),16,colorTab[i]);
					}
					else
					{	LEDControl(mqttPublishIotMqtt((u8*)&sensorID[i][0],(u8*)"0"));
						eDisplayRet(75,24,59+(i*20),16,BackColor);
					}
				}
			}
			aliveCnt=0;												//alive計時器歸零
		}
		else 
		{	if(aliveCnt>Alive-10)									//每隔1.25 Alive的時間,發出連線要求(aliveCnt會於TB0 ISR中遞增)
			{	mqttPingReq();										//依手冊所敘，若超過1.5倍Alive未收到Client送出的Command Packet,
				aliveCnt=0;											//Broker會視為Network Failed而自動斷線!!!
			}
		}			
	}
}