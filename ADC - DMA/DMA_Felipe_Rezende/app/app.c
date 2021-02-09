/*
 * app.c
 *
 *  Created on: Dec 10, 2020
 *      Author: Felipe
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "hw.h"


extern float led_time_ms;
#define ADC_SAMPLES_N 10
#define ADC_CHANNEL_N 2
bool app_started = false;
volatile bool adc_finished = false;
uint16_t adc_raw_data[ADC_SAMPLES_N] = {0};

void app_set_adc_finished(void)
{
	adc_finished = true;
	hw_adc_stop();
}

void app_average_adc_value(uint16_t *adc_raw_val, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2)
{
	uint16_t cnt = 0;
	uint32_t sum_temp[ADC_CHANNEL_N] = {0,0};

	while(cnt< ADC_SAMPLES_N)
	{
		for(uint8_t i=0; i<ADC_CHANNEL_N;i++)
			sum_temp[i] = sum_temp[i] + adc_raw_val[cnt+i];
		cnt+=ADC_CHANNEL_N;
	}
	for(uint8_t i=0; i< ADC_CHANNEL_N;i++)
		sum_temp[i] = sum_temp[i] / (ADC_SAMPLES_N/ADC_CHANNEL_N);

	*adc_avg_ch1 = (uint16_t) sum_temp[0];
	*adc_avg_ch2 = (uint16_t) sum_temp[1];

}



void app_init(void)
{
	app_started = true;
	hw_adc_calibration();
}

void app_loop(void)
{
	uint16_t adc_avg_val_1,adc_avg_val_2;
	hw_adc_start(adc_raw_data, ADC_SAMPLES_N);
	hw_cpu_sleep();
	if(adc_finished == true)
		{
			adc_finished = false;
			app_average_adc_value(adc_raw_data, &adc_avg_val_1, &adc_avg_val_2);
			change_led_blink(adc_avg_val_1,adc_avg_val_2);
		}
	//hw_delay_ms(100);
}

