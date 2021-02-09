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
void hw_input_capture_init(void);
uint16_t hw_input_capture_get(void);
void hw_input_capture_set(uint16_t cnt);
void hw_input_capture_stop(void);



#endif /* HW_H_ */
