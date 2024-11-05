//Authors: Jonathon Brown

#ifdef __cplusplus
extern "C"{
#endif

#ifndef MCP23017_HPP_
#define MCP23017_HPP_

//registers
#define GPIOA_CONFIG 0x00
#define GPIOB_CONFIG 0x01

#define GPIO_PORTA_8BIT 0x12
#define GPIO_PORTB_8BIT 0x13

#include "stm32l4xx_hal.h"

#define MCP23017_I2C_ADDR (0b01000000) // bits 1-3 are set by hardware -> bit 0 is R/W
// addr = MCP23017_I2C_ADDR | (0b(A2)(A1)(A0)) | 0
typedef struct 
{
    I2C_HandleTypeDef *i2cHandle;

    uint8_t deviceAddress;

    

}MCP23017;

typedef enum{
    portA = 0,
    portB = 1
}port;

uint8_t MCP23017_INIT(MCP23017 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t hardwareAddress);

//higher level funcs
HAL_StatusTypeDef MCP23017_ReadPort(MCP23017 *dev, port port, uint8_t *data);
HAL_StatusTypeDef MCP23017_WritePort(MCP23017 *dev, port port, uint8_t *data);

HAL_StatusTypeDef MCP23017_SetPortOut(MCP23017 *dev, port port);
HAL_StatusTypeDef MCP23017_SetPortIn(MCP23017 *dev, port port);

//low level functions
HAL_StatusTypeDef MCP23017_ReadRegister(MCP23017 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MCP23017_WriteRegister(MCP23017 *dev, uint8_t reg, uint8_t *data);



#endif

#ifdef __cplusplus
}

#endif