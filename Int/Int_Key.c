#include "Int_Key.h"
#include "main.h"
#include "cmsis_os.h"

uint8_t read_button_pin1(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
}
uint8_t read_button_pin2(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
}
uint8_t read_button_pin3(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin);
}
uint8_t read_button_pin4(uint8_t btn_id)
{
    return HAL_GPIO_ReadPin(KEY4_GPIO_Port, KEY4_Pin);
}

// 创建软件定时器，用于实现5ms的定时扫描
static osTimerId_t Key_Scan_Timer;
// 定时器回调函数

static void Key_Scan_Timer_Callback(void *argument)
{
    button_ticks();
}

// 创建定时器
static void Key_Scan_Timer_Init(void)
{
    Key_Scan_Timer = osTimerNew(Key_Scan_Timer_Callback, osTimerPeriodic, NULL, NULL);
    osTimerStart(Key_Scan_Timer, 5);
}

// 初始化按键
void Key_Init(void)
{
    // 初始化按键Int接口
    Int_KEY_init();
    // 创建定时器
    // 在循环任务中调用button_ticks()，每5ms调用一次
    Key_Scan_Timer_Init();
}

// #define Key_GetState(Key_ID, Key_State) \
//     (key_state##Key_ID & (0x1 << Key_State))

// key_state[Key_ID] 是在Key_Scan_Timer_Callback中更新的
uint8_t Key_GetState(uint8_t Key_ID, uint8_t Key_State)
{
    switch (Key_ID)
    {
    case KEY1:
        return key_state1 & (0x1 << Key_State);
    case KEY2:
        return key_state2 & (0x1 << Key_State);
    case KEY3:
        return key_state3 & (0x1 << Key_State);
    case KEY4:
        return key_state4 & (0x1 << Key_State);
    default:
        return 0;
    }
}

void Key_ResetState(uint8_t Key_ID, uint8_t Key_State)
{
    switch (Key_ID)
    {
    case KEY1:
        key_state1 &= ~(0x1 << Key_State);
        break;
    case KEY2:
        key_state2 &= ~(0x1 << Key_State);
        break;
    case KEY3:
        key_state3 &= ~(0x1 << Key_State);
        break;
    case KEY4:
        key_state4 &= ~(0x1 << Key_State);
        break;
    default:
        break;
    }
}
