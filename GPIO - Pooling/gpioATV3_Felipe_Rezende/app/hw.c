/*
 * hw.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */


#include "main.h"
#include <stdbool.h>

_Bool hw_switch_state_get_pin0(void){
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW0_GPIO_Port, USER_SW0_Pin);

	return switch_state == GPIO_PIN_SET ? true : false;

}

_Bool hw_switch_state_get_pin1(void){
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW1_GPIO_Port, USER_SW1_Pin);

	return switch_state == GPIO_PIN_SET ? true : false;

}

void hw_led_state_set(_Bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);

}

void hw_delay(uint32_t time_ms){
	HAL_Delay(time_ms);
}

