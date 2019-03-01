#include "ControlMechanism.h"

uint8_t classifiedSignal = 0;

void ControlOpposed(void)
{
	classifiedSignal = SignalDetection();
	PrintSignal(classifiedSignal);
	
	switch(classifiedSignal)
	{
		case Short_Short:
			UARTprintf("\n Short-short detected");
			if(lastgrip == REST_OPP)
			{
				PowerGrip();
				ProportionalControl(POWER);
				RestOppGrip();
			}
			break;
	
		case Short_Long:
			if(lastgrip == REST_OPP)
			{
				TripodGrip();
				ProportionalControl(TRIPOD);
				RestOppGrip();
			}
			break;

		case Long_Short:
			if(lastgrip == REST_OPP)
			{
				PrecisionOpenGrip();
				ProportionalControl(PRECISION_OPEN);
				RestOppGrip();
			}
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
			if(lastgrip == REST_OPP)
			{
				HookGrip();
				ProportionalControl(HOOK);
				RestOppGrip();
			}
			break;
	
		case Short_Long:
			if(lastgrip == REST_OPP)
			{
				KeyGrip();
				ProportionalControl(KEY);
				RestOppGrip();
			}
			break;

		case Long_Short:
			if(lastgrip == REST_OPP)
			{
				FingerPointGrip();
				ProportionalControl(FINGER_POINT);
				initGrip();
				RestOppGrip();
			}
			break;
			
		case Short_Short_Short:
			if(lastgrip == REST_NOPP)
				MouseGrip();
			break;			
	}
}

