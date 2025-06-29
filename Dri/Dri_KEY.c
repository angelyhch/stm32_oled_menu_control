/**
 * @brief
 * FIXME:
 * 1. 一定记住要把button_ticks(); 放到程序5ms的脉冲里面，不然按键检测不出来，可以单独开一个线程
 * 2. 一定要执行KEY_init(); 初始化按键init，attach, start, 确保按键功能启动
 *
 */

/*
//// @brief 按键使用例程
//// 主程序中重写对应的函数即可
//// 1. read_button_pin1 读取按键状态
//// 2. Callback_SINGLE_CLICK1 单击回调函数
//// 3. Callback_DOUBLE_CLICK1 双击回调函数
//// 如果需要更多的功能，如长按，按下PRESS_DOWN，抬起PRESS_UP，需要自己写对应的attach函数，然后在回调函数中实现

uint8_t read_button_pin2(uint8_t btn_id)
{
  return HAL_GPIO_ReadPin(K1_GPIO_Port, K1_Pin);
}
void Callback_SINGLE_CLICK2(void *arg)
{
  HAL_GPIO_TogglePin(LED_PA6_GPIO_Port, LED_PA6_Pin);
  debug("SINGLE_CLICK2\r\n");
}

void Callback_DOUBLE_CLICK2(void *arg)
{
  HAL_GPIO_WritePin(LED_PC13_GPIO_Port, LED_PC13_Pin, GPIO_PIN_SET);
  debug("DOUBLE_CLICK2\r\n");
}
*/

#include "Dri_KEY.h"
#include "dbg.h"

static Button button1;
static Button button2;
static Button button3;
static Button button4;

Key_state key_state1;
Key_state key_state2;
Key_state key_state3;
Key_state key_state4;

__weak uint8_t read_button_pin1(uint8_t btn_id)
{
    UNUSED(btn_id);
    return 0;
}
__weak void Callback_SINGLE_CLICK1(void *arg)
{
    UNUSED(arg);
    key_state1 |= (0x1 << KEY_STATE_SINGLE);
}

__weak void Callback_DOUBLE_CLICK1(void *arg)
{
    UNUSED(arg);
    key_state1 |= (0x1 << KEY_STATE_DOUBLE);
}

__weak uint8_t read_button_pin2(uint8_t btn_id)
{
    UNUSED(btn_id);
    return 0;
}
__weak void Callback_SINGLE_CLICK2(void *arg)
{
    UNUSED(arg);
    key_state2 |= (0x1 << KEY_STATE_SINGLE);
}

__weak void Callback_DOUBLE_CLICK2(void *arg)
{
    UNUSED(arg);
    key_state2 |= (0x1 << KEY_STATE_DOUBLE);
}
__weak uint8_t read_button_pin3(uint8_t btn_id)
{
    UNUSED(btn_id);
    return 0;
}
__weak void Callback_SINGLE_CLICK3(void *arg)
{
    UNUSED(arg);
    key_state3 |= (0x1 << KEY_STATE_SINGLE);
}

__weak void Callback_DOUBLE_CLICK3(void *arg)
{
    UNUSED(arg);
    key_state3 |= (0x1 << KEY_STATE_DOUBLE);
}
__weak uint8_t read_button_pin4(uint8_t btn_id)
{
    UNUSED(btn_id);
    return 0;
}
__weak void Callback_SINGLE_CLICK4(void *arg)
{
    UNUSED(arg);
    key_state4 |= (0x1 << KEY_STATE_SINGLE);
}

__weak void Callback_DOUBLE_CLICK4(void *arg)
{
    UNUSED(arg);
    key_state4 |= (0x1 << KEY_STATE_DOUBLE);
}

void Int_KEY_init(void)
{

    button_init(&button1, read_button_pin1, 0, 1);
    button_attach(&button1, SINGLE_CLICK, Callback_SINGLE_CLICK1);
    button_attach(&button1, DOUBLE_CLICK, Callback_DOUBLE_CLICK1);
    button_start(&button1);

    button_init(&button2, read_button_pin2, 0, 2);
    button_attach(&button2, SINGLE_CLICK, Callback_SINGLE_CLICK2);
    button_attach(&button2, DOUBLE_CLICK, Callback_DOUBLE_CLICK2);
    button_start(&button2);

    button_init(&button3, read_button_pin3, 0, 3);
    button_attach(&button3, SINGLE_CLICK, Callback_SINGLE_CLICK3);
    button_attach(&button3, DOUBLE_CLICK, Callback_DOUBLE_CLICK3);
    button_start(&button3);

    button_init(&button4, read_button_pin4, 0, 4);
    button_attach(&button4, SINGLE_CLICK, Callback_SINGLE_CLICK4);
    button_attach(&button4, DOUBLE_CLICK, Callback_DOUBLE_CLICK4);
    button_start(&button4);
}
