#include "ControlMechanism.h"

uint8_t classifiedSignal = 0;

void ControlOpposed(void)
{
	classifiedSignal = SignalDetection();
	PrintSignal(classifiedSignal);
	
	switch(classifiedSignal)
	{
		case Short_Short:
			if(lastgrip == REST_OPP)
				PowerGrip();
				ProportionalControl(POWER);
			break;
	
		case Short_Long:
			if(lastgrip == REST_OPP)
				TripodGrip();
			break;

		case Long_Short:
			if(lastgrip == REST_OPP)
				PrecisionOpenGrip();
			break;
			
		case Short_Short_Short:
			if(lastgrip == REST_OPP)
				ActiveIndexGrip();
			break;			
	}
}

void ControlNonOpposed(void)
{
	classifiedSignal = SignalDetection();
	PrintSignal(classifiedSignal);
	
	switch(classifiedSignal)
	{
		case Short_Short:
			if(lastgrip == REST_NOPP)
				HookGrip();
			break;
	
		case Short_Long:
			if(lastgrip == REST_NOPP)
				KeyGrip();
			break;

		case Long_Short:
			if(lastgrip == REST_NOPP)
				FingerPointGrip();
			break;
			
		case Short_Short_Short:
			if(lastgrip == REST_NOPP)
				MouseGrip();
			break;			
	}
}

