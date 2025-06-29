#ifndef __DRI__MYI2C_H
#define __DRI__MYI2C_H

#include "stm32f1xx_hal.h"
#include <stdint.h>
#define DELAY 1

typedef struct MyI2C_TypeStructure
{
    // GPIO_Pin_0 ~ GPIO_Pin_15
    uint16_t SCL_Pin;
    // GPIOA ~ GPIOG
    GPIO_TypeDef *SCL_GPIO_Port;
    // SDA
    uint16_t SDA_Pin;
    GPIO_TypeDef *SDA_GPIO_Port;
    // GPIO时钟
    void (*GPIO_Clock_Enable)(void);

} MyI2C_TypeStructure;

void MyI2C_Init(MyI2C_TypeStructure *Myi2c);
void MyI2C_Start(MyI2C_TypeStructure *Myi2c);
void MyI2C_Stop(MyI2C_TypeStructure *Myi2c);
void MyI2C_SendByte(MyI2C_TypeStructure *Myi2c, uint8_t Byte);
void MyI2C_SendAck(MyI2C_TypeStructure *Myi2c, uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(MyI2C_TypeStructure *Myi2c);
uint8_t MyI2C_ReceiveByte(MyI2C_TypeStructure *Myi2c);
uint8_t MyI2C_ReceiveByte(MyI2C_TypeStructure *Myi2c);

#endif
