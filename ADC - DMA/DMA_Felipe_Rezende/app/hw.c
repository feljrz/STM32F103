/*
 * hw.c
 *
 *  Created on: Dec 10, 2020
 *      Author: Felipe
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;
extern DMA_HandleTypeDef hdma_adc1;
volatile float led_time_ms = 200;

void hw_adc_start(uint16_t *values, uint32_t size)
{
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)values,size);
}
void hw_adc_stop(void)
{
	HAL_TIM_Base_Stop(&htim3);
	HAL_ADC_Stop_DMA(&hadc1);
}
void hw_adc_calibration(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	__HAL_DMA_DISABLE_IT(&hdma_adc1,DMA_IT_HT);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	app_set_adc_finished();

}

void hw_delay_ms(uint32_t time_ms)
{
	HAL_Delay(time_ms);
}

void hw_led_toggle(void)
{
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}


void change_led_blink(uint16_t adc1_val,uint16_t adc2_val)
{
	float adc_avg = 0;
	adc_avg = (adc1_val + adc2_val)/2;
	led_time_ms = (0.097)*adc_avg + 200; // (600-200)/4095 + 200
	hw_led_toggle();
	hw_delay_ms(led_time_ms);
	hw_led_toggle();
	hw_delay_ms(led_time_ms);
}


void hw_cpu_sleep(void)
{
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON,PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}

