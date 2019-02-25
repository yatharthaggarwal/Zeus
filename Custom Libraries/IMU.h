#ifndef _IMU_
#define _IMU_

#include "Header.h"

#define LSM9DS1_ADDRESS_ACCELGYRO 0x6B
#define LSM9DS1_ADDRESS_MAG 0x1E

typedef enum
{
			LSM9DS1_ACCELRANGE_2G                = (0b00 << 3),
			LSM9DS1_ACCELRANGE_16G               = (0b01 << 3),
			LSM9DS1_ACCELRANGE_4G                = (0b10 << 3),
			LSM9DS1_ACCELRANGE_8G                = (0b11 << 3)
} AccRange;

typedef enum
{
      LSM9DS1_GYROSCALE_245DPS             = (0b00 << 3),  // +/- 245 degrees per second rotation
      LSM9DS1_GYROSCALE_500DPS             = (0b01 << 3),  // +/- 500 degrees per second rotation
      LSM9DS1_GYROSCALE_2000DPS            = (0b11 << 3)   // +/- 2000 degrees per second rotation
} GyroScale;

void initAcc(AccRange range);
void initGyro(GyroScale scale);
void readAcc(void);
void readGyro(void);
void CalibrateAcc(void);
void CalibrateGyro(void);
void setupIMU(void);

float findRoll(void);
float findPitch(void);

#endif
