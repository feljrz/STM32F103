/*
 * app.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "app.h"
#include <stdint.h>
#include "hw.h"
#define APP_DEBOUNCING_TIME_MS 100

_Bool app_started = 0;
_Bool esteira = 0;

volatile uint32_t led_time_ms = 100;
//Controlando a inicialização

void app_switch_interrupt(void){

	static uint32_t debouncing_time_ms = 0;

	if(!app_started)
			return;
	//Se a diferença de tempo entre o tempo de "repique" for maior que o debouncing entra
	if((hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
	{
		esteira = 1;
		hw_input_capture_init();

	debouncing_time_ms = hw_tick_ms_get();
}
}


void app_tick_1ms(void){


}

void app_init(void){
	app_started = 1;
	hw_input_capture_init();
	esteira = 1; // Variável que representa o estado da esteira
}

void app_loop(void){
	uint16_t cnt = hw_input_capture_get();
	// Contador define o numero de objetos que já passou pelo sensor, caso atinga um determinado limite a esteira
	if (cnt > 200){
		hw_input_capture_stop();
		esteira = 0;
		// Indica que a esteira está ligada
		for(uint8_t i; i< 10; i++){
			hw_led_toggle();
			hw_delay(200);
		}
	}



	// hw_cpu_sleep();
}

