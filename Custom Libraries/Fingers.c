#include "Fingers.h"

uint32_t CurrFingerPulse[5];

void read_Enc_Fingers()
{
	for(int i = 0; i < 5;	i++)
	{
		 CurrFingerPulse[i] = FingerPulses(i);
	}
}

bool check_CurrSense(int fingernumber)
{
	if(ReadADC((Channel)(fingernumber+2)) < 200)
		return true;
	else
		return false;		
}

void control_Finger(int fingernumber, bool fingerDirection, uint16_t fingerSpeed)
{
		motorDirection((Phase)fingernumber, fingerDirection);
		motorPWM((Enable)fingernumber, fingerSpeed);
}

void control_Finger_Time(int fingernumber, bool fingerDirection,uint16_t fingerSpeed, int duration)
{
	uint32_t t1,t2,t21;
	t1 = t2 = t21 = 0;
	
	t1 = millis();
	t2 = millis();
	while(t2>=t1 && t21 <= duration)
	{
		control_Finger(fingernumber, fingerDirection, fingerSpeed);
		t2 = millis();
		t21 = t2 - t1;
	}
	control_Finger(fingernumber, fingerDirection, 0);
}

void control_Finger_withEncoder(int fingernumber, bool fingerDirection,	uint16_t fingerSpeed, uint32_t Encodervalue)
{
	uint32_t StartPulse = FingerPulses(fingernumber);
	uint32_t CurrPulse = 0;
	
	while(1)
	{
		CurrPulse = FingerPulses(fingernumber);
		
		if(fingerDirection == CURL_OUT && CurrPulse >= (StartPulse - Encodervalue))
		{
			control_Finger(fingernumber, fingerDirection, fingerSpeed);
		}
		else if(fingerDirection == CURL_IN && CurrPulse <= (StartPulse + Encodervalue))
		{
			control_Finger(fingernumber, fingerDirection, fingerSpeed);
		}
		else
		{
			control_Finger(fingernumber, fingerDirection, 0);
			break;
		}
	}
}

void control_Finger_CurrandEncoder(int fingernumber, bool fingerDirection, uint16_t fingerSpeed, uint32_t Encodervalue)
{
	uint32_t StartPulse = FingerPulses(fingernumber);
	uint32_t CurrPulse = 0;
	
	while(1)
	{
		CurrPulse = FingerPulses(fingernumber);
		
		if(fingerDirection == CURL_OUT && CurrPulse <= (StartPulse + Encodervalue) && check_CurrSense(fingernumber))
		{
			control_Finger(fingernumber, fingerDirection, fingerSpeed);
		}
		else if(fingerDirection == CURL_IN && CurrPulse >= (StartPulse - Encodervalue) && check_CurrSense(fingernumber))
		{
			control_Finger(fingernumber, fingerDirection, fingerSpeed);
		}
		else
		{
			control_Finger(fingernumber, fingerDirection, 0);
			break;
		}
	}
}

int control_Finger_Encoder(int fingernumber, struct gripName gripval)
{
	uint32_t val[5];
	val[0] = gripval.ThumbEncVal;
	val[1] = gripval.IndexEncVal;
	val[2] = gripval.MiddleEncVal;
	val[3] = gripval.RingEncVal;
	val[4] = gripval.PinkyEncVal;
	
	if(FingerPulses(fingernumber) <= ((encodeRef + val[fingernumber]) - 10))
	{
		control_Finger(fingernumber, CURL_IN, SPEED_MAX);
		return 2;
	}
	else if(FingerPulses(fingernumber) >= ((encodeRef + val[fingernumber]) + 10))
	{
		control_Finger(fingernumber, CURL_OUT, SPEED_MAX);
		return 3;
	}
	else
	{
		control_Finger(fingernumber, CURL_OUT, SPEED_MIN);
		return 0;
	}
//	return 1;
}
