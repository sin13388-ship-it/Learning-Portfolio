#include <HT66F2390.h>
#include "MyType.h"
extern volatile u8  *ptrBuf;
extern volatile u16 CmdLen,Wait;
extern volatile u8 RxCount;

#define	SSID 		"thmrb311"				//SSID
#define	PSWD 		"thmrbthmrb"			//SSID Password


//#define mqttServer	"MQTTGO.io"			//小霸王Broker/Server  http://MQTTGO.io
#define mqttServer	"broker-cn.emqx.io"	

#define MaxPacketSize 	256
#define	DUP 0								//Bit[3]
#define	QoS 0	  							//Bit[2:1]
#define	RETAIN 0							//Bit[0]

#define ConFlag 0xC2						//Connect flag 
#define Alive 	(u8)40						//KeepAlive(Unit:sec)
//#define PLevel	3						//Prtoocol Level 3.0 for CHT IoT
#define PLevel	4							//Prtoocol Level 3.1 for ThingSpeak 
//MQTT Command
enum {CONNECT=0x10,PUBLISH=0x30,PUBREC=0x50,PUBREL= 0x62,SUBSCRIBE=0x82,UNSUBSCRIBE=0xA2,PINGREQ= 0xC0,
	  CONNACK=0x20,PUBACK= 0x40,			PUBCOMP=0x70,SUBACK=   0x90,UNSUBACK=   0xB0,PINGRESP=0xD0,DISCONNECT=0xE0};
u8 *FindString(u8* ptrsrc, u8* ptrfind, u8 srclen);
void word2string(u8* ptrdst,s16 value,u8 dotpos);
u8 mqttConnect(void);
u8 mqttPublish(u8* ptrTopic,u8 *ptrsensorID,u8 sensorCnt, u8* ptrraw);
u8 mqttPublishAck(void);
u8 mqttSubscribe(u8* ptrSubscribe);
u8 mqttUnSubscribe(u8* ptrSubscribe);
u8 mqttPublishRec(void);
u8 mqttPublishRel(void);
u8 mqttPublishComp(void);
u8 mqttPingReq(void);
u8 mqttDisconnect(void);
u8 mqtt_Receive(u8* ptrlen);
u8 mqtt_send(u8 command,u8* ptrvarheader,u8 varlen, u8* ptrpayload,u8 paylen);
u8 mqttPublishIotMqtt(u8* ptrTopic, u8* ptrraw);					//for IoT MQTT APP