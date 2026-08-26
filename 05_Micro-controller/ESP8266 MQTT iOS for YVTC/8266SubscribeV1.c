// PROGRAM	: 8266SubscribeV1.c											2024.0506
// FUNCTION	: ESP8266 Command Test for HT66Fxx(@11.059)					By Steven
// NOTE		: UAR1 is used, ESP Firmware AT Version:1.2.0.0 
//			: for Iot MQTT APP, 
// HARDWARE	: PF0->eDisplay LED1, PF1->eDisplay LED2, PF2->eDisplay LED3,
// in MQTT.h: QoS=0				
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "MQTT.H"
#include "eDisplayV2.H"
#include <string.h>				
#include <stdlib.h>			
const s8* clientID=NULL;                       							//用戶端ID,搭配Broker設置
const s8* mqttUser=NULL;												//搭配Broker設置
const s8* mqttPswd=NULL;												//搭配Broker設置

const s8* filter1="/YVTCxxx/dht22/#";    								//Subscribe Topic,/YVTCxxx/dht22/下所有主題，修正xxx為自己的學號
#define	SENSOR1	"/YVTCxxx/dht22/temp"									//感測器名稱(1),搭配IoT MQTT App設置，修正xxx為自己的學號
#define	SENSOR2	"/YVTCxxx/dht22/humi"									//感測器名稱(2),搭配IoT MQTT App設置，修正xxx為自己的學號
#define	SENSOR3	"/YVTCxxx/dht22/i"										//感測器名稱(3),搭配IoT MQTT App設置，修正xxx為自己的學號

#define SensorCNT 3
extern u8 aliveCnt, hbPID, lbPID;
const u8  sensorID[SensorCNT][30]={SENSOR1,SENSOR2,SENSOR3};			//
 void main()
{	u8 i,remLen,command,*volatile ptr;
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
	eDisplayStr(8,10,(u8*)"MQTT SUBSCRIBE");
	_mf5e=1; _ur1e=1;													//致能UART0中斷
	_emi=1;																//致能中斷
	CmdLen=0;
	while(!ATE0());														//設置ESP-01不回應命令
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;											//BRGH1=1,115200

	while(!SetWiFiMode(STA));											//設置ESP-01為Station模式								
	while(!SetConnectionMode(SINGLE));	
	eDisplayStr(6,35,(u8*)"Wait SSID......");							//設置ESP-01為單點傳輸	

	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
//		GCC_NOP(); 
	}
 	while(!GetIP());
 	eDisplayStr(6,35,(u8*)"Wait Broker....");
	while(!SetUpConnection(0,0,(u8*)"TCP",(u8*)mqttServer,1883));	
	while(!LEDControl(mqttConnect()));
	aliveCnt=0;	_tb0on=1; 													//啟動Alive Time Unit Counter(1 Sec)
	eDisplayStr(6,35,(u8*)"Broker Connect!");						

	while(!mqttSubscribe((u8*)filter1));									//
	ptr=(u8*)strstr((char*)RxBuf0,(char*)":")+5;							//ptr指向: (+IPD,xxx:CMD_LEN_HPID_LPID_ReturnCode)
	eDisplayChar(115,113,*ptr+'0');											//顯示Broker支援的QoS	 
 
	while(QoS>*ptr)															//若QoS設置超過Broker支援的Level
	{	eDisplayStr(0,35,(u8*)"     Modify     ");	
		eDisplayStr(0,55,(u8*)"  QoS Setting!  ");	
		BackColor=Red;														//顯示警示訊息,提示修改MQTT.h中QoS之設置
		eDisplayChar(115,113,*ptr+'0');										//顯示Broker支援的QoS	 
		LEDControl(0);
		eDisplayRet(110,18,110,18,Red);	
		Delayms(500);
	}
	eDisplayStr(6,60,(u8*)"Temp=");
	eDisplayChar(104,52,'o'); eDisplayChar(113,60,'C');
	eDisplayStr(6,80,(u8*)"Humi=");
	eDisplayChar(108,80,'%');
	eDisplayStr(6,100,(u8*)"fld3=");
/*	
	if(LEDControl(mqttUnSubscribe((u8*)filter1)))							//注意：for測試UNSUBSCRIBE測試命令
	{	LEDControl('R');													//此時PINGREQ命令將一直執行失敗
	}
*/	
	while(1)
	{	command=mqtt_Receive(&remLen);										//等待Alive-10的時間接收資料
		if(command!=0)														//
		{	LEDControl(1);													//若有收到
			switch(command&0xF0)
			{	case PUBLISH:
					if(command & (1<<3)) eDisplayChar(2,113,'1');			//顯示DUP
					else eDisplayChar(2,113,'0');			
					for(i=0;i<SensorCNT;i++)
					{	ptr=myFindStr((u8*)RxBuf0,(u8*)&sensorID[i][0],RxCount);
						if(ptr==0) continue;								//找不到主題
						ptr+=strlen((char*)&sensorID[i][0]);				//移至Payload起始位址(QoS=0)				
						eDisplayRet(48,56,i*20+60,12,BackColor);			//清除之前接收數值
						eDisplayStr(48,i*20+60,(u8*)ptr);					//顯示本次接收數值
					}
			}
						
		}
		if(aliveCnt>Alive-10)												//每隔1.25 Alive的時間,發出連線要求(aliveCnt會於TB0 ISR中遞增)
		{	while(1)														//依手冊所敘，若超過1.5倍Alive未收到Client送出的Command Packet,
			if(mqttPingReq())
			{	LEDControl(2);						
				break;
			}
			else  LEDControl(0);	
			aliveCnt=0;														//Broker會視為Network Failed而自動斷線!!!
		}		
	}
}
