#include "FSRsignal.h"

uint32_t time1 = 0, time2 = 0, time21 = 0;

uint32_t Ptime1 = 0, Ptime2 = 0, Ptime21 = 0;

uint8_t SignalClassify(void)
{
	time1 = millis();
	while(ReadADC(FSR1) >= Threshold1) 
	{
	}
	time2 = millis();

	if(time2 >= time1)
		time21 = time2 - time1;
	
	if(time21 > Short_durMin && time21 < Short_durMax)
	{
		return SHORT;
	}
	else if (time21 > Long_durMin && time21 < Long_durMax)
	{
		return LONG;
	}
	else
	{	
		return ERROR;
	}
}

uint8_t SignalDetection(void)
{
	uint8_t Signal1 = 0, Signal2 = 0, Signal3 = 0;
	volatile uint8_t FinalSignal = 0;
	uint32_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	
	Signal1 = SignalClassify();										// First High
	if(Signal1)
	{
		t1 = millis();							
		while(ReadADC(FSR1) < Threshold1)				 		// Check for Low
		{
			t2 = millis();
			if((t2 > t1) && (t2-t1) > Signal_DurOverflow)
			{
				FinalSignal = Signal1;
				return FinalSignal;
			}
		}
		
		if((t2 > t1) && (t2-t1) < Signal_DurOverflow)
		{
				Signal2 = SignalClassify();								// Second High
				FinalSignal = Signal1*10 + Signal2;
				if(FinalSignal!=11)
					return FinalSignal;				
		}
	}
	
	if(FinalSignal ==  11)													// Checking for Short-Short-Short
	{
		t3 = millis();
		while(ReadADC(FSR1) < Threshold1)							// Check for Low
		{
			t4 = millis();
			if((t4 > t3) && (t4-t3) > Signal_DurOverflow)
			{
				return FinalSignal;
			}
		}

			if((t4 > t3) && (t4-t3) < Signal_DurOverflow)
			{
				Signal3 = SignalClassify();								// Third High
				FinalSignal = FinalSignal*10 + Signal3;
				return FinalSignal;				
			}
		}		
	return ERROR;
}

void PrintSignal(int8_t signalValue)
{
	if(signalValue != ERROR)	
	switch(signalValue)
	{
		case 1:
			UARTprintf("\n Short");
			break;
		
		case 2:
			UARTprintf("\n Long");
			break;
			
		case 11:
			UARTprintf("\n Short - Short");
			break;
		
		case 12:
			UARTprintf("\n Short - Long");
			break;
		
		case 21:
			UARTprintf("\n Long - Short");
			break;
		
		case 22:
			UARTprintf("\n Long - Long");
			break;
		
		case 111:
			UARTprintf("\n Short - Short - Short");
			break;
	}
}
	
uint8_t ProportionalControl(int8_t makeGrip)
{
	uint16_t nowADC, lastADC;
	nowADC = lastADC = 0;
	bool transition = false;
	bool curl = CURL_IN;

		while(1)
		{
			nowADC = ReadADC(FSR1);
			
			//nowADC > Threshold1 ? GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,GPIO_PIN_2) : GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x00);
			
			if(nowADC > lastADC && nowADC > Threshold1 && lastADC < Threshold1 && transition == false) // start timer for signal rise
			{
				Ptime1 = millis();
				transition = true;
			}
			
			if(nowADC > Threshold1 && transition == true)	// update rise duration of signal
			{
				Ptime2 = millis();
				Ptime21 = Ptime2 - Ptime1;
			}
			
			if(nowADC < Threshold1 && Ptime2 > Ptime1 && Ptime21 < Proportion_durBegin && transition == true) // SHORT detection
			{
				StopAllFinger();
				UARTprintf("\n SHORT detected");
				return SHORT;
			}
			
			if(nowADC > Threshold1 && Ptime2 > Ptime1 && Ptime21 > Proportion_durBegin && transition == true)	// Proportional detection
			{
				UARTprintf("\n Proportional detected");
				ProportionalGrip(makeGrip, curl, nowADC);
			}
			
			if(nowADC < lastADC && nowADC < Threshold1 && lastADC > Threshold1 && Ptime21 > Proportion_durBegin && transition == true) // check fall of signal
			{
				StopAllFinger();
				transition = false;
				curl = !curl; // change direction
			}
			
			lastADC = nowADC;
		}
}

