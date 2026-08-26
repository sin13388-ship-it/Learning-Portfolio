//2024.0322   for All QOS Level for 3.1.1 
#include <HT66F2390.h>												//20230330 增加TB0 ISR做為PingRequest發布時機的計時單位(秒)與aliveCnt變數
#include "ESP8266V9.H"
#include "MQTT.H"
#include <string.h>
#include <stdlib.h>
extern s8 *clientID,*mqttUser,*mqttUser,*mqttPswd;
const u8  ConVarHeader[10]={0,4,'M','Q','T','T',PLevel,ConFlag,(u8)(Alive>>8),(u8)Alive};
volatile u8 aliveCnt=0, hbPID=0,lbPID=0;//,sQoS;					//(去掉vol... aliveCnt1不會清除)packetID Hi/Lo-Byte, real QoS

DEFINE_ISR(ISR_TB0,0x24)
{	aliveCnt++;														//aliveCnt+1
}
u8 mqttConnect(void)
{	DEFINE_SFR(u8, payload[128], 0x1080);							//Bank 16:80h~FFh
	u8 paylen,len; u8 *ptr,*ptrpay=(u8*)payload;						
	ptr=(u8*)clientID; 												//取得Client ID位址
	len=strlen((char*)ptr);											//取得Client ID長度
	*ptrpay++=0; *ptrpay++=len;										//設置長度資訊
	paylen=len+2;													//累計Payload總長度(含2-Byte長度資訊)
	while(*ptr!=NULL) *ptrpay++=*ptr++;								//附加資料
	ptr=(u8*)mqttUser;  											//取得MQTT Username位址
	len=strlen((char*)ptr);											//取得MQTT Username長度
	*ptrpay++=0; *ptrpay++=len;										//設置長度資訊
	paylen+=len+2;													//累計Payload總長度(含2-Byte長度資訊)
	while(*ptr!=NULL) *ptrpay++=*ptr++;								//附加資料
	ptr=(u8*)mqttPswd; 												//取得MQTT Password位址
	len=strlen((char*)ptr);											//取得Password長度
	*ptrpay++=0; *ptrpay++=len;										//設置長度資訊
	paylen+=len+2;													//累計Payload總長度(含2-Byte長度資訊)
	while(*ptr!=NULL) *ptrpay++=*ptr++;								//附加資料			
	return mqtt_send(CONNECT,(u8*)ConVarHeader,10,(u8*)payload,paylen);			
}

u8 mqttSubscribe(u8* ptrSubscribe)
{	DEFINE_SFR(u8, payload[128], 0x1080);							//Bank 16:80h~FFh
	u8 varHeader[2], paylen; u8 *ptrdst=(u8*)payload;
	if(++lbPID==0)													//設置packetID(packetID不得為0)
	{	if(++hbPID==0) lbPID++;
	} 
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	paylen=strlen((char*)ptrSubscribe);								//取得Subscribe Topic長度
	*ptrdst++=0; *ptrdst++=paylen;									//設置長度資訊
	while(*ptrSubscribe!=NULL) *ptrdst++=*ptrSubscribe++;			//附加Topic Filter名稱
	*ptrdst=QoS;													//附加Request QoS
	paylen+=3;														//長度資訊(含2-Byte長度資訊及Request QoS)		
	return mqtt_send(SUBSCRIBE,(u8*)varHeader,2,(u8*)payload,paylen);
}
u8 mqttUnSubscribe(u8* ptrSubscribe)
{	DEFINE_SFR(u8, payload[128], 0x1080);							//Bank 16:80h~FFh
	u8 varHeader[2],paylen;	u8 *ptrdst=(u8*)payload;					
	if(++lbPID==0)													//設置packetID(packetID不得為0)
	{	if(++hbPID==0) lbPID++;
	} 
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	paylen=strlen((char*)ptrSubscribe);								//取得Subscribe Topic長度
	*ptrdst++=0; *ptrdst++=paylen;									//設置長度資訊(Length MSB,LSB))
	while(*ptrSubscribe!=NULL) *ptrdst++=*ptrSubscribe++;			//附加Topic Filter名稱
	paylen+=2;														//長度資訊(含2-Byte長度資訊)
	return mqtt_send(UNSUBSCRIBE,(u8*)varHeader,2,(u8*)payload,paylen);
}
u8 mqttPingReq(void)
{	return mqtt_send(PINGREQ,NULL,0,NULL,0);
}
u8 mqttDisconnect(void)
{	return mqtt_send(DISCONNECT,NULL,0,NULL,0);
}
u8 mqttPublishAck(void)
{	u8 varHeader[2];							
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	return mqtt_send(PUBACK,(u8*)varHeader,2,NULL,0);
}
u8 mqttPublishRec(void)
{	u8 varHeader[2];							
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	return mqtt_send(PUBREC,(u8*)varHeader,2,NULL,0);
}
u8 mqttPublishComp(void)
{	u8 varHeader[2];							
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	return mqtt_send(PUBCOMP,(u8*)varHeader,2,NULL,0);
}
u8 mqttPublishRel(void)
{	u8 varHeader[2];							
	varHeader[0]=hbPID; varHeader[1]=lbPID;							//設置packetID
	return mqtt_send(PUBREL,(u8*)varHeader,2,NULL,0);
}

u8 mqtt_send(u8 command,u8* ptrvarheader,u8 varlen, u8* ptrpayload,u8 paylen) //2024.03.23(提升速度TB1C預除值可降低) 
{	u8 fixHeader[5],i,len=1,error=0; 
	u16	remLen; u8 *ptr=NULL;
	if(command==PUBLISH)
	{	fixHeader[0]=command|(DUP<<3)|(QoS<<1)|RETAIN;	
#if QoS!=0															//需再Topic後加上加上PacketID
		if(++lbPID==0)												//設置packetID(packetID不得為0)
		{	if(++hbPID==0) lbPID++;
		} 
		ptrvarheader[varlen]=hbPID;									//PID MSByte
		ptrvarheader[varlen+1]=lbPID;								//PID LSByte
		varlen+=2;													//加上PacketID 2-Byte長度
#endif	
	}	
	else fixHeader[0]=command;										//裝載命令
	remLen=varlen+paylen;											//計算總長度
	do
	{	fixHeader[len]=remLen&0x7F;									//remLen MOD 128
		remLen>>=7;													//remLen=remLen/128
		if(remLen>0) fixHeader[len]|=(1<<7);						//Set MSB=1
		len++;
	} while(remLen>0);
	if(CIPSendLen(SINGLE,NULL,len+varlen+paylen))					//AT+CIPSEND command
	{	for(i=0;i<len;i++)											//Fixed Header
		{	_txr_rxr1=fixHeader[i];									//送出資料至TXR
			while(!_txif1);											//等待資料送至TSR
		}
		for(i=0;i<varlen;i++)										//Variable Header
		{	_txr_rxr1=ptrvarheader[i];								//送出資料至TXR
			while(!_txif1);											//等待資料送至TSR
		}
		for(i=0;i<paylen;i++)										//Payload
		{	_txr_rxr1=ptrpayload[i];								//送出資料至TXR
			while(!_txif1);											// 
		}		
		CmdLen=11;													//Recv xxx Bytes....SEND OK... +IPD,5:....	
		ptrBuf=RxBuf0; *ptrBuf=NULL; RxCount=0; 					
		_rxen1=1; 
		Wait=0; _tb1on=1;											//啟動UART接收

		ptr=NULL;
		while(Wait<(u16)62500)										//若未超時(unit:185us,TB1)
		{	switch(command)
			{	case DISCONNECT:									//Broker不會回應DISCONNECT
				case PUBACK:										//Broker不會回應PUBACK
				case PUBCOMP:										//Broker不會回應PUBCOMP
#if QoS==0
				case PUBLISH: 										//QoS=0,Broker不會回應PUBLISH
#endif
					if(strstr((char*)RxBuf0,"OK"))
					{	error=1;
						_tb1on=0;_rxen1=0; 							//關閉超時計數器與UART接收
						return error;
					}
				default:			
					ptr=(u8*)strstr((char*)RxBuf0,(char*)":");		//ptr指向: (+IPD,xxx:...)
			}
			if(Wait>3 && ptr!=NULL) break; 							//若已有收到資料,但超過時間未再有任何訊息接收(注意SERVER反應時間)
//			if(Wait!=0 && ptr!=NULL) break; 						//若已有收到資料,但超過時間未再有任何訊息接收(注意SERVER反應時間)
		}
		_tb1on=0; 													//關閉超時計數器
		_rxen1=0;													//關閉UART接收	
		if(RxCount!=0) 												//若有收到訊息,尋找是否有指定之回應字串
		{	ptr=(u8*)strstr((char*)RxBuf0,(char*)":");				//ptr指向: (+IPD,xxx:...)
			switch(command)
			{	case SUBSCRIBE: 
						if(ptr[1]==SUBACK) error=1;					//SUBACK					
						if(ptr[2]!=3) error=0;						//remLen
						if(ptr[3]!=hbPID || ptr[4]!=lbPID) error=0;
						if(ptr[5]>2) error=0;						//SUBACK Return Code(QoS:0~2)
						break;
				case UNSUBSCRIBE: 
						if(ptr[1]==UNSUBACK) error=1;				//UNSUBACK
						if(ptr[2]!=2) error=0;						//remLen
						if(ptr[3]!=hbPID || ptr[4]!=lbPID) error=0;
						break;
				case PINGREQ: 
						if(ptr[1]==PINGRESP) error=1;				//PINGRESP
						if(ptr[2]!=0) error=0;						//remLen
						break;								
				case CONNECT: 
						if(ptr[1]==CONNACK) error=1;				//CONNACK
						if(ptr[2]!=2) error=0;						//remLen
						if(ptr[4]!=0) error=0;						//Return Code Response
						break;
				case PUBLISH: 
#if QoS==1		
						if(ptr[1]==PUBACK) error=1;					//PUBACK(QoS=1)
#else			
						if(ptr[1]==PUBREC) error=1;					//PUBREC(QoS=2)
#endif		
						if(ptr[2]!=2) error=0;						//remLen
						if(ptr[3]!=hbPID || ptr[4]!=lbPID) error=0;
						break;						
#if QoS==2
				case PUBREC:
						if(ptr[1]==PUBREL) error=1;					//PUBREL(QoS=2),REC下達後,PUBREL命令超快到達～
						if(ptr[2]!=2) error=0;						//remLen
						if(ptr[3]!=hbPID || ptr[4]!=lbPID) error=0;
						break;						
				case PUBREL: 
						if(ptr[1]==PUBCOMP) error=1;				//PUBCOMP(QoS=2)
						if(ptr[2]!=2) error=0;						//remLen
						if(ptr[3]!=hbPID || ptr[4]!=lbPID) error=0;
						break;						
#endif				
			}
		}
	}		
	return error;
}
u8 mqtt_Receive(u8* ptrlen)											//2024.301可行新版
{	u8 command=0,*ptr;
	u16	multiplier=1;
	CmdLen=0;
	ptrBuf=RxBuf0; *ptrBuf=NULL; RxCount=0; 						//記錄CIPSEND回應">"後的接收字元
	_rxen1=1; Wait=0; _tb1on=1;										//啟動UART接收
	while(aliveCnt<=Alive-10)										//若未超時,繼續等待
	{	if(Wait>3 && RxCount>5) break;								//已有資料接收,但已一段時間未再有資料接收
	}	
	_tb1on=0; 														//關閉超時計數器
	_rxen1=0;														//關閉UART接收		
	if(RxCount!=0)													//若有收到資料
	{	ptr=(u8*)strstr((char*)RxBuf0,(char*)":");					//+IPD,Length:...
		if(ptr!=NULL) 												//若有收到":"
		{	ptr++;
			command=*ptr;											//取得Command	
			*ptrlen=0;
			do														//解碼Remain Length
			{	ptr++;												//指向Remain Length First Byte
				*ptrlen+=((*ptr)&0x7F)*multiplier;	
				multiplier<<=7;										//multiplier*=128
			} while (*ptr&(1<<7));									//若MSB=1,解碼下一個Byte
			if(*ptrlen>110) command=0;								//remlen長度限制!!!!!!
		}
	}
	return command;
}
u8 mqttPublishIotMqtt(u8* ptrTopic, u8* ptrraw)						//for IoT MQTT APP
{	DEFINE_SFR(u8, varHeader[128], 0x1180);							//Bank 16:80h~FFh
	u8 varlen,paylen,len;							
	u8 *ptrdst;
	ptrdst=(u8*)varHeader;											//指向varHeader[]起始位址
	len=strlen((char*)ptrTopic);									//取得TOPIC長度
	*ptrdst++=0; *ptrdst++=len;										//設置TOPIC長度資訊
	varlen=len+2;													//長度資訊(含2-Byte TOPIC長度資訊)
	while(*ptrTopic!=NULL) *ptrdst++=*ptrTopic++;					//附加TOPIC名稱(於mqtt_send()中決定是否添加Packet ID)
	paylen=strlen((char*)ptrraw);
	return mqtt_send(PUBLISH,(u8*)varHeader,varlen,(u8*)ptrraw,paylen);
}