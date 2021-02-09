/*
 * hw.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "main.h"
#include <stdbool.h>
#include "app.h"

extern TIM_HandleTypeDef htim1;

uint32_t hw_tick_ms_get(void){
	return HAL_GetTick();
}

//Wait for interrupt, entra em modo de economia de energia até que uma interrupção seja chamada
void hw_cpu_sleep(void){
	__WFI();
}


//Função que será sobrescrita
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == GPIO_PIN_0){
		app_switch_interrupt();
	}

}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);

}

_Bool hw_switch_state_get(void){
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin);

	return switch_state == GPIO_PIN_SET ? true : false;

}

void hw_led_state_set(_Bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);

}

void hw_delay(uint32_t time_ms){
	HAL_Delay(time_ms);

}

void hw_input_capture_init(void){
	HAL_TIM_Base_Start(&htim1);
	hw_input_capture_set(0);
}

void hw_input_capture_stop(void){
	HAL_TIM_Base_Stop(&htim1);
}

uint16_t hw_input_capture_get(void){
	return __HAL_TIM_GET_COUNTER(&htim1);
}

void hw_input_capture_set(uint16_t cnt){
	__HAL_TIM_SET_COUNTER(&htim1, cnt);
}

