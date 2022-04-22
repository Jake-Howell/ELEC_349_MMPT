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

int main(void)
{
	
	
	PLL_Config_HSE();
	init();	//run basic init - DO NOT REMOVE
	set_PB0_PWM_mode(100000); //set PWM to 100KHz frequency
	float sampleSumP;
	float sampleSumV;
	float sampleSumC;
	
	
	PandO.sweep_duty();	//sweep and locate max power point
	//PandO.set_duty(PandO.get_peak_duty());
	//PandO.set_threshold(0.8); //reset MPP if current power is below 80% of peak power
	
	
	int OS_Num = 10; //set over sampling rate to 10x
	while(delay_nms(100))
	{
		
		for (int i = 0; i<OS_Num; i++){
			sampleSumP += PandO.read_adc();
			//sampleSumV += PandO.getVoltage();
			//sampleSumC += PandO.getCurrent(); //PandO does not use current!
			delay_nms(1);
		}
		PandO.set_OS_AVG_PWR(sampleSumP/OS_Num);
		//PandO.set_OS_AVG_VOL(sampleSumV/OS_Num);
		PandO.evaluate();
		//ICon.evaluate();

	/*
	ICon.sweep_duty();	//sweep and locate max power point
	//PandO.set_duty(PandO.get_peak_duty());
	//PandO.set_threshold(0.8); //reset MPP if current power is below 80% of peak power
	int OS_Num = 10; //set over sampling rate to 10x
	while(delay_nms(100))
	{
		
		for (int i = 0; i<OS_Num; i++){
			ICon.read_adc();
			sampleSumV = ICon.getVoltage();
			sampleSumC = ICon.getCurrent();
			delay_nms(1);
		}
		ICon.set_OS_AVG_VOL(sampleSumV/OS_Num);
		ICon.set_OS_AVG_CUR(sampleSumC/OS_Num);
		ICon.evaluate();
		
		
				
	*/
	}//end loop
	
}//end main

void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;				//clear interrupt flag in status register
	//Place ADC read here
	
}



#ifdef __cplusplus
}
#endif
