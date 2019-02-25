#ifndef _InterruptHandlers_
#define _InterruptHandlers_

#include "Header.h"

#define encodeRef 10000

typedef enum
{
	EncA1, EncA2, EncA3, EncA4, EncA5, 
	EncB1, EncB2, EncB3, EncB4, EncB5
}Encoder;

void InitEnoderVal(void);

//void PortBIntHandler(void);
void PortCIntHandler(void);
void PortDIntHandler(void);
//void PortFIntHandler(void);

void SysTickIntHandler(void);

uint32_t encodervalue(Encoder channel); 
uint32_t FingerPulses(int fingernumber);

#endif
