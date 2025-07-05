#ifndef __JOB__H_
#define __JOB__H_

#include "MyTasks.h"
#include "Int_LED.h"
#include "Comp_OLED_Job.h"

void create_led_timer(LED_TypeDef led);

void create_all_led_timer(void);

void destory_led_timer(LED_TypeDef led);

void destory_all_led_timer(void);

void start_led_timer(LED_TypeDef led, uint32_t blink_time_ms);

void start_all_led_timer(uint32_t blink_time_ms);

void stop_led_blink_to_off(LED_TypeDef led);

void stop_led_blink_to_on(LED_TypeDef led);

void stop_all_led_blink_to_on(void);

void stop_all_led_blink_to_off(void);

void change_led_blink_timer(LED_TypeDef led, uint32_t blink_time_ms);

void create_led_flow_timer(void);

void destory_led_flow_timer(void);

void start_led_flow_timer(uint32_t flow_time_ms);

void stop_led_flow_timer(void);

void LED_flow_on_front(uint32_t flow_time_ms);

void LED_flow_on_back(uint32_t flow_time_ms);

void Comp_OLED_Job_Init(void);

void Comp_OLED_Job_Deinit(void);

#endif
