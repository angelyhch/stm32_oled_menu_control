#ifndef __Key__H_
#define __Key__H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include "Dri_KEY.h"

#define KEY1 1
#define KEY2 2
#define KEY3 3
#define KEY4 4

void Key_Init(void);
uint8_t Key_GetState(uint8_t Key_ID, uint8_t Key_State);

void Key_ResetState(uint8_t Key_ID, uint8_t Key_State);

#endif /* __Key__H_ */
