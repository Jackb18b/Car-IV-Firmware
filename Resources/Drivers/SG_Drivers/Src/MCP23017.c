//Authors: Jonathon Brown
//11/5/2024

#include "MCP23017.h"

uint8_t MCP23017_INIT(MCP23017 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t hardwareAddress)
{
    dev->i2cHandle = i2cHandle;

    // hardware address should be from 0-7
    if (hardwareAddress > 7)
    {
        //return early?
        return 1; //?
    }
    dev->deviceAddress = MCP23017_I2C_ADDR | (hardwareAddress << 1);
}

HAL_StatusTypeDef MCP23017_ReadRegister(MCP23017 *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_READ(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}

HAL_StatusTypeDef MCP23017_WriteRegister(MCP23017 *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_WRITE(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}