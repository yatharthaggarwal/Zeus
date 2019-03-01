#include "AnalogSensor.h"

uint32_t uiADCValue[8];

void initADC(void)
{
	
	GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_3);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0))
	{
	}

	ADCSequenceDisable(ADC0_BASE, 0);
	ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

	ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH3);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH4);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 3, ADC_CTL_CH1);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 4, ADC_CTL_CH2);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 5, ADC_CTL_CH7);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 6, ADC_CTL_CH11);
	ADCSequenceStepConfigure(ADC0_BASE, 0, 7, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);

	ADCSequenceEnable(ADC0_BASE, 0);
}

uint16_t ReadADCChannel(Channel Ch)
{
	if(Ch == FSR1)
		return uiADCValue[0];
	else if(Ch == FSR2)
		return uiADCValue[1];
	else if(Ch == Curr1)
		return uiADCValue[2];
	else if(Ch == Curr2)
		return uiADCValue[3];
	else if(Ch == Curr3)
		return uiADCValue[4];
	else if(Ch == Curr4)
		return uiADCValue[5];
	else if(Ch == Curr5)
		return uiADCValue[6];
	else
		return 0;
}

uint16_t ReadADC(Channel Ch)
{
	uint16_t sigval;
	ADCIntClear(ADC0_BASE, 0);
	ADCProcessorTrigger(ADC0_BASE, 0);
	while(!ADCIntStatus(ADC0_BASE, 0, false))
	{
	}
	ADCSequenceDataGet(ADC0_BASE, 0, uiADCValue);
	
	sigval = ReadADCChannel(Ch);
	//UARTprintf("\n%d", sigval);
	return sigval;
}


