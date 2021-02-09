/*
 * hw.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "main.h"
#include <stdbool.h>
#include "app.h"

_Bool pin_state0 = 1;
_Bool pin_state1 = 1;

uint32_t hw_tick_ms_get(void){
	return HAL_GetTick();
}

//Wait for interrupt, entra em modo de economia de energia até que uma interrupção seja chamada
void hw_cpu_sleep(void){
	__WFI();
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == GPIO_PIN_0){
		pin_state0 = !pin_state0;
	}
	if(GPIO_Pin == GPIO_PIN_1){
		pin_state1 = !pin_state1;
	}
	app_switch_interrupt(pin_state0, pin_state1);
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);
}



void hw_led_state_set(_Bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);

}

void hw_delay(uint32_t time_ms){
	HAL_Delay(time_ms);

}
