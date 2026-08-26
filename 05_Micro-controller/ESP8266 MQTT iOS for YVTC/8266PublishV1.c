// PROGRAM	: 8266PublishV1.c											2024.0422
// FUNCTION	: Publish to ThingSpeak(@11.059)							By Steven
// NOTE		: UAR1 is used, ESP Firmware AT Version:1.2.0.0 
//			: for Iot MQTT APP,
// HARDWARE	: PF0->eDisplay LED1, PF1->eDisplay LED2, PF2->eDisplay LED3
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "MQTT.H"
#include "eDisplayV2.H"
#include <string.h>
#include <math.h>
const s8* clientID=NULL;                       							//用戶端ID,搭配Broker設置
const s8* mqttUser=NULL;												//搭配Broker設置
const s8* mqttPswd=NULL;												//搭配Broker設置

#define topicT "/YVTCxxx/dht22/temp"    								//Publish Topic(1),搭配IoT MQTT設置，修正xxx為自己的學號
#define topicH "/YVTCxxx/dht22/humi"    								//Publish Topic(2),搭配IoT MQTT設置，修正xxx為自己的學號
#define topicI "/YVTCxxx/dht22/i"    									//Publish Topic(3),搭配IoT MQTT設置，修正xxx為自己的學號
#define	TopicCNT	3													//Sensor ID

const u8 sensorID[TopicCNT][25]={topicT,topicH,topicI};					//
extern u8 aliveCnt;
void main()
{	s16 raw; u8 i,idx,ASCII[8];	
	_wdtc=0xAA; _rstc=0xAA;												//關閉看門狗計時器,PB5 as RESET
	_pbs1=0xF0; _hxtm=1;												//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);											//致能HXT並等待穩定
	_fhs=1; _hircen=0;													//選擇fH為HXT,關閉HIRC
	pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff;						//eDisplay LED Control Pin(Active Low!!!)
	pERLEDC=0; 		pEGLEDC=0; 		pEBLEDC=0;	

	_u1cr1=0b10000000;													//UARTEN1/8-Bit/No_parity//1 Stop Bit///
	_u1cr2=0b10100100;													//TXEN1/RXEN1/BRGH1/RIE1//	
	_brg1=fH/((u32)16*BR)-1;											//BRGH1=1,19200
 	_pds0=0x28;	_rx1ps=0;												//設置腳位功能 TX1->PD2,RX1->PD1
 	_psc1r=0x01; _tb1c=0x01; _tb1f=0; _tb1e=1;							//fTB1=fSYS/4,(4/fSYS)*512 (資料接收等待單位時間185us) 	
 	_psc0r=0x02; _tb0c=0x07; _tb0f=0; _tb0e=1;							//fTB0=fSUB,(1/fSUB)*2^15(KeepAlive等待單位時間1.024s)
	HardRESET8266(0);													//RESET 8266後才能致能中斷,避開RESET階段回送之訊息
	eDisplayReset(); 
	eDisplayRet(0,128,0,128,BackColor); 
	eDisplayStr(16,10,(u8*)"MQTT PUBLISH");
	_mf5e=1; _ur1e=1;													//致能UART0中斷
	_emi=1;																//致能中斷
	CmdLen=0;
	while(!ATE0());														//設置ESP-01不回應命令
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;											//BRGH1=1,230400	

	while(!SetWiFiMode(STA));											//設置ESP-01為Station模式								
	while(!SetConnectionMode(SINGLE));									//設置ESP-01為單點傳輸	
	eDisplayStr(6,35,(u8*)"Wait SSID......");
	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
		GCC_NOP(); 
	}
	while(!GetIP());													//取得分配之IP
	while(1)
	{	eDisplayStr(6,35,(u8*)"Wait Broker....");
		while(!SetUpConnection(0,0,(u8*)"TCP",(u8*)mqttServer,1883));	//連線至CHT IoT Server
		while(!LEDControl(mqttConnect()));								//建立MQTT連線
		eDisplayStr(6,35,(u8*)"Broker Connect!");
		eDisplayStr(6,60,(u8*)"Temp=");
		eDisplayChar(104,52,'o'); eDisplayChar(113,60,'C');
		eDisplayStr(6,80,(u8*)"Humi=");
		eDisplayChar(108,80,'%');
		eDisplayStr(6,100,(u8*)"   i=");

		for(i=0;i<=199;i+=10)
		{	for(idx=0;idx<TopicCNT;idx++)
			{	switch(idx)
				{	case 0:	raw=10000*sin(2*PI*i/200);
							word2string(ASCII,raw,3);
							break;
					case 1:	raw=5000*cos(2*PI*i/200)+5000;
							word2string(ASCII,raw,3);
							break;
							
					case 2:	word2string(ASCII,i,0);
							break;
				}														
				eDisplayRet(48,56,60+(idx*20),12,BackColor); 
				eDisplayStr(48,60+(idx*20),(u8*)ASCII);
				LEDControl(mqttPublishIotMqtt((u8*)&sensorID[idx][0],ASCII));
				Delayms(250);
			}	
			Delayms(1000);														//注意時間間隔太短,CHT的發佈似乎LOSS嚴重
		}
		while(!LEDControl(mqttDisconnect()));									//關閉MQTT連線								
		eDisplayRet(0,128,35,128,BackColor);
		eDisplayStr(0,35,(u8*)"MQTT Disconnect!");
		Delayms(3000);	
		eDisplayRet(0,128,35,128,BackColor);	
	}
}
