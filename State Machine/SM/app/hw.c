/*
 * hw.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "main.h"
#include <stdbool.h>
#include "app.h"

static char buffer[] = {'F', 'F', 'F', 'F'};

#define APP_DEBOUNCING_TIME_MS 100

static uint32_t bf_pos;




char * hw_getBuffer(){
	return buffer;
}

void hw_setBuffer(char var, uint16_t pos){
	buffer[pos] = var;
	hw_delay(65);
}


uint32_t hw_tick_ms_get(void){
	return HAL_GetTick();
}

//Wait for interrupt, entra em modo de economia de energia até que uma interrupção seja chamada
void hw_cpu_sleep(void){
	__WFI();
}

void hw_buffer_clear(void){
	for(int pos = 0; pos <= 3; pos++){
				hw_setBuffer('F', pos);
			}
}

uint32_t hw_getBufferPos(){
	return bf_pos;
}

void hw_setBufferPos(uint32_t pos){
	bf_pos = pos;
}



//Função que será sobrescrita
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint16_t pos = 0;
	static uint32_t debouncing_time_ms = 0;
	uint32_t db_time = hw_tick_ms_get();
	if( (hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS){

		if(pos <= 3)
		{
			if(GPIO_Pin == GPIO_PIN_0)
				hw_setBuffer('A', pos);

			else if(GPIO_Pin == GPIO_PIN_1)
				hw_setBuffer('B', pos);

			else if(GPIO_Pin == GPIO_PIN_2)
				hw_setBuffer('C', pos);

			else if(GPIO_Pin == GPIO_PIN_3)
				hw_setBuffer('D', pos);
			pos++;

		}
		else
			pos = 0;

		hw_setBufferPos(pos);



	debouncing_time_ms = hw_tick_ms_get();
	}
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);

}

_Bool hw_switch_state_get(void){
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_LED_GPIO_Port, USER_LED_Pin);

	return switch_state == GPIO_PIN_SET ? true : false;

}

void hw_led_state_set(_Bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);

}

void hw_delay(uint32_t time_ms){
	HAL_Delay(time_ms);
}
