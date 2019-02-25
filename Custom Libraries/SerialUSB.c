#include "SerialUSB.h"

void serialBegin(int16_t baud_rate)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	
	GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
	
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_SYSTEM);
  UARTStdioConfig(0, baud_rate, SysCtlClockGet());
	
	SysCtlDelay(16000000u/ 16u);
	UARTprintf("\n Serial Communication Begins \n");
	
}

void UARTprintfloat(float value)
{
	int a,d1,d2,d3;
	float b;
	a = (int)value;
	if(value < 0)
	{
		b = a - value;
		if (a == 0)
			UARTprintf("-");
	}
	else
		b = value - a;
		
	d1 = b*10;
	d2 = b*100 - d1*10;
	d3 = b*1000 - (d1*100 + d2*10);

		
	UARTprintf("%d.%d%d%d",a,d1,d2,d3);
}
