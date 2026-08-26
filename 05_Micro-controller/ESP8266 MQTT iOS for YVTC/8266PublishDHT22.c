// PROGRAM	: 8266PublishDHT22.c										2024.0422
// FUNCTION	: Publish DHT22 Data and Tx Count(@11.059MHz)				By Steven
// NOTE		: UAR1 is used, ESP Firmware AT Version:1.2.0.0 
//			: for Iot MQTT APP, 
// HARDWARE	: PF0->eDisplay LED1, PF1->eDisplay LED2, PF2->eDisplay LED3
//			  PB3->DHT22 
// in MQTT.h: QoS=0	
#include <HT66F2390.h>
#include "ESP8266V9.H"
#include "MQTT.H"
#include "eDisplayV2.H"
#include <string.h>
#include <math.h>
#include "DHTSeries.h"
const s8* clientID=NULL;                       							//用戶端ID,搭配Broker設置
const s8* mqttUser=NULL;												//搭配Broker設置
const s8* mqttPswd=NULL;												//搭配Broker設置

#define topicT "/YVTCxxx/dht22/temp"    								//Publish Topic(1),搭配IoT MQTT設置，修正xxx為自己的學號
#define topicH "/YVTCxxx/dht22/humi"    								//Publish Topic(2),搭配IoT MQTT設置，修正xxx為自己的學號
#define topicI "/YVTCxxx/dht22/i"    									//Publish Topic(3),搭配IoT MQTT設置，修正xxx為自己的學號
#define	TopicCNT	3													//Sensor ID
const u8 sensorID[TopicCNT][25]={topicT,topicH,topicI};					//
extern u8 aliveCnt;
u8 ReadDHT(s16* ptrh,s16* ptrt);
void main()
{	s16 h,t; u8 tCnt=0,idx,ASCII[8];	
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
	pDHTPU=1; pDHTC=1;													//DHT Series資料腳位規劃
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
//		GCC_NOP(); 
	}
	while(!GetIP());													//取得分配之IP
	eDisplayStr(6,35,(u8*)"Wait Broker....");
	while(!SetUpConnection(0,0,(u8*)"TCP",(u8*)mqttServer,1883));		//連線至CHT IoT Server
	while(!LEDControl(mqttConnect()));									//建立MQTT連線
	eDisplayStr(6,35,(u8*)"Broker Connect!");
	eDisplayStr(6,60,(u8*)"Temp=");
	eDisplayChar(104,52,'o'); eDisplayChar(113,60,'C');
	eDisplayStr(6,80,(u8*)"Humi=");
	eDisplayChar(108,80,'%');
	eDisplayStr(6,100,(u8*)"TCnt=");
	while(1)
	{	if(ReadDHT(&h,&t)==1)
		{	for(idx=0;idx<TopicCNT;idx++)
			{	switch(idx)
				{	case 0:	word2string(ASCII,t,4);
							break;
					case 1:	word2string(ASCII,h,4);
							break;
					case 2:	word2string(ASCII,tCnt++,0);
				}														
				eDisplayRet(48,56,60+(idx*20),12,BackColor); 
				eDisplayStr(48,60+(idx*20),(u8*)ASCII);
				LEDControl(mqttPublishIotMqtt((u8*)&sensorID[idx][0],ASCII));
				Delayms(100);
			}														
			Delayms(1800);												//注意時間間隔太短,發佈似乎LOSS嚴重
		}
	}
}
u8 ReadDHT(s16* ptrh,s16* ptrt)
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