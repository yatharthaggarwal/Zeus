#ifndef _Timer_
#define _Timer_

#include "Header.h"

void initSysTick(void);

uint32_t millis(void);
uint32_t micros(void);

void delay(uint32_t time_millis);

#endif
