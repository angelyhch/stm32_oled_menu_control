#ifndef __JOB__H_
#define __JOB__H_

#include "MyTasks.h"
#include "Int_LED.h"
#include "Comp_OLED_Job.h"

void Comp_OLED_Job_Init(void);
void Comp_OLED_Job_Deinit(void);

void create_all_led_timer(void);
void destory_all_led_timer(void);

void start_led_timer(LED_TypeDef led, uint32_t blink_time_ms);
void start_all_led_timer(uint32_t blink_time_ms);

void change_led_blink_timer(LED_TypeDef led, uint32_t blink_time_ms);
void stop_led_blink_to_off(LED_TypeDef led);
void stop_led_blink_to_on(LED_TypeDef led);

#endif // !__JOB__H_
