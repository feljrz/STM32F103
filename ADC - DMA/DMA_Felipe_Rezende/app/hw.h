/*
 * hw.h
 *
 *  Created on: Dec 10, 2020
 *      Author: felipe
 */

#ifndef HW_H_
#define HW_H_

#define ADC_MAX_DIGITAL_VAL 4095 //2^12 - 1
#define ADC_MAX_VOLTAGE_SCALE_INT 33000// 3.3^10^4 scale factor
#define ADC_MAX_VOLTAGE_SCALE_FLOAT 3.3 //3.3


void hw_adc_start(uint16_t *values, uint32_t size);
void hw_adc_stop(void);
void hw_adc_calibration(void);
void hw_delay_ms(uint32_t time_ms);
void hw_led_toggle(void);
void change_led_blink(uint16_t adc1_val,uint16_t adc2_val);
void hw_cpu_sleep(void);

#endif /* HW_H_ */
