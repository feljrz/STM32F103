/*
 * hw.h
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#ifndef HW_H_
#define HW_H_

_Bool hw_switch_state_get(void);
void hw_led_state_set(_Bool state);
void hw_delay(uint32_t time_ms);
void hw_led_toggle(void);
void hw_cpu_sleep(void);
uint32_t hw_tick_ms_get(void);
void hw_timer_start();
void hw_timer2_start();

void hw_enable_interrupts(void);
void hw_disable_interrupts(void);
uint32_t hw_tim2_ms_get();
//void hw_stop_tim(TIM_HandleTypeDef *htim);




#endif /* HW_H_ */
