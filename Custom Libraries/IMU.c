#include "IMU.h"
#include <math.h>

const float PI = 3.1415;
const float Angle = 180.0;
	
int16_t Axx =	0;
int16_t Ayy	= 0;
int16_t Azz =	0;
int16_t Gxx = 0;
int16_t Gyy	= 0;
int16_t Gzz = 0;

uint8_t accBuffer[6] 	= {0,0,0,0,0,0};
uint8_t gyroBuffer[6] = {0,0,0,0,0,0};

bool calGyro = false;
bool calAcc	 = false;
	
const float Gres = 0.00875;
const float Ares = 0.000061;

float Ax = 0;
float Ay = 0;
float Az = 0;

float Gx = 0;
float Gy = 0;
float Gz = 0;

int16_t cal_Gx = 0;
int32_t sum_Gx = 0;
int16_t cal_Gy = 0;
int32_t sum_Gy = 0;
int16_t cal_Gz = 0;
int32_t sum_Gz = 0;

int16_t cal_Ax = 0;
int32_t sum_Ax = 0;
int16_t cal_Ay = 0;
int32_t sum_Ay = 0;
int16_t cal_Az = 0;
int32_t sum_Az = 0;

void initAcc(AccRange range)
{
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG8, 0x05);						// soft reset accleroometer+gyro
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG2_M, 0x0C);					// soft reset mag
	SysCtlDelay(16000000u/3u);
	
	// Enable the accelerometer continous
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG5_XL, 0x38);
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG6_XL, 0xC0);
	
	uint8_t reg = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG6_XL);
  reg &= ~(0b00011000);
  reg |= range;
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG6_XL, reg);
}


void initGyro(GyroScale scale)
{
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG1_G, 0xC0);				// enable gyro continuous on XYZ
	uint8_t reg = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG1_G);
  reg &= ~(0b00011000);
  reg |= scale;
	I2C_write(LSM9DS1_ADDRESS_ACCELGYRO, CTRL_REG1_G, reg);				// 
}

void readAcc(void)
{
	accBuffer[0] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_X_L_XL);
	accBuffer[1] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_X_H_XL);
	accBuffer[2] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Y_L_XL);
	accBuffer[3] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Y_H_XL);
	accBuffer[4] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Z_L_XL);
	accBuffer[5] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Z_H_XL);
	Axx = (accBuffer[1]<<8) | accBuffer[0];
	Ax = Axx * Ares;
	Ayy = (accBuffer[3]<<8) | accBuffer[2];
	Ay = Ayy * Ares;
	Azz = (accBuffer[5]<<8) | accBuffer[4];
	Az = Azz * Ares;
	if(calAcc)
	{
		Ax = Ax - cal_Ax;
		Ay = Ay - cal_Ay;
		Az = Az - cal_Az;
	}
}

void readGyro(void)
{
	gyroBuffer[0] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_X_L_G);
	gyroBuffer[1] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_X_H_G);
	gyroBuffer[2] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Y_L_G);
	gyroBuffer[3] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Y_H_G);
	gyroBuffer[4] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Z_L_G);
	gyroBuffer[5] = I2C_read(LSM9DS1_ADDRESS_ACCELGYRO, OUT_Z_H_G);
	Gxx = (gyroBuffer[1]<<8) | gyroBuffer[0];
	Gx = Gxx * Gres;
	Gyy = (gyroBuffer[3]<<8) | gyroBuffer[2];
	Gy = Gyy * Gres;
	Gzz = (gyroBuffer[5]<<8) | gyroBuffer[4];
	Gz = Gzz * Gres; 
	if(calGyro)
	{
		Gx = Gx - cal_Gx;
		Gy = Gy - cal_Gy;
		Gz = Gz - cal_Gz;
	}
}

void CalibrateGyro(void)
{
	for(uint16_t x = 0; x<1000; x++)
	{
		readGyro();
		sum_Gx += Gx;
		sum_Gy += Gy;
		sum_Gz += Gz;
	}
	cal_Gx = sum_Gx/1000;
	cal_Gy = sum_Gy/1000;
	cal_Gz = sum_Gz/1000;
	
	calGyro = true;
}

void CalibrateAcc(void)
{
	for(uint16_t x = 0; x<1000; x++)
	{
		readAcc();
		sum_Ax += Ax;
		sum_Ay += Ay;
		sum_Az += Az;
	}
	cal_Ax = sum_Ax/1000;
	cal_Ay = sum_Ay/1000;
	cal_Az = sum_Az/1000;
	
	calAcc = true;
}
	
void setupIMU(void)
{
	initAcc(LSM9DS1_ACCELRANGE_2G);
	initGyro(LSM9DS1_GYROSCALE_245DPS);
//	CalibrateAcc();
//	CalibrateGyro();
}

float findRoll(void)
{
	float _roll = atan2(Ay, Az);
	_roll  *=  Angle / PI;
	return _roll;
}

float findPitch(void)
{
	float _pitch = atan2(-Ax, sqrt(Ay * Ay + Az * Az));
	_pitch *=  Angle/ PI;
	return _pitch;
}
