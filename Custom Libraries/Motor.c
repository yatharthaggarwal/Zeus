#include "Motor.h"
#include "InterruptHandlers.h"


bool M1PWMflag = 0;
bool M2PWMflag = 0;
bool M3PWMflag = 0;
bool M4PWMflag = 0;
bool M5PWMflag = 0;

void init_motors(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){		}
	
	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

	GPIOPinConfigure(GPIO_PB7_M0PWM1);
	GPIOPinConfigure(GPIO_PC5_M0PWM7);
	GPIOPinConfigure(GPIO_PC4_M0PWM6);
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);
	GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
	GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
	
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_6);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
	
	GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,0x00);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0x00);
	GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0x00);
	GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0x00);
	GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1,0x00);
	
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_GEN_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_GEN_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_GEN_NO_SYNC);
	PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_GEN_NO_SYNC);
	
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 1000);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 1000);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, 1000);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 1000);
		
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1);
	
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);
	PWMGenEnable(PWM0_BASE, PWM_GEN_1);
	PWMGenEnable(PWM0_BASE, PWM_GEN_2);
	PWMGenEnable(PWM0_BASE, PWM_GEN_3);

	PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, false);
	PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);
	PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
	PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
}

void init_encoders()
{
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
//	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_2);
//	GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_1);
	
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_7);
//	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
//	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_1);
//	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_4);	
	
//	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);
//	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_0);
//	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_1);
//	GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_2);
//	GPIOIntDisable(GPIO_PORTB_BASE, GPIO_PIN_1);
	
	GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_7);
//	GPIOIntDisable(GPIO_PORTC_BASE, GPIO_PIN_6);
//	GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_1);
//	GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_4);
	
//	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
//	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
//	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_1);
//	GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_2);
//	GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_1);
	
	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_7);
//	GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_6);
//	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_1);
//	GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_4);
	
//	GPIOIntRegister(GPIO_PORTB_BASE,PortBIntHandler);
	GPIOIntRegister(GPIO_PORTC_BASE,PortCIntHandler);
	GPIOIntRegister(GPIO_PORTD_BASE,PortDIntHandler);
//	GPIOIntRegister(GPIO_PORTF_BASE,PortFIntHandler);
	
//	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_2,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_1,GPIO_RISING_EDGE);
	
	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_2,GPIO_RISING_EDGE);
	GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_7,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_6,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_1,GPIO_RISING_EDGE);
//	GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_4,GPIO_RISING_EDGE);
	
//	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
//	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0);
//	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_1);
//	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_2);
//	GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_1);
	
	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_7);
//	GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_6);
//	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_1);
//	GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_4);
	
}

void motorDirection(Phase port, bool state)
{
	if(state)
	{
		if(port == M1DirPin)
			GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,GPIO_PIN_6);
		else if(port == M2DirPin)
			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,GPIO_PIN_6);
		else if(port == M3DirPin)
			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,GPIO_PIN_7);
		else if(port == M4DirPin)
			GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,GPIO_PIN_5);
		else if(port == M5DirPin)
			GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1,0x00);
	}
	else
	{
		if(port == M1DirPin)
			GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6,0x00);
		else if(port == M2DirPin)
			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_6,0x00);
		else if(port == M3DirPin)
			GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_7,0x00);
		else if(port == M4DirPin)
			GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_5,0x00);
		else if(port == M5DirPin)
			GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1,GPIO_PIN_1);
	}
}

void motorPWM(Enable port, uint16_t pwm)
{
	if(pwm == 0)
	{
		if(port == M1PWMPin)
		{
			PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, false);
			M1PWMflag = 0;
		}
		if(port == M2PWMPin)
		{
			PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);
			M2PWMflag = 0;
		}
		if(port == M3PWMPin)
		{
			PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
			M3PWMflag = 0;
		}
		if(port == M4PWMPin)
		{
			PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
			M4PWMflag = 0;
		}
		if(port == M5PWMPin)
		{
			PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, false);
			M5PWMflag = 0;		
		}
	}
	else
	{
		if(port == M1PWMPin)
		{
			if(M1PWMflag == 0)
				PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);
			
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, pwm);
			M1PWMflag = 1;
		}
		else if(port == M2PWMPin)
		{
			if(M2PWMflag == 0)
				PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
				
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, pwm);
			M2PWMflag = 1;			
		}
		else if(port == M3PWMPin)
		{
			if(M3PWMflag == 0)
				PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
			
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, pwm);
			M3PWMflag = 1;
		}
		else if(port == M4PWMPin)
		{
			if(M4PWMflag == 0)
				PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
			
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, pwm);
			M4PWMflag = 1;
		}
		
		else if(port == M5PWMPin)
		{
			if(M5PWMflag == 0)
				PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
			
			PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, pwm);
			M5PWMflag = 1;
		}
	}
}

