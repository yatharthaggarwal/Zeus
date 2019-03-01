#include "Header.h"

void setup(void);
uint8_t classifiedSignal1 = 0;

float roll;
float pitch;

int main()
{
	setup();
	serialBegin(9600);
	
//	control_Finger_Time(THUMB, 	CURL_IN, 900, 1000);
//	control_Finger_Time(INDEX, 	CURL_IN, 900, 1000);
//	control_Finger_Time(MIDDLE, CURL_IN, 900, 1000);
//	control_Finger_Time(PINKY, 	CURL_IN, 900, 1000);
//	delay(1000);
		initGrip();
		RestOppGrip();
	
	//PowerGrip();
	while(1)
	{
		if(GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2))
		{
//			UARTprintf("\n Opposed Mode ");
			ControlOpposed();
		}
		else
		{
//			UARTprintf("\n Non-Opposed Mode ");
			ControlNonOpposed();
		}
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
//		UARTprintf("\n%d", ReadADC(FSR1));
//		UARTprintf("\t%d", ReadADC(FSR2));

//		PrintSignal(SignalDetection());
	
		//ControlNonOpposed();
	//ProportionalControl(POWER);
	//RestOppGrip();
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
	
	GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2); 
	GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
}
