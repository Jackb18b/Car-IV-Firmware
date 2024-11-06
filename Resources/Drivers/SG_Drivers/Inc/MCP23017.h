//Authors: Jonathon Brown, Justin Lopez

#ifdef __cplusplus
extern "C"{
#endif

#ifndef MCP23017_H
#define MCP23017_H

#include "stm32l4xx_hal.h"

#define MCP23017_I2C_ADDR (0b01000000) // bits 1-3 are set by hardware -> bit 0 is R/W
// addr = MCP23017_I2C_ADDR | (0b(A2)(A1)(A0)) | 0

typedef enum
{
    MCP23017_IODIRA =        0x00, 
    MCP23017_IODIRB =        0x01, 
    MCP23017_IPOLA =         0x02, 
    MCP23017_IPOLB =         0x03, 
    MCP23017_GPINTENA =      0x04, 
    MCP23017_GPINTENB =      0x05, 
    MCP23017_DEFVALA =       0x06, 
    MCP23017_DEFVALB =       0x07, 
    MCP23017_INTCONA =       0x08, 
    MCP23017_INTCONB =       0x09, 
    MCP23017_IOCON =         0x0A, 
    MCP23017_IOCON_ALT =     0x0B, 
    MCP23017_GPPUA =         0x0C, 
    MCP23017_GPPUB =         0x0D, 
    MCP23017_INTFA =         0x0E, 
    MCP23017_INTFB =         0x0F, 
    MCP23017_INTCAPA =       0x10, 
    MCP23017_INTCAPB =       0x11, 
    MCP23017_GPIOA =         0x12, 
    MCP23017_GPIOB =         0x13, 
    MCP23017_OLATA =         0x14, 
    MCP23017_OLATB =         0x15  
}MCP23017_Register;

typedef struct 
{
    I2C_HandleTypeDef *i2cHandle;

    uint8_t deviceAddress; // do we even need to do this in struct/handled in i2chandle

    // set up interrupts?
    // default values in registers to trigger ints? -> set up func?

    

}MCP23017;

typedef enum{
    portA = 0,
    portB = 1
}port;

uint8_t MCP23017_INIT(MCP23017 *dev, I2C_HandleTypeDef *i2cHandle, uint8_t hardwareAddress);

//higher level funcs
HAL_StatusTypeDef MCP23017_ReadPort(MCP23017 *dev, port port, uint8_t *data);
HAL_StatusTypeDef MCP23017_WritePort(MCP23017 *dev, port port, uint8_t *data);

HAL_StatusTypeDef MCP23017_SetPortDirection(MCP23017 *dev, port port, uint8_t pins);

//low level functions
HAL_StatusTypeDef MCP23017_ReadRegister(MCP23017 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MCP23017_WriteRegister(MCP23017 *dev, uint8_t reg, uint8_t *data);



#endif

#ifdef __cplusplus
}

#endif