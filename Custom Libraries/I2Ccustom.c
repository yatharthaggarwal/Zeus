#include "I2Ccustom.h"

void initI2C(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
	
	GPIOPinConfigure(GPIO_PB2_I2C0SCL);
	GPIOPinConfigure(GPIO_PB3_I2C0SDA);
	
	GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
  GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);
	
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
	
	HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
	
//	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
//	GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
}

void I2C_write(uint32_t slave_addr, uint8_t reg, uint8_t data)
{
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false); // write mode
	I2CMasterDataPut(I2C0_BASE, reg);
	while (I2CMasterBusy(I2C0_BASE));
	
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START); //I2C_MASTER_CMD_FIFO_BURST_SEND_START
	while (I2CMasterBusy(I2C0_BASE));
	
	I2CMasterDataPut(I2C0_BASE, data);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);  //I2C_MASTER_CMD_FIFO_BURST_SEND_FINISH
	
	while (I2CMasterBusy(I2C0_BASE));
}

uint32_t I2C_read(uint32_t slave_addr, uint8_t reg)
{
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, false);  					// write mode
	I2CMasterDataPut(I2C0_BASE, reg);																//specify register to be read
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);		//send control byte and register address byte to slave device
	while(I2CMasterBusy(I2C0_BASE));
	
	I2CMasterSlaveAddrSet(I2C0_BASE, slave_addr, true);							// read mode 
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);			//send control byte and read from the register we specified
	while(I2CMasterBusy(I2C0_BASE));
	
	return (I2CMasterDataGet(I2C0_BASE));
}

