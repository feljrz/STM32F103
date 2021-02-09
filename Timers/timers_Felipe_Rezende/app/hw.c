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
extern TIM_HandleTypeDef htim2;
#define APP_DEBOUNCING_TIME_MS 60

_Bool change_led = 0;
uint32_t pos;
extern uint32_t led_time;

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);

}

void hw_led_state_set(_Bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_state);

}


uint32_t hw_tick_ms_get(void){
	return HAL_GetTick();
}

int hw_tim2_ms_get(){
	return __HAL_TIM_GET_COUNTER(&htim2);
}

//Wait for interrupt, entra em modo de economia de energia até que uma interrupção seja chamada
void hw_cpu_sleep(void){
	__WFI();
}

_Bool hw_switch_state_get(void){
	GPIO_PinState switch_state = HAL_GPIO_ReadPin(USER_SW_GPIO_Port, USER_SW_Pin);

	return switch_state == GPIO_PIN_SET ? true : false;

}


void hw_delay(uint32_t time_ms){
	HAL_Delay(time_ms);

}

void hw_disable_interrupts(void)
{
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}

void hw_enable_interrupts(void)
{
	HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
}

void hw_timer_start(){

	hw_led_state_set(0);
	__HAL_TIM_SET_COUNTER(&htim1, 0); // Começa a contagem em 0
	HAL_TIM_Base_Start_IT(&htim1); //Ligo a contagem com interrupção
}

void hw_timer2_start(){

	__HAL_TIM_SET_COUNTER(&htim2, 0); // Começa a contagem em 0
	HAL_TIM_Base_Start_IT(&htim2); //Ligo a contagem com interrupção
}

void hw_stop_tim(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Stop_IT(&htim);
}


// Por problemas no ao realizar a ativação com LED tambem adotei uma estratégia com um contador
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	hw_timer2_start();
	uint32_t tim2_cnt =  __HAL_TIM_GET_COUNTER(&htim2);
	static uint32_t cnt_it_in = 0;
	static uint32_t cnt_it_out = 0;
	static uint32_t debouncing_time_ms = 0;
	cnt_it_out++;
	if((hw_tim2_ms_get()- debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
	{
		if(GPIO_Pin == GPIO_PIN_0 && cnt_it_out <= 1){
			change_led = !change_led;
			if(change_led)
				HAL_TIM_Base_Stop_IT(&htim1);

			}
		else{
			cnt_it_out = 0;
			return;
		}
		}
		debouncing_time_ms = __HAL_TIM_GET_COUNTER(&htim2);
	}



//Função fraca que é chamada ao termino da interrupção de contagem
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t cnt = 0;

	if(htim == &htim1 && !change_led){
		hw_led_toggle();
	}

	if(htim == &htim2 ){
		hw_led_toggle();
		if(++cnt >= 7 && change_led ){ //Tempo para visualizar mudança
			HAL_TIM_Base_Stop_IT(&htim2);
			change_led = !change_led;
			hw_timer_start();
		}
	}
}





