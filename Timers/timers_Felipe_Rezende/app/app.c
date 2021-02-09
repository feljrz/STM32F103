/*
 * app.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "app.h"
#include <stdint.h>
#include "hw.h"
#include "main.h"
#define APP_DEBOUNCING_TIME_MS 65

_Bool app_started = 0;

volatile uint32_t led_time_ms = 500;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

//Controlando a inicialização

//void app_switch_interrupt(_Bool stop_led){
//
//	static uint32_t debouncing_time_ms = 0;
//
//	if(!app_started)
//		return;
//	uint32_t tim2_cnt = hw_tim2_ms_get();
//	//Se a diferença de tempo entre o tempo de "repique" for maior que o debouncing entra
//	if((tim2_cnt - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
//	{
//		stop_led = !stop_led;
//		if(stop_led){
//			hw_timer_start(500);
//		}
//		else{
//			hw_timer_start(250);
//		}
////		HAL_TIM_Base_Stop_IT(&htim1);
////		stop_led = !stop_led;
//		debouncing_time_ms = hw_tim2_ms_get();
//}
//	return stop_led;
//}


void app_tick_1ms(void){


}

void app_init(void){
	hw_timer_start();

	app_started = 1;
}

void app_loop(void){
	hw_cpu_sleep();
}

