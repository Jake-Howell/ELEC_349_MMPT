#include <stm32f4xx.h>
#include "TIMERS.h"
#include "ADC.h"
#include "DAC.h"
//#include "USART.h"
#include "GPIO.h"
#include <math.h>


#define PA1_DATA	adc_data[0]
#define PA2_DATA	adc_data[1]


#define set_PB0() 				GPIO_setpin(GPIOB,0)
#define clr_PB0()					GPIO_clrpin(GPIOB,0)

#define green_led_on()		GPIO_setpin(GPIOD,12)
#define green_led_off()		GPIO_clrpin(GPIOD,12)

#define orange_led_on()		GPIO_setpin(GPIOD,13)
#define orange_led_off()	GPIO_clrpin(GPIOD,13)

#define red_led_on()			GPIO_setpin(GPIOD,14)
#define red_led_off()			GPIO_clrpin(GPIOD,14)

#define blue_led_on()			GPIO_setpin(GPIOD,15)
#define blue_led_off()		GPIO_clrpin(GPIOD,15)

#define MAX_DUTY 100
#define MIN_DUTY 0


unsigned short adc_data[2]={0};
#include "delay.c"
#include "init.c"
