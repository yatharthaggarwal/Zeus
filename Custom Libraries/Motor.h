/*
 * @file Motor.h
 *
 * @brief Header file for motor.c
 *
 * @author Aether Biomedical
 * Contact: info@aetherbiomedical.com
 *
 * @description
 *								Unit		|	Direction	|	PWM	| Encoder ChannelA	|	Encoder ChannelB
 *								--------+-----------+-----+-------------------+------------------
 *								Motor1	|	PB6				|	PB7	|	PF4								|	PD2
 *								Motor2	|	PA6				|	PC5	|	PF0								|	PC7
 *								Motor3	|	PA7				|	PC4	|	PF1								|	PC6
 *								Motor4	|	PE5				|	PE4	|	PF2								| PD1
 *								Motor5	|	PD5				| PB4	|	PB1								| PD4
 */
 
#ifndef _Motor_
#define _Motor_

#include "Header.h"

#define M1DirPin PB6
#define M2DirPin PA6
#define M3DirPin PA7
#define M4DirPin PE5
#define M5DirPin PD1

#define M1PWMPin PB7
#define M2PWMPin PC5
#define M3PWMPin PC4
#define M4PWMPin PE4
#define M5PWMPin PB4

#define M1EncA PF4
#define M2EncA PF0 //locked 
#define M3EncA PF1
#define M4EncA PF2
#define M5EncA PB1

#define M1EncB PD2
#define M2EncB PC7
#define M3EncB PC6
#define M4EncB PD1
#define M5EncB PD4

typedef enum
{
	PB6,	PA6,	PA7,	PE5,	PD1
}Phase;

typedef enum
{
	PB7,	PC5,	PC4,	PE4,	PB4
}Enable;

void init_motors(void);
void init_encoders(void);
void motorDirection(Phase port, bool state);
void motorPWM(Enable port, uint16_t pwm);

#endif
