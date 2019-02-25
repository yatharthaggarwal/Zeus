#ifndef _Header_
#define _Header_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/adc.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/i2c.h"

#include "Timer.h"
#include "InitPorts.h"
#include "Motor.h"
#include "AnalogSensor.h"
#include "InterruptHandlers.h"
#include "SerialUSB.h"
#include "I2Ccustom.h"
#include "IMU.h"
#include "LSM9DS1_Registers.h"
#include "ControlMechanism.h" 
#include "Grips.h"
#include "Fingers.h"
#include "FSRsignal.h"

#endif
