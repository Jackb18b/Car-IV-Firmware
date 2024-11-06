//Authors: Jonathon Brown, Justin Lopez
//11/5/2024

#include "MCP23017.h"

uint8_t MCP23017_INIT(MCP23017 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t hardwareAddress)
{
    dev->i2cHandle = i2cHandle;

    hardwareAddress &= 0b00000111; // hardware address should be from 0-7
    dev->deviceAddress = MCP23017_I2C_ADDR | (hardwareAddress << 1);
}



HAL_StatusTypeDef MCP23017_ReadPort(MCP23017 *dev, port port, uint8_t *data)
{
    if (port == portA)
        return MCP23017_ReadRegister(dev, MCP23017_GPIOA, data);
    else
        return MCP23017_ReadRegister(dev, MCP23017_GPIOB, data);
}
HAL_StatusTypeDef MCP23017_WritePort(MCP23017 *dev, port port, uint8_t *data)
{
    if (port == portA)
        return MCP23017_WriteRegister(dev, MCP23017_GPIOA, data);
    else
        return MCP23017_WriteRegister(dev, MCP23017_GPIOB, data);
}


HAL_StatusTypeDef MCP23017_SetPortDirection(MCP23017 *dev, port port, uint8_t pins)
{
    //pins = '1' is input
    if (port == portA)
        return MCP23017_WriteRegister(dev, MCP23017_IODIRA, (0b01111111 & pins));
    else
        return MCP23017_WriteRegister(dev, MCP23017_IODIRB, (0b01111111 & pins));
}

HAL_StatusTypeDef MCP23017_ReadRegister(MCP23017 *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_READ(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}

HAL_StatusTypeDef MCP23017_WriteRegister(MCP23017 *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_READ(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}