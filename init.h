#include "stm32f407xx.h"
#include "GPIO.h"
#include "ADC.h"
#include "DAC.h"
#include "TIMERS.h"
#include "delay.h"
#include "USART.h"

extern short adc_data[2];
void init(void);
void read_adc(void);
void set_PB0_PWM_mode(unsigned int Fsw);
void set_PWM_duty(float d);