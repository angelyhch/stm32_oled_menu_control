#ifndef __LED__H_
#define __LED__H_

#include "main.h"
#include "cmsis_os.h"
// // x 传入参数 LED1  LED2 LED3 LED4
// #define LED_On(x) HAL_GPIO_WritePin(x##_GPIO_Port, x##_Pin, GPIO_PIN_RESET)
// #define LED_Off(x) HAL_GPIO_WritePin(x##_GPIO_Port, x##_Pin, GPIO_PIN_SET)
// #define LED_Toggle(x) HAL_GPIO_TogglePin(x##_GPIO_Port, x##_Pin)
// #define LED_All_On() \
//     LED_On(LED1);    \
//     LED_On(LED2);    \
//     LED_On(LED3);    \
//     LED_On(LED4)
// #define LED_All_Off() \
//     LED_Off(LED1);    \
//     LED_Off(LED2);    \
//     LED_Off(LED3);    \
//     LED_Off(LED4)

typedef enum
{
    LED1 = 1,
    LED2 = 2,
    LED3 = 3,
    LED4 = 4,
} LED_TypeDef;

void LED_On(LED_TypeDef led);
void LED_Off(LED_TypeDef led);
void LED_Toggle(LED_TypeDef led);
void LED_All_On(void);
void LED_All_Off(void);

void LED_Blink(LED_TypeDef led, uint32_t time_ms);
#endif // !__LED__H_
