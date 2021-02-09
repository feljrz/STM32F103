/*
 * app.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "app.h"
#include <stdint.h>
#include "hw.h"
#define APP_DEBOUNCING_TIME_MS 80

_Bool app_started = 0;

volatile uint32_t led_time_ms_on = 950;
volatile uint32_t led_time_ms_off = 450;
_Bool led_state_on = 1;

//Controlando a inicialização
//Original
void app_switch_interrupt(_Bool pin_state0, _Bool pin_state1){

	static uint32_t debouncing_time_ms = 0;

	if(!app_started)
			return;

	//Se a diferença de tempo entre o tempo de "repique" for maior que o debouncing entra
	if((hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
	{
		if(pin_state0 == 0 && pin_state1 == 0){
			led_time_ms_on = 100;
			led_time_ms_off = 100;
		}

		else if(pin_state0 == 0 && pin_state1 == 1){
			led_time_ms_on = 300;
			led_time_ms_off = 150;
		}
		else if(pin_state0 == 1 && pin_state1 == 0){
			led_time_ms_on = 600;
			led_time_ms_off = 300;
		}

		else if (pin_state0 == 1 && pin_state1 == 1){
			led_time_ms_on = 950;
			led_time_ms_off = 450;
		}

	debouncing_time_ms = hw_tick_ms_get();
}
}



void app_tick_1ms(void){
	if(!app_started)
		return;
	static uint32_t led_time_cnt_ms = 0;
	led_time_cnt_ms++;

	if(led_state_on && led_time_cnt_ms >= led_time_ms_on){
		led_state_on = !led_state_on;
		led_time_cnt_ms = 0;
		hw_led_toggle();
	}
	else if (!led_state_on && led_time_cnt_ms >= led_time_ms_off){
		led_state_on = !led_state_on;
		led_time_cnt_ms = 0;
		hw_led_toggle();
	}
}


void app_init(void){
	app_started = 1;
}

void app_loop(void){
	hw_cpu_sleep();
}

