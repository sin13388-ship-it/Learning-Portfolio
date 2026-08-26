#include <HT66F2390.h>										//2024.0421
#include "MyType.H"
#define BufLen		128										//Rx Buffer Length
//DEFINE_SFR(u8, RxBuf2[BufLen], 0x1A80);					//Bank B:80h~FFh
DEFINE_SFR(u8, RxBuf0[BufLen], 0x1B80);						//Bank B:80h~FFh

#define	fH			11059200								//MCU HXT Frequency
#define fSYS		11059200								//MCU System Frequency
#define BR			19200									//Baud Rate
//#define BRH			230400								//Baud Rate 2
#define BRH			115200									//Baud Rate 2

#define pRLED		_pc2									//2024.0421 ESK-310 RGB-R				
#define pRLEDC		_pcc2			
#define pGLED		_pc4									//2024.0421 ESK-310 RGB-G
#define pGLEDC		_pcc4			
#define pBLED		_pc6									//2024.0421 ESK-310 RGB-B
#define pBLEDC		_pcc6


#define pERLED		_pf2									//2024.0421 eDisplay LED1(Orange)
#define pERLEDC		_pfc2			
#define pEGLED		_pf1									//2024.0421 eDisplay LED2(Red)
#define pEGLEDC		_pfc1												
#define pEBLED		_pf0									//2024.0421 eDisplay LED3(Green)						
#define pEBLEDC		_pfc0									


#define pESPReset	_pd0									//8266 RST					
#define pESPResetc	_pdc0				

#define LEDOn		1										//LED亮燈準位設定
#define LEDOff		!LEDOn

#define	PI		3.14159
//AT ESP8266 Relative
enum {STA=1,AP,BOTH};
enum {SINGLE=0,MULTIPLE};
enum {HTTP=1,GET};

u8 ATE0(void);
u8 HardRESET8266(_Bool delay);
u8 SoftRESET8266(void);
u8 AutoConnection(u8 connect);
//u8 UART_CUR(void);
u8 UART_CUR(u32 baudRate);										//2024.0413
u8 SendCommand(u8* cmdptr,u8* echo);	
u8 SetWiFiMode(u8 mode);										//'1':STA, '2':AP, '3':Both(MUX=1)	
u8 SetConnectionMode(u8 mode);									//'0':Single, '1':Multiple
u8 CWJAP_(u8* ssid);
u8 QuitAP(void);
u8 JointAP(u8* ssid, u8* pswd);
u8 GetIP(void);
u8 SetUpConnection(u8 mode,u8 id,u8* type,u8* conip,u16 port);
u8 CIPSend(u8 mode,u8 id,u8* ptr);
u8 CIPSendLen(u8 mode,u8 id, u16 length);
u8 CloseConnection(u8 mode,u8 id);
u8 LEDControl(u8 error);
u8 SendCommand(u8* ptr,u8* echo);
u8 ConfigTcpServer(u8 mode,u16 port);
u8 NetRxData(u8 *ptr);
void baud2String(u32 bdr,u8 *ptr);								//轉換BRH為字串(115200/230400)
void Word2String(s16 data,u8 *ptr);	
void word2string(u8* ptrdst,s16 value,u8 dotpos);
u8* myFindStr(u8* ptrsrc, u8* ptrfind, u8 srclen);				//Find String in buffer which Null Character
u8 *FindString(u8* ptrsrc, u8* ptrfind, u8 srclen);
u8 *FindStringHMQ(u8* ptrsrc, u8* ptrfind, u8 srclen);			//Find String in buffer(Corss Section) which Null Character
void Delayms(u16 i);