#include "InterruptHandlers.h"

volatile uint32_t countA1;
volatile uint32_t countA2;
volatile uint32_t countA3;
volatile uint32_t countA4;
volatile uint32_t countA5;

volatile uint32_t countB1;
volatile uint32_t countB2;
volatile uint32_t countB3;
volatile uint32_t countB4;
volatile uint32_t countB5;

volatile uint32_t _millis = 0;
volatile uint32_t _micros = 0;

uint32_t curr;

void InitEnoderVal(void)
{
	countA1 = encodeRef;
	countA2 = encodeRef;
	countA3 = encodeRef;
	countA4 = encodeRef;
	countA5 = encodeRef;
	
	countB1 = encodeRef;
	countB2 = encodeRef;
	countB3 = encodeRef;
	countB4 = encodeRef;
	countB5 = encodeRef;
}

/*
void PortBIntHandler(void)
{
	if(GPIOIntStatus(GPIO_PORTB_BASE, false) & GPIO_PIN_1)
	{
		GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_1);
		
		if((GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7) >> 7) == CURL_IN)
			countA5++ ;
		else
			countA5-- ;
	}
}
*/

void PortCIntHandler(void)
{
//	if(GPIOIntStatus(GPIO_PORTC_BASE, false) & GPIO_PIN_6)
//	{
//		GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_6);
//		if((GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7) >> 7) == CURL_IN)
//			countB3++ ;
//		else
//			countB3-- ;
//	}	
	
	if(GPIOIntStatus(GPIO_PORTC_BASE, false) & GPIO_PIN_7)
	{
		GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_7);
		if((GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6) >> 6) == CURL_IN)
			countB2++ ;
		else
			countB2-- ;
	}
}
	
void PortDIntHandler(void)
{
//	if(GPIOIntStatus(GPIO_PORTD_BASE, false) & GPIO_PIN_1)
//	{
//		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_1);
//		
//		if((GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) >> 5) == CURL_IN)
//			countB4++ ;
//		else
//			countB4-- ;
//	}
	
	if(GPIOIntStatus(GPIO_PORTD_BASE, false) & GPIO_PIN_2)
	{
		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_2);
		
		if((GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6) >> 6) == CURL_IN)
			countB1++ ;
		else
			countB1-- ;
	}
	
//	else if(GPIOIntStatus(GPIO_PORTD_BASE, false) & GPIO_PIN_4)
//	{
//		GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_4);
//		
//		if((GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_7) >> 7) == CURL_IN)
//			countB5++ ;
//		else
//			countB5-- ;
//	}
}

/*
void PortFIntHandler(void)
{
	if(GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_0)
	{
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
		
		if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_6) >> 6) == CURL_IN)
			countA2++ ;
		else
			countA2-- ;
	}
	
	else if(GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_1)
	{
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_1);
		
		if((GPIOPinRead(GPIO_PORTA_BASE,GPIO_PIN_7) >> 7) == CURL_IN)
			countA3++ ;
		else
			countA3-- ;
	}

	else if(GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_2)
	{
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_2);
		
		if((GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) >> 5) == CURL_IN)
			countA4++ ;
		else
			countA4-- ;
	}
	
	else if(GPIOIntStatus(GPIO_PORTF_BASE, false) & GPIO_PIN_4)
	{
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
		
		if((GPIOPinRead(GPIO_PORTB_BASE,GPIO_PIN_6) >> 6) == CURL_IN)
			countA1++ ;
		else
			countA1-- ;
	}
}
*/

void SysTickIntHandler(void)
{
	_millis++;
}

uint32_t encodervalue(Encoder channel)
{
	if(channel == EncA1)
		return countA1;
	else if(channel == EncA2)
		return countA2;
	else if(channel == EncA3)
		return countA3;
	else if(channel == EncA4)
		return countA4;
	else if(channel == EncA5)
		return countA5;
	else if(channel == EncB1)
		return countB1;
	else if(channel == EncB2)
		return countB2;
	else if(channel == EncB3)
		return countB3;
	else if(channel == EncB4)
		return countB4;
	else if(channel == EncB5)
		return countB5;
	else	
		return 0;
}

uint32_t FingerPulses(int fingernumber)
{
	uint32_t Var = 0;
	switch(fingernumber)
	{
		case 0:
			Var = encodervalue(EncB1);
			break;
		case 1:
			Var = encodervalue(EncB2);
			break;
		case 2:
			Var = encodervalue(EncB3);
			break;
		case 3:
			Var = encodervalue(EncA4);
			break;
		case 4:
			Var = encodervalue(EncB5);
			break;
	}
	
	return Var;
}
