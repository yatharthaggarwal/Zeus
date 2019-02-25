#ifndef _FSRsignal_
#define _FSRsignal_

#include "Header.h"

#define SHORT 1
#define LONG 	2
#define ERROR 0

#define Short 							1
#define Long  							2
#define Short_Short 				11
#define Short_Long  				12
#define Long_Short  				21
#define Long_Long   				22
#define Short_Short_Short 	111

#define Threshold1 					500

#define Short_durMin				100			//milliseconds
#define Short_durMax				1000		//milliseconds
#define Long_durMin					1000		//milliseconds
#define Long_durMax					2000		//milliseconds

#define Proportion_durBegin	1000		//milliseconds

#define Signal_DurOverflow 	500			//milliseconds

#define Active 							1	
#define Passive							2

uint8_t SignalClassify(void);
uint8_t SignalDetection(void);

uint8_t ProportionalControl(int8_t makeGrip);


void PrintSignal(int8_t signalValue);

#endif
