#ifndef _AnalogSensor_
#define _AnalogSensor_

#include "Header.h"

#define Curr1Threshold 200
#define Curr2Threshold 200
#define Curr3Threshold 200
#define Curr4Threshold 200
#define Curr5Threshold 200

typedef enum
{
	FSR1,	FSR2,	Curr1,	Curr2,	Curr3,	Curr4,	Curr5 	
}Channel;

void initADC(void);
uint16_t ReadADC(Channel Ch);
uint16_t ReadADCChannel(Channel Ch);

#endif
