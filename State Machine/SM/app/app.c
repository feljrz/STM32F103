/*
 * app.c
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#include "app.h"
#include <stdint.h>
#include <string.h>
#include "hw.h"
#define APP_DEBOUNCING_TIME_MS 100

_Bool app_started = 0;

volatile uint32_t led_time_ms = 100;
volatile uint32_t led_time_ms2 = 450;

#define NUM_DIGITS 4
#define PASSWORD "ABCD"
static uint32_t time_spend;


typedef enum sm_state_e {
	SM_RESET = 0,
	SM_WAIT_DIGITS,
	SM_CHECK_CODE
}sm_state_t;

typedef struct sm_state_var_s{
	uint8_t pos;
	sm_state_t state;
	uint32_t tmr_out;
	char code[NUM_DIGITS];
}sm_state_var_t;

sm_state_var_t sm;

sm_state_t sm_reset_state(sm_state_var_t *st)
{
	sm_state_t next_state = SM_WAIT_DIGITS;

	st->pos = 0;

	return next_state;
}

sm_state_t sm_wait_digits_state(sm_state_var_t *st)
{
	sm_state_t next_state = st->state = SM_WAIT_DIGITS;

	char *c = hw_getBuffer();

		while(*c != '\0'){
			if(*c != 'F'){
				// Incremento o ponteiro passando-o para a struct
				st->code[st->pos] = (uint16_t) *(c);
				st->pos++;

			}
			else{
				next_state = SM_RESET;
			}
			c++;
		}

	if(time_spend >= 5000 && hw_getBufferPos() !=0){
		hw_buffer_clear();
		time_spend = 0;
		hw_led_toggle();
		hw_delay(200);
		hw_led_toggle();
		hw_delay(200);

		next_state = SM_RESET;
	}
	//Trocar pelo um ponteiro
	if(st->pos == 4)
		next_state = SM_CHECK_CODE;

	return next_state;
}


sm_state_t sm_check_code_state(sm_state_var_t *st)
{
	sm_state_t next_state = SM_RESET;

	if(strncmp(st->code,PASSWORD,4) == 0){
		//Senha Correta
		hw_led_state_set(1);
		hw_delay(2000);
		hw_led_state_set(0);
		hw_delay(2000);
	}

	else{
		// Senha Incorreta
		hw_led_state_set(1);
		hw_delay(200);
		hw_led_state_set(0);
		hw_delay(200);
		hw_led_state_set(1);
		hw_delay(200);
		hw_led_state_set(0);
		hw_delay(200);
		hw_led_state_set(1);
		hw_delay(200);
		hw_led_state_set(0);
		hw_delay(200);
	}
	hw_buffer_clear();
	return next_state;
}

void sm_func(sm_state_var_t *st)
{
	switch(st->state)
	{
	case SM_RESET:
		st->state = sm_reset_state(st);
		break;
	case SM_WAIT_DIGITS:
		st->state = sm_wait_digits_state(st);
		break;
	case SM_CHECK_CODE:
		st->state = sm_check_code_state(st);
		break;
	default:
		st->state = SM_RESET;
		break;
	}

}

void app_tick_1ms(void){

	//A aplicação só irá iniciar quando a aplicação partir
	if(!app_started)
		return;

	static uint32_t cnt_ms = 0;
	cnt_ms++;
	if(sm.pos !=0)
		time_spend++;
}


void app_init(void){
	app_started = 1;
	hw_led_state_set(0);
	sm.state = SM_RESET;
}

void app_loop(void){
	hw_cpu_sleep();
	sm_func(&sm);
}
