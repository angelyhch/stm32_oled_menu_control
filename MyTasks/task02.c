#include "MyTasks.h"
#include "Int_LED.h"
#include "Int_OLED.h"
#include "Int_KEY.h"
#include "dbg.h"

void StartTask02(void *argument)
{
    OLED_Init();
    Key_Init();
    OLED_ShowString(0, 0, "Hello World!", OLED_8X16);
    OLED_Update();

    for (;;)
    {

        if (Key_GetState(KEY1, KEY_STATE_SINGLE))
        {
            LED_On(LED1);
            Key_ResetState(KEY1, KEY_STATE_SINGLE);
        }
        if (Key_GetState(KEY2, KEY_STATE_SINGLE))
        {
            LED_Off(LED1);
            Key_ResetState(KEY2, KEY_STATE_SINGLE);
        }
        if (Key_GetState(KEY3, KEY_STATE_SINGLE))
        {
            LED_On(LED2);
            Key_ResetState(KEY3, KEY_STATE_SINGLE);
        }
        if (Key_GetState(KEY4, KEY_STATE_SINGLE))
        {
            LED_Off(LED2);
            Key_ResetState(KEY4, KEY_STATE_SINGLE);
        }

        osDelay(1000);
    }
}
