#include "Timer.h"

extern void SysTickIntHandler(void);
uint32_t last_count = 0;
extern uint32_t _millis;
extern uint32_t _micros;

void initSysTick(void)
{
	SysTickPeriodSet(SysCtlClockGet()/1000-1);
	SysTickIntRegister(SysTickIntHandler);
	IntMasterEnable();
  SysTickIntEnable();
  SysTickEnable();
}

uint32_t millis(void)
{
	return _millis;
}
uint32_t micros(void)
{
	return _micros;
}

void delay(uint32_t time_millis)
{
	last_count = _millis;
	while((_millis - last_count) < time_millis)
	{
	}
}
