#ifndef _I2Ccustom_
#define _I2Ccustom_

#include "Header.h"

void initI2C(void);
void I2C_write(uint32_t slave_addr, uint8_t reg, uint8_t data);
uint32_t I2C_read(uint32_t slave_addr, uint8_t reg);

#endif
