#ifndef __KEY_H__
#define __KEY_H__
#include "main.h"
#include "multi_button.h"

typedef uint8_t Key_state;

extern Key_state key_state1;
extern Key_state key_state2;
extern Key_state key_state3;
extern Key_state key_state4;

#define KEY_STATE_SINGLE 1
#define KEY_STATE_DOUBLE 2

void Int_KEY_init(void);
#endif

/*
// FIXME: 初始化按键
    // [ ]
uint8_t read_button_pin1(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY_A3_GPIO_Port, KEY_A3_Pin);
}
    // [ ]
uint8_t read_button_pin2(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY_B11_GPIO_Port, KEY_B11_Pin);
}
void my_StartTask03(void *argument)
{
    // [ ]
    KEY_init();
    for (;;)
    {
        // [ ]
        button_ticks();
        osDelay(5);
    }
}

*/

/*

// FIXME: 住循环中使用按键
    // [ ]
    for (;;)
    {

        // key1单击
        if (key_state1 & (0x1 << 1))
        {
            debug("SINGLE_CLICK1\r\n");
            // [ ] 必须清零
            key_state1 &= ~(0x1 << 1);
        }
        if (key_state1 & (0x1 << 2))
        {
            debug("DOUBLE_CLICK1\r\n");
            // [ ] 必须清零
            key_state1 &= ~(0x1 << 2);
        }

        // key2单击
        if (key_state2 & (0x1 << 1))
        {
            debug("SINGLE_CLICK2\r\n");
            // [ ] 必须清零
            key_state2 &= ~(0x1 << 1);
        }
        if (key_state2 & (0x1 << 2))
        {
            debug("DOUBLE_CLICK2\r\n");
            // [ ] 必须清零
            key_state2 &= ~(0x1 << 2);
        }


*/
