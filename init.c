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

void set_PB0_PWM_mode(unsigned int Fsw)
{
	GPIO_setmode(GPIOB,0,2);	//PB0 alternate function
	config_TIM3();
	PSC3=0;
	TMR3=0;
	PR3=(unsigned short)(SystemCoreClock/(2*Fsw));
	T3CCR3=(unsigned short)(PR3/10);
	start_timer3();
}

//void set_PWM_duty(float d)
//{
//	if(d>1.0f) d=1.0f;
//	T3CCR3=(unsigned short)(d*(float)PR3);
//}
