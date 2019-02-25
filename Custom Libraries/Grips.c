#include "Grips.h"

struct gripName grips[10] = {//Gripname							Thumb		Index		Middle		Ring		Pinky			ThumbS`		IndexS	 MiddleS		 RingS		PinkyS
														{"Rest Opposed Grip", 		100,		100,		100,		100,			100,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Power Grip", 						900,		900,		900,		900,			900,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE},
														{"Tripod Grip", 					100,		100,		100,		100,			100,		ACTIVE,		ACTIVE,		ACTIVE,	INACTIVE,	INACTIVE},
														{"Active Index Grip", 		100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Precision Open Grip", 	100,		100,		100,		100,			100,		ACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Rest Non-Opposed Grip", 100,		100,		100,		100,			100,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Hook Grip", 						100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE},
														{"Key Grip", 							100,		600,		600,		600,			600,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Mouse Grip", 						100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Finger Point Grip", 		100,		100,		100,		100,			100,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE}
														};	
//
														
int lastgrip = -1;
float FSRmax = 3800.0;

void initGrip(void)
{
	int flag1, flag2, flag3, flag4, flag5;
	flag1 = flag2 = flag3 = flag4 = flag5 = 1;
	
	while(1)
	{
		if(ReadADC(Curr1) <= Curr1Threshold)
			control_Finger(THUMB, CURL_OUT, 400);
		else
		{
			control_Finger(THUMB, CURL_OUT, 0);
			flag1 = 0;
		}
		
		if(ReadADC(Curr2) <= Curr2Threshold)
			control_Finger(INDEX, CURL_OUT, 400);
		else
		{
			control_Finger(INDEX, CURL_OUT, 0);
			flag2 = 0;
		}
		
		if(ReadADC(Curr3) <= Curr3Threshold)
			control_Finger(MIDDLE, CURL_OUT, 400);
		else
		{
			control_Finger(MIDDLE, CURL_OUT, 0);
			flag3 = 0;
		}
		
		if(ReadADC(Curr4) <= Curr4Threshold)
			control_Finger(RING, CURL_OUT, 400);
		else
		{
			control_Finger(RING, CURL_OUT, 0);
			flag4 = 0;
		}
		
		if(ReadADC(Curr5) <= Curr5Threshold)
			control_Finger(PINKY, CURL_OUT, 400);
		else
		{
			control_Finger(PINKY, CURL_OUT, 0);
			flag5 = 0;
		}
		
		if((flag1 + flag2 + flag3 + flag4 + flag5) == 0)
			break;
	}
	InitEnoderVal();
}

void makeGrip(struct gripName gripVal)
{
	bool flag1, flag2, flag3, flag4, flag5;
	flag1 = flag2 = flag3 = flag4 = flag5 = 1;
	
	UARTprintf("\n%s",gripVal.GripName);
	
	while(1)
	{
		flag1 = control_Finger_Encoder(THUMB, gripVal);
		flag2 = control_Finger_Encoder(INDEX, gripVal);
		flag3 = control_Finger_Encoder(MIDDLE,gripVal);
		flag4 = control_Finger_Encoder(RING,	gripVal);
		flag5 = control_Finger_Encoder(PINKY, gripVal);
		
		if(flag1 + flag2 + flag3 + flag4 + flag5 == 0)
			break;
	}
}

void makeGripException(struct gripName gripVal)
{
	int flag1, flag2;
	flag1 = flag2 = 1;
	
	UARTprintf("\n%s",gripVal.GripName);
	
	while(1)
	{
//		flag1 = control_Finger_Encoder(THUMB, gripVal);
		flag1 = 0;
		flag2 = control_Finger_Encoder(INDEX, gripVal);
		if(flag2 == 2)
		{
			control_Finger(MIDDLE,CURL_IN,	SPEED_MAX * gripVal.MiddleStatus);
			control_Finger(RING,	CURL_IN,	SPEED_MAX * gripVal.RingStatus);
			control_Finger(PINKY,	CURL_IN,	SPEED_MAX * gripVal.PinkyStatus);
		}
		else if(flag2 == 3)
		{
			control_Finger(MIDDLE,CURL_OUT,	SPEED_MAX * gripVal.MiddleStatus);
			control_Finger(RING,	CURL_OUT,	SPEED_MAX * gripVal.RingStatus);
			control_Finger(PINKY,	CURL_OUT,	SPEED_MAX * gripVal.PinkyStatus);			
		}
		
		if(flag1 + flag2 == 0)
		{
			StopAllFinger();
			break;
		}
	}
}

int RestOppGrip(void)
{
	makeGrip(grips[0]);
	return REST_OPP;
}
int PowerGrip(void)
{
	read_Enc_Fingers();
	// make all fingers reach the reqd position
	// 
	UARTprintf("\n Power Grip Begins");
	return POWER;
}

int TripodGrip(void)
{
	UARTprintf("\n Tripod Grip Begins");
	return TRIPOD;
}

int ActiveIndexGrip(void)
{
	UARTprintf("\n Active Index Grip Begins");
	return ACTIVE_INDEX;
}

int PrecisionOpenGrip(void)
{
	UARTprintf("\n Precision Open Begins");
	return PRECISION_OPEN;
}


int RestNoppGrip(void)
{
	return REST_NOPP;
}
int HookGrip(void)
{
	UARTprintf("\n Hook Grip Begins");
	//1. make fingers reach to a certain position
	//2. Check for next signal
	//3. Behave 
	//4. Again step 2
	return HOOK;
}
int KeyGrip(void)
{
	UARTprintf("\n Key Grip Begins");
	return KEY;
}
int MouseGrip(void)
{
	UARTprintf("\n Mouse Grip Begins");
	return MOUSE;
}
int FingerPointGrip(void)
{
	UARTprintf("\n Finger Point Grip Begins");
	return FINGER_POINT;
}

void ProportionalGrip(int8_t GripVal, bool dir, uint16_t FSRadc)
{
	struct gripName Currgrip = grips[GripVal];
	int setPWM;
	
	setPWM = FSRadc/FSRmax * 500;
		if (setPWM < 1)
			setPWM = 1;
		
	if(Currgrip.ThumbStatus == ACTIVE)
		control_Finger(THUMB, dir, setPWM);
	else
		control_Finger(THUMB, dir, 0);
	
	if(Currgrip.IndexStatus == ACTIVE)
		control_Finger(INDEX, dir, setPWM);
	else
		control_Finger(INDEX, dir, 0);
	
	if(Currgrip.MiddleStatus == ACTIVE)
		control_Finger(MIDDLE, dir, setPWM);
	else
		control_Finger(MIDDLE, dir, 0);
	
	if(Currgrip.RingStatus == ACTIVE)
		control_Finger(RING, dir, setPWM);
	else
		control_Finger(RING, dir, 0);
	
	if(Currgrip.PinkyStatus == ACTIVE)
		control_Finger(PINKY, dir, setPWM);
	else
		control_Finger(PINKY, dir, 0);	
}

void StopAllFinger(void)
{
	for(int i = 0; i < 5;i++)
		control_Finger(i, CURL_IN, SPEED_MIN);
}
