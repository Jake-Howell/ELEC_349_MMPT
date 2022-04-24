#include "init.h"
void init(void)
{
	config_GPIOA();
	config_GPIOB();
	config_GPIOD();
	
	config_ADC1();
	config_DAC();
	SysTick_Init();
	
}



//void set_PWM_duty(float d)
//{
//	if(d>1.0f) d=1.0f;
//	T3CCR3=(unsigned short)(d*(float)PR3);
//}
