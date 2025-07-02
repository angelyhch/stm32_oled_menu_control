#include "Comp_OLED_Job.h"

static uint8_t g_led_flow_direction;

// 创建定时器实现LED灯闪烁
static osTimerId_t led1_timer_id;
static osTimerId_t led2_timer_id;
static osTimerId_t led3_timer_id;
static osTimerId_t led4_timer_id;
static osTimerId_t led_flow_timer_id;

// 定时器回调函数
static void led1_timer_callback(void *arg)
{
    LED_Toggle(LED1);
}
static void led2_timer_callback(void *arg)
{
    LED_Toggle(LED2);
}
static void led3_timer_callback(void *arg)
{
    LED_Toggle(LED3);
}
static void led4_timer_callback(void *arg)
{
    LED_On(LED4);
}

static void led_flow_timer_callback(void *arg)
{
    static LED_TypeDef last_led;
    static LED_TypeDef current_led;
    LED_Off(last_led);
    LED_On(current_led);
    last_led = current_led;
    if (g_led_flow_direction == 0)
    {
        if (current_led == LED3)
        {
            current_led = LED1;
        }
        else
        {
            current_led = (LED_TypeDef)((int)current_led + 1);
        }
    }
    else
    {

        if (current_led == LED1)
        {
            current_led = LED3;
        }
        else
        {
            current_led = (LED_TypeDef)((int)current_led - 1);
        }
    }
    osTimerStart(led_flow_timer_id, 1000);
}

void create_led_timer(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        led1_timer_id = osTimerNew(led1_timer_callback, osTimerPeriodic, NULL, NULL);
        break;
    case LED2:
        led2_timer_id = osTimerNew(led2_timer_callback, osTimerPeriodic, NULL, NULL);
        break;
    case LED3:
        led3_timer_id = osTimerNew(led3_timer_callback, osTimerPeriodic, NULL, NULL);
        break;
    case LED4:
        led4_timer_id = osTimerNew(led4_timer_callback, osTimerPeriodic, NULL, NULL);
        break;
    default:
        break;
    }
}

void create_all_led_timer()
{
    create_led_timer(LED1);
    create_led_timer(LED2);
    create_led_timer(LED3);
    create_led_timer(LED4);
}

void destory_led_timer(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        if (led1_timer_id != NULL)
        {
            osTimerDelete(led1_timer_id);
            led1_timer_id = NULL;
        }
        break;
    case LED2:
        if (led2_timer_id != NULL)
        {
            osTimerDelete(led2_timer_id);
            led2_timer_id = NULL;
        }
        break;
    case LED3:
        if (led3_timer_id != NULL)
        {
            osTimerDelete(led3_timer_id);
            led3_timer_id = NULL;
        }
        break;
    case LED4:
        if (led4_timer_id != NULL)
        {
            osTimerDelete(led4_timer_id);
            led4_timer_id = NULL;
        }
        break;
    default:
        break;
    }
}

void destory_all_led_timer()
{
    destory_led_timer(LED1);
    destory_led_timer(LED2);
    destory_led_timer(LED3);
    destory_led_timer(LED4);
}
void start_led_timer(LED_TypeDef led, uint32_t blink_time_ms)
{
    switch (led)
    {
    case LED1:
        osTimerStart(led1_timer_id, blink_time_ms);
        break;
    case LED2:
        osTimerStart(led2_timer_id, blink_time_ms);
        break;
    case LED3:
        osTimerStart(led3_timer_id, blink_time_ms);
        break;
    case LED4:
        osTimerStart(led4_timer_id, blink_time_ms);
        break;
    default:
        break;
    }
}

void start_all_led_timer(uint32_t blink_time_ms)
{
    start_led_timer(LED1, blink_time_ms);
    start_led_timer(LED2, blink_time_ms);
    start_led_timer(LED3, blink_time_ms);
    start_led_timer(LED4, blink_time_ms);
}

void stop_led_blink_to_off(LED_TypeDef led)
{

    switch (led)
    {
    case LED1:
        osTimerStop(led1_timer_id);
        LED_Off(LED1);
        break;
    case LED2:
        osTimerStop(led2_timer_id);
        LED_Off(LED2);
        break;
    case LED3:
        osTimerStop(led3_timer_id);
        LED_Off(LED3);
        break;
    case LED4:
        osTimerStop(led4_timer_id);
        LED_Off(LED4);
        break;
    default:
        break;
    }
}

void stop_led_blink_to_on(LED_TypeDef led)
{
    switch (led)
    {
    case LED1:
        osTimerStop(led1_timer_id);
        LED_On(LED1);
        break;
    case LED2:
        osTimerStop(led2_timer_id);
        LED_On(LED2);
        break;
    case LED3:
        osTimerStop(led3_timer_id);
        LED_On(LED3);
        break;
    case LED4:
        osTimerStop(led4_timer_id);
        LED_On(LED4);
        break;
    default:
        break;
    }
}

void stop_all_led_blink_to_on()
{
    stop_led_blink_to_on(LED1);
    stop_led_blink_to_on(LED2);
    stop_led_blink_to_on(LED3);
    stop_led_blink_to_on(LED4);
}

void stop_all_led_blink_to_off()
{
    stop_led_blink_to_off(LED1);
    stop_led_blink_to_off(LED2);
    stop_led_blink_to_off(LED3);
    stop_led_blink_to_off(LED4);
}

void change_led_blink_timer(LED_TypeDef led, uint32_t blink_time_ms)
{
    switch (led)
    {
    case LED1:
        osTimerStart(led1_timer_id, blink_time_ms);
        break;
    case LED2:
        osTimerStart(led2_timer_id, blink_time_ms);
        break;
    case LED3:
        osTimerStart(led3_timer_id, blink_time_ms);
        break;
    case LED4:
        osTimerStart(led4_timer_id, blink_time_ms);
        break;

    default:
        break;
    }
}

void create_led_flow_timer()
{
    if (led_flow_timer_id == NULL)
    {
        led_flow_timer_id = osTimerNew(led_flow_timer_callback, osTimerOnce, NULL, NULL);
    }
}

void destory_led_flow_timer()
{
    if (led_flow_timer_id != NULL)
    {
        osTimerDelete(led_flow_timer_id);
        led_flow_timer_id = NULL;
    }
}

void start_led_flow_timer(uint32_t flow_time_ms)
{
    osTimerStart(led_flow_timer_id, flow_time_ms);
}
void stop_led_flow_timer()
{
    osTimerStop(led_flow_timer_id);
    LED_All_Off();
}

void LED_flow_on_front(uint32_t flow_time_ms)
{
    g_led_flow_direction = 0;
    start_led_flow_timer(flow_time_ms);
}

void LED_flow_on_back(uint32_t flow_time_ms)
{
    g_led_flow_direction = 1;
    start_led_flow_timer(flow_time_ms);
}

void Comp_OLED_Job_Init()
{
    create_all_led_timer();
    create_led_flow_timer();
}

void Comp_OLED_Job_Deinit(void)
{
    destory_all_led_timer();
    destory_led_flow_timer();
}
