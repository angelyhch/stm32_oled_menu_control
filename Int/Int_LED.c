#include "Int_LED.h"

void LED_On(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
        break;
    case LED2:
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
        break;
    case LED3:
        HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
        break;
    case LED4:
        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_RESET);
        break;
    default:
        break;
    }
}

void LED_Off(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
        break;
    case LED2:
        HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
        break;
    case LED3:
        HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
        break;
    case LED4:
        HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}

void LED_Toggle(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
        break;
    case LED2:
        HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
        break;
    case LED3:
        HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
        break;
    case LED4:
        HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
        break;
    default:
        break;
    }
}

void LED_All_On()
{
    LED_On(LED1);
    LED_On(LED2);
    LED_On(LED3);
    LED_On(LED4);
}

void LED_All_Off()
{
    LED_Off(LED1);
    LED_Off(LED2);
    LED_Off(LED3);
    LED_Off(LED4);
}

// 原始闪烁程序可以不同间隔
void LED_Blink_Raw(LED_TypeDef led, uint32_t on_time_ms, uint32_t off_time_ms)
{
    LED_On(led);
    osDelay(on_time_ms);
    LED_Off(led);
    osDelay(off_time_ms);
}

void LED_Blink(LED_TypeDef led, uint32_t time_ms)
{
    LED_Blink_Raw(led, time_ms, time_ms);
}
