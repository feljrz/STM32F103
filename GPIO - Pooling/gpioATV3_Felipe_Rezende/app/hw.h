/*
 * hw.h
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#ifndef HW_H_
#define HW_H_

_Bool hw_switch_state_get_pin0(void);
_Bool hw_switch_state_get_pin1(void);
void hw_led_state_set(_Bool state);
void hw_delay(uint32_t time_ms);

#endif /* HW_H_ */
