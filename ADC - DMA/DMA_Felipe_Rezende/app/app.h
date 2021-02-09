/*
 * app.h
 *
 *  Created on: Dec 10, 2020
 *      Author: Felipe
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_set_adc_finished(void);
void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2);


#endif /* APP_H_ */
