/*
 * app.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */


#include "app.h"
#include <stdint.h>
#include "hw.h"

void app_init(void){

}
void app_loop(void){
	uint32_t led_time_ms = 950;
	uint32_t led_time_ms2 = 450;
	_Bool switch_state_pin1 = hw_switch_state_get_pin0();
	_Bool switch_state_pin0 = hw_switch_state_get_pin1();

	if(switch_state_pin0 == 0 && switch_state_pin1 == 0){
		led_time_ms = 100;
		led_time_ms2 = 100;
	}

	if(switch_state_pin0 == 0 && switch_state_pin1 == 1){
			led_time_ms = 300;
			led_time_ms2 = 150;
	}

	if(switch_state_pin0 == 1 && switch_state_pin1 == 0){
			led_time_ms = 600;
			led_time_ms2 = 300;
	}

	hw_led_state_set(1);
	hw_delay(led_time_ms);
	hw_led_state_set(0);
	hw_delay(led_time_ms2);
}

