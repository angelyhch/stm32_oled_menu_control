#include "MyTasks.h"
#include "Int_LED.h"
#include "Int_OLED.h"
#include "Int_KEY.h"
#include "dbg.h"

#include "Comp_OLED_Menu.h"
#include "Comp_OLED_Job.h"

void StartTask02(void *argument)
{
    OLED_Init();
    Key_Init();
    Comp_OLED_Menu_Init();

    // OLED_ShowString(0, 48, "Hello World!", OLED_8X16);
    // OLED_Update();

    // test_multi_tree();

    for (;;)
    {

        menu_key_scan();
        osDelay(10);
    }
}
