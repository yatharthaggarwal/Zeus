#include "Header.h"

void setup(void);
uint8_t classifiedSignal1 = 0;

float roll;
float pitch;

int main()
{
	setup();
	serialBegin(9600);

	control_Finger(INDEX, CURL_OUT, 900);
	delay(100);
	control_Finger(INDEX, CURL_OUT, 0);
//	delay(2000);
	while(1)
	{
	// CURL_IN 		=> Closes Fingers
	// CURL_OUT 	=> Opens Fingers
	// SPEED_MAX	=> Motor's maximum speed
	// 500				=> Number of respective encoder's count to move
		
//	control_Finger_withEncoder(THUMB, 	CURL_IN, SPEED_MAX, 500);
//	control_Finger_withEncoder(INDEX, 	CURL_IN, SPEED_MAX, 500);
//	control_Finger_withEncoder(MIDDLE, 	CURL_IN, SPEED_MAX, 500);
//	control_Finger_withEncoder(RING, 		CURL_IN, SPEED_MAX, 500);
//	control_Finger_withEncoder(PINKY, 	CURL_IN, SPEED_MAX, 500);
//	delay(1000);
//		
//	control_Finger_withEncoder(THUMB, 	CURL_OUT, SPEED_MAX, 500);
//	control_Finger_withEncoder(INDEX, 	CURL_OUT, SPEED_MAX, 500);
//	control_Finger_withEncoder(MIDDLE, 	CURL_OUT, SPEED_MAX, 500);
//	control_Finger_withEncoder(RING, 		CURL_OUT, SPEED_MAX, 500);
//	control_Finger_withEncoder(PINKY, 	CURL_OUT, SPEED_MAX, 500);
//	delay(1000);
//	control_Finger(INDEX, CURL_IN, 500);
//	control_Finger(RING, CURL_IN, 500);
//	delay(2000);
//	control_Finger(INDEX, CURL_OUT, 500);
//	control_Finger(RING, CURL_OUT, 500);
//	delay(2000);
	}
}

void setup()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	
	initSysTick();
	initallPorts();
	init_motors();
	initADC();
	init_encoders();
	InitEnoderVal();
//	initI2C();
//	setupIMU();
}
