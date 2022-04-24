#ifdef __cplusplus
extern "C" {
#endif

#include "PLL_Config.h"
#include "main.h"
#include "init.h"
#include "delay.h"
#include "PeturbObserb.h"
#include "IncConduct.h"
bool kontinue = true;
void set_duty(float d);
PeturbObserb PandO;
IncConduct ICon;


void TIM2_INIT(int frq);
void TIM2_IRQHandler(void);

	
int main(void)
{
	
	
	PLL_Config_HSE();
	init();	//run basic init - DO NOT REMOVE
	TIM2_INIT(250000);	//set sample frequency to 250KHz
	PandO.set_PB0_PWM_mode(120000); //set PWM to 100KHz frequency

	
	//PandO.sweep_duty();	//sweep and locate max power point
	PandO.set_sampleRate(250000);
	PandO.set_duty(0.5);
	//PandO.set_duty(PandO.get_peak_duty());
	//PandO.set_threshold(0.8); //reset MPP if current power is below 80% of peak power
	
	
	while(1)
	{
		
		PandO.evaluate();

		//ICon.evaluate();
	}//end loop
}//end main

void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;				//clear interrupt flag in status register
	PandO.read_adc();
	//ICon.read_adc();
}

//WARNING Frq shoudnt exceed 1MHz
void TIM2_INIT(int frq){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	//ENABLE tim2 to run on APB1 (Advanced Perphieral Bus 1's 
	volatile int psc, arr;
	const int scalar = 12000000;
	//SCC = 168 000 000
	psc = ((SystemCoreClock/2)/scalar); //calculate PSC to get 1/24th us ticks
	arr = (scalar/frq);				//work out how many nano seconds for given freq
	
	
	TIM2->DIER |= TIM_DIER_UIE; //interrupt enable
	TIM2->PSC = psc - 1;				//psc
	TIM2->ARR = arr - 1;				//arr
	TIM2->CNT = 0;							//cnt
	NVIC_EnableIRQ(TIM2_IRQn);	//set interrupt
	NVIC_SetVector(TIM2_IRQn, (uint32_t)&TIM2_IRQHandler);
	TIM2->CR1|= TIM_CR1_CEN;		//enable timer
}


#ifdef __cplusplus
}
#endif
