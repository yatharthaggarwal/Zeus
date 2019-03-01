#include "Grips.h"

struct gripName grips[10] = {//Gripname							Thumb		Index		Middle		Ring		Pinky			ThumbS`		IndexS	 MiddleS		 RingS		PinkyS
														{"Rest Opposed Grip", 		100,		100,		100,		100,			100,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE},
														{"Power Grip", 						900,		900,		900,		900,			900,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE},
														{"Tripod Grip", 				 1000,		100,		100,		100,			100,		ACTIVE,		ACTIVE,		ACTIVE,	INACTIVE,	INACTIVE},
														{"Active Index Grip", 		100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Precision Open Grip",   100,		100,		100,		100,			100,		ACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Rest Non-Opposed Grip", 100,		100,		100,		100,			100,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Hook Grip", 						100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,		ACTIVE,		ACTIVE,		ACTIVE},
														{"Key Grip", 							100,		1000,		1000,		1000,			1000,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Mouse Grip", 						100,		100,		100,		100,			100,	INACTIVE,		ACTIVE,	INACTIVE,	INACTIVE,	INACTIVE},
														{"Finger Point Grip", 		100,		100,		100,		100,			100,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE,	INACTIVE}
														};	
//
														
int lastgrip = -1;
float FSRmax = 4000.0;

void initGrip(void)
{
//	int flag1, flag2, flag3, flag4, flag5;
//	flag1 = flag2 = flag3 = flag4 = flag5 = 1;
	uint32_t t1,t2,t21;
	t1=t2=t21=0;
	
	t1=millis();
	while(1)
	{
		t2= millis();
		t21 = t2-t1;
//		UARTprintf("\t\n%d",t21);
		
		if(t21 <= TimeThreshold)
		{
			control_Finger(THUMB, CURL_OUT, 900);
			control_Finger(INDEX, CURL_OUT, 900);
			control_Finger(MIDDLE, CURL_OUT, 900);
			control_Finger(RING, CURL_OUT, 900);
			control_Finger(PINKY, CURL_OUT, 900);
		}
		else
		{
			control_Finger(THUMB, CURL_OUT, 0);
			control_Finger(INDEX, CURL_OUT, 0);		
			control_Finger(MIDDLE, CURL_OUT, 0);		
			control_Finger(RING, CURL_OUT, 0);
			control_Finger(PINKY, CURL_OUT, 0);
			UARTprintf("\n Grip Initialized");
			StopAllFinger();
			break;
		}			
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
	uint32_t t1, t2, t21;
	t1 = t2 = t21 = 0;
	
	UARTprintf("\n%s",gripVal.GripName);
	
	t1 = millis();
	while(1)
	{
		t2 = millis();
		t21 = t2 - t1;
		flag1 = control_Finger_Encoder(THUMB, gripVal);
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
		
		if(flag1 + flag2 == 0 || (t2 > t1 && t21 > 2000))
		{
			StopAllFinger();
			break;
		}
	}
	UARTprintf(" Completed");
}

int RestOppGrip(void)
{
	UARTprintf("\n Rest Opp Grip Begins");
	makeGripException(grips[REST_OPP]);
	lastgrip = REST_OPP;
	return REST_OPP;
}
int PowerGrip(void)
{
	UARTprintf("\n Power Grip Begins");
	makeGripException(grips[POWER]);
	lastgrip = POWER;
	return POWER;
}

int TripodGrip(void)
{
	UARTprintf("\n Tripod Grip Begins");
	makeGripException(grips[TRIPOD]);
	lastgrip = TRIPOD;
	return TRIPOD;
}

int ActiveIndexGrip(void)
{
	UARTprintf("\n Active Index Grip Begins");
	lastgrip = ACTIVE_INDEX;
	return ACTIVE_INDEX;
}

int PrecisionOpenGrip(void)
{
	UARTprintf("\n Precision Open Begins");
	makeGripException(grips[PRECISION_OPEN]);
	lastgrip = PRECISION_OPEN;
	return PRECISION_OPEN;
}


int RestNoppGrip(void)
{
	lastgrip = REST_NOPP;
	return REST_NOPP;
}
int HookGrip(void)
{
	UARTprintf("\n Hook Grip Begins");
	makeGripException(grips[HOOK]);
	lastgrip = HOOK;
	return HOOK;
}
int KeyGrip(void)
{
		uint32_t t1, t2, t21;
	t1 = t2 = t21 = 0;
	UARTprintf("\n Key Grip Begins");
		
	t1 = t2 = millis();
	while(t21 < 1500 && t2>= t1)
	{
		t2 = millis();
		t21 = t2 - t1;
		control_Finger(INDEX, 	CURL_IN, 900);
		control_Finger(MIDDLE, 	CURL_IN, 900);
		control_Finger(RING, 		CURL_IN, 900);
		control_Finger(PINKY, 	CURL_IN, 900);
	}
	StopAllFinger();
	lastgrip = KEY;
	return KEY;
}
int MouseGrip(void)
{
	UARTprintf("\n Mouse Grip Begins");
	makeGripException(grips[MOUSE]);
	lastgrip = MOUSE;
	return MOUSE;
}
int FingerPointGrip(void)
{
	uint32_t t1, t2, t21;
	t1 = t2 = t21 = 0;
	UARTprintf("\n Finger Point Grip Begins");
		
	t1 = t2 = millis();
	while(t21 < 1500 && t2>= t1)
	{
		t2 = millis();
		t21 = t2 - t1;
		control_Finger(MIDDLE, 	CURL_IN, 900);
		control_Finger(RING, 		CURL_IN, 900);
		control_Finger(PINKY, 	CURL_IN, 900);
	}
	StopAllFinger();
	lastgrip = FINGER_POINT;
	return FINGER_POINT;
}

void ProportionalGrip(int8_t GripVal, bool dir, uint16_t FSRadc)
{
	struct gripName Currgrip = grips[GripVal];
	int setPWM;
	
	if(FSRadc <= 500)
		setPWM = 0;
	else if(FSRadc > 500 && FSRadc <= 2000)
		setPWM = 850;
	else if (FSRadc > 2000)
		setPWM = 999;
		
	if(Currgrip.ThumbStatus == ACTIVE)
	{
		if(GripVal == POWER && dir == CURL_IN)
			control_Finger(THUMB, dir, 750);
		else
			control_Finger(THUMB, dir, setPWM);
	}
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
	UARTprintf("\n Fingers Stoppped");
}
