/*
 * app.h
 *
 *  Created on: Nov 19, 2020
 *      Author: Felipe
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_switch_interrupt(_Bool stop_led);

#endif /* APP_H_ */
