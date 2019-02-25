#ifndef _Fingers_
#define _Fingers_

#include "Header.h"

#define THUMB			0
#define INDEX			1
#define MIDDLE		2
#define RING			3
#define PINKY			4

#define CURL_IN 	1
#define CURL_OUT	0

#define SPEED_MAX	999
#define SPEED_MIN	0

extern uint32_t CurrFingerPulse[5];
extern struct gripName gripval;
	
void read_Enc_Fingers(void);
bool check_CurrSense(int fingernumber);

void control_Finger(int fingernumber, bool fingerDirection, uint16_t fingerSpeed);

void control_Finger_Time(int fingernumber, bool fingerDirection, uint16_t fingerSpeed, int duration);
void control_Finger_withEncoder(int fingernumber, bool fingerDirection, uint16_t fingerSpeed, uint32_t Encodervalue);

void control_Finger_CurrandEncoder(int fingernumber, bool fingerDirection, uint16_t fingerSpeed, uint32_t Encodervalue);
int control_Finger_Encoder(int fingernumber, struct gripName gripval);

#endif

