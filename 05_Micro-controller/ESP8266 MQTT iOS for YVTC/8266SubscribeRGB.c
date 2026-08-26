// PROGRAM	: 8266SubscribeRGB.c	(RGB LED PWM Controll)			2024.0506
// FUNCTION	: ESP8266 Command Test for HT66Fxx(@11.059)				By Steven
// NOTE		: UAR1 is used, ESP Firmware AT Version:1.2.0.0 
//			: for Iot MQTT APP
// HARDWARE	: PF0->eDisplay LED1, PF1->eDisplay LED2, PF2->eDisplay LED3
//			  PC0->RGB LED-R, PC2->RGB LED-G, PC4->RGB LED-B
// in MQTT.h: QoS=0					
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "MQTT.H"
#include "eDisplayV2.H"
#include <string.h>
#include <stdlib.h>
const s8* clientID=NULL;                       						//用戶端ID,搭配Broker設置
const s8* mqttUser=NULL;											//搭配Broker設置
const s8* mqttPswd=NULL;											//搭配Broker設置

const s8* filter1="/YVTCxxx/pwm/#";    								//Subscribe Topic,/YVTCxxx/rgb/下所有主題，修正xxx為自己的學號
#define	SENSOR1	"/YVTCxxx/pwm/r"									//感測器名稱(1),搭配 IoT MQTT APP，修正xxx為自己的學號
#define	SENSOR2	"/YVTCxxx/pwm/g"									//感測器名稱(2),搭配 IoT MQTT APP，修正xxx為自己的學號
#define	SENSOR3	"/YVTCxxx/pwm/b"									//感測器名稱(2),搭配 IoT MQTT APP，修正xxx為自己的學號
#define SensorCNT 3

extern u8 aliveCnt, hbPID, lbPID;//, sQoS;;
const u8  sensorID[SensorCNT][30]={SENSOR1,SENSOR2,SENSOR3};		//
void main()
{	u8 i,remLen,command,*volatile ptr; u16 tmp;										
	_wdtc=0xAA; _rstc=0xAA;											//關閉看門狗計時器,PB5 as RESET
	_pbs1=0xF0; _hxtm=1;											//指定PB[7:6]為OSC功能
	_hxten=1; while(!_hxtf);										//致能HXT並等待穩定
	_fhs=1; _hircen=0;												//選擇fH為HXT,關閉HIRC
	pERLED=!LEDOff; pEGLED=!LEDOff; pEBLED=!LEDOff;					//eDisplay LED Control Pin(Active Low!!!)
	pERLEDC=0; 		pEGLEDC=0; 		pEBLEDC=0;	

	_u1cr1=0b10000000;												//UARTEN1/8-Bit/No_parity//1 Stop Bit///
	_u1cr2=0b10100100;												//TXEN1/RXEN1/BRGH1/RIE1//	
	_brg1=fH/((u32)16*BR)-1;										//BRGH1=1
 	_pds0=0x28;	_rx1ps=0;											//設置腳位功能 TX1->PD2,RX1->PD1
 	_psc1r=0x01; _tb1c=0x01; _tb1f=0; _tb1e=1;						//fTB1=fSYS/4,(4/fSYS)*512 (資料接收等待單位時間185us) 	
 	_psc0r=0x02; _tb0c=0x07; _tb0f=0; _tb0e=1;						//fTB0=fSUB,(1/fSUB)*2^15(KeepAlive等待單位時間)
	_pcs0=0x20; _pcs1=0x22;											//PC2->PTP0(R),PC4->PTP1(G), PC6->STP0(B)
	_ptm0al=0; _ptm0ah=0;											//Duty=0	
	_ptm0rpl=0; _ptm0rph=2;											//PWM 週期=1024/fINT
	_ptm0c0=0b00111000;												//fINT=fSYS/64,PT0ON=1
	_ptm0c1=0b10101000;												//PWM模式,Active High
	_ptm1al=0; _ptm1ah=0;											//Duty=0	
	_ptm1rpl=0;	_ptm1rph=1;											//PWM 週期=1024/fINT
	_ptm1c0=0b00111000;												//fINT=fSYS/64,PT1ON=1
	_ptm1c1=0b10101000;												//PWM模式,Active High
	_stm0al=0; _stm0ah=0;											//Duty=0	
	_stm0rp=2;														//PWM 週期=1024/fINT
	_stm0c0=0b00111000;												//fINT=fSYS/64,ST0ON=1
	_stm0c1=0b10101000;												//PWM模式,Active High,STM0RP控制週期
 	
	HardRESET8266(0);												//RESET 8266後才能致能中斷,避開RESET階段回送之訊息
	eDisplayReset();
	eDisplayRet(0,128,0,128,BackColor);
	eDisplayStr(8,10,(u8*)"MQTT SUBSCRIBE");
	_mf5e=1; _ur1e=1;												//致能UART0中斷
	_emi=1;															//致能中斷
	CmdLen=0;
	while(!ATE0());
	while(!UART_CUR(BRH));
	_brg1=fH/((u32)16*BRH)-1;										//BRGH1=1	

	while(!SetWiFiMode(STA));									
	while(!SetConnectionMode(SINGLE));	
	eDisplayStr(6,35,(u8*)"Wait SSID......");

	while(1)
	{	if(JointAP((u8*)SSID,(u8*)PSWD)==TRUE) break;
//		GCC_NOP(); 
	}
 	while(!GetIP());
 	eDisplayStr(6,35,(u8*)"Wait Broker....");	
	while(!SetUpConnection(0,0,(u8*)"TCP",(u8*)mqttServer,1883));	
	while(!LEDControl(mqttConnect()));
	_tb0on=1; aliveCnt=0;											//啟動Alive Time Unit Counter(1 Sec.)	
	eDisplayStr(6,35,(u8*)"Broker Connect!");

	while(!mqttSubscribe((u8*)filter1));
	BackColor=Black;
	eDisplayRet(0,128,52,128,BackColor);
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
	eDisplayStr(30, 60,(u8*)"RLED:");
	eDisplayStr(30, 80,(u8*)"GLED:");	
	eDisplayStr(30,100,(u8*)"BLED:");
	
	while(1)
	{	command=mqtt_Receive(&remLen);
		if(command!=0)
		{	LEDControl(1);													//若有收到
			switch(command&0xF0)
			{	case PUBLISH:
					if(command & (1<<3)) eDisplayChar(2,113,'1');			//顯示DUP
					else eDisplayChar(2,113,'0');			
					for(i=0;i<SensorCNT;i++)
					{	ptr=myFindStr((u8*)RxBuf0,(u8*)&sensorID[i][0],RxCount);
						if(ptr==0) continue;
						else ptr+=strlen((char*)&sensorID[i][0]);				//移至Payload起始位址(QoS=0)				
						tmp=atoi((const char*)ptr);								//取得Payload並轉成整數值
						switch(i)
						{	case 0: _ptm0al=tmp; _ptm0ah=tmp>>8;				//Set R Duty
									break;
							case 1: _ptm1al=tmp; _ptm1ah=tmp>>8;				//Set G Duty
									break;
							case 2: _stm0al=tmp; _stm0ah=tmp>>8;				//Set B Duty
						}
						eDisplayRet(75,32,59+(i*20),12,BackColor);				//清除前一次Payload值
						eDisplayStr(75,59+(i*20),ptr);							//顯示Payload值
					}
			}
		}
		if(aliveCnt>Alive-10)												//每隔1.125 Alive的時間,發出連線要求(aliveCnt會於TB0 ISR中遞增)
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
