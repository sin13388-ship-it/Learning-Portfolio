#include <HT66F2390.h>
#define StartTC		(((u32)1*fSYS)/(4*1000))		//DHT22 Start Signal Time Constant :1ms
#define TresMax		((u32)220*fSYS/(4*1000000))		//220us(170+50)
#define TresMin		((u32)100*fSYS/(4*1000000))		//100us(150-50)
#define Tbit		((u32) 95*fSYS/(4*1000000))		//95us
//for v2
#define	pDHT		_pb3						//DHT信號輸出連接腳位
#define	pDHTC		_pbc3						//PB3 as PTP2I/PTP2
#define	pDHTPU		_pbpu3