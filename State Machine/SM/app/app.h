/*
 * app.h
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#ifndef APP_H_
#define APP_H_

typedef struct sm_state_var_s sm_state_var_t;
typedef enum sm_state_e sm_state_t;

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_switch_interrupt(void);
void sm_func(sm_state_var_t *st);



sm_state_t sm_wait_digits_state(sm_state_var_t *st);
sm_state_t sm_reset_state(sm_state_var_t *st);
sm_state_t sm_check_code_state(sm_state_var_t *st);

#endif /* APP_H_ */
