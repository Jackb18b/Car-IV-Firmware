#include "TCAL9538RSVR.h"

#define TCAL9538RSVR_ADDR 0b1110000
#define TCAL9538RSVR_GPIO_INPUT 0x00
#define TCAL9538RSVR_GPIO_OUTPUT 0x01
#define TCAL9538RSVR_DIR_CONFIG 0x03
#define TCAL9538RSVR_INT_CONFIG 0x45
#define TCAL9538RSVR_INT_STATUS 0x46

uint8_t bitmask_to_pin(uint8_t bitmask) {
    uint8_t pin_number = 0;
    if (bitmask == 0) 
    {
        return -1;
    }
    
    while ((bitmask & 1) == 0) 
    {
        bitmask >>= 1;
        pin_number++;
    }
    
    return pin_number; 
}

uint8_t TCAL9538RSVR_INIT(TCAL9538RSVR *dev, I2C_HandleTypeDef *i2cHandle, uint8_t hardwareAddress)
{
    dev->i2cHandle = i2cHandle;

    hardwareAddress &= 0b00000011; // hardware address should be from 0-3
    dev->deviceAddress = TCAL9538RSVR_ADDR | (hardwareAddress << 1);
}


/**
 * @brief Sets GPIO expansion direction
 * @param uint8_t : bitMask -> '1' is input
 * @retval HAL_StatusTypeDef : HAL_Status
 */
HAL_StatusTypeDef TCAL9538RSVR_SetDirection(TCAL9538RSVR* dev, uint8_t bitMask)
{
    return TCAL9538RSVR_WriteRegister(dev, TCAL9538RSVR_DIR_CONFIG, bitMask);
}

/**
 * @brief Sets interrupt register
 * @param uint8_t : bitMask -> '0' is input enabled
 * @retval HAL_StatusTypeDef : HAL_Status
 */
HAL_StatusTypeDef TCAL9538RSVR_SetInterrupts(TCAL9538RSVR* dev, uint8_t bitMask)
{
    return TCAL9538RSVR_WriteRegister(dev, TCAL9538RSVR_INT_CONFIG, bitMask);
}

/**
 * @brief Handles interrupt and returns pin# that triggered
 * @param uint8_t* : pin -> expect to be overwritten
 *                 : if pin == 255, no interrupt triggered
 * @retval uint8_t : errNum
 */
HAL_StatusTypeDef TCAL9538RSVR_HandleInterrupt(TCAL9538RSVR* dev, uint8_t *pin)
{
    uint8_t errNum = 0;
	HAL_StatusTypeDef status;
    uint8_t intPinBitMask = 0;

    status = TCAL9538RSVR_ReadRegister(dev, TCAL9538RSVR_INT_STATUS, intPinBitMask);
    errNum += (status != HAL_OK);

    pin = bitmask_to_pin(intPinBitMask);
    if (pin == 255) // no high pin detected
    {
        return (errNum); // return early, no need to reset
    }

    status = TCAL9538RSVR_WriteRegister(dev, TCAL9538RSVR_INT_STATUS, intPinBitMask);
    errNum += (status != HAL_OK);

    return (errNum);
}


HAL_StatusTypeDef TCAL9538RSVR_ReadInput(TCAL9538RSVR* dev, uint8_t *data)
{
    return TCAL9538RSVR_ReadRegister(dev, TCAL9538RSVR_GPIO_INPUT, data);
}
HAL_StatusTypeDef TCAL9538RSVR_SetOutput(TCAL9538RSVR* dev, uint8_t *data)
{
    return TCAL9538RSVR_WriteRegister(dev, TCAL9538RSVR_GPIO_OUTPUT, data);
}

//low level functions
HAL_StatusTypeDef TCAL9538RSVR_ReadRegister(TCAL9538RSVR *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_READ(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}
HAL_StatusTypeDef TCAL9538RSVR_WriteRegister(TCAL9538RSVR *dev, uint8_t reg, uint8_t *data)
{
    return(HAL_I2C_MEM_READ(dev->i2cHandle, dev->deviceAddress, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY));
}
