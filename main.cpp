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
	
	PandO.sweep_duty();	//sweep and locate max power point
	PandO.set_duty(PandO.get_peak_duty());
	//PandO.set_threshold(0.8); //reset MPP if current power is below 80% of peak power
	float sampleSum;
	int OS_Num = 10; //set over sampling rate to 10x
	while(delay_nms(100))
	{
		
		for (int i = 0; i<OS_Num; i++){
			sampleSum += PandO.read_adc();
			delay_nms(10);
		}
		PandO.set_OS_AVG_PWR(sampleSum/OS_Num);
		PandO.evaluate();
		//ICon.evaluate();
		
				

	}//end loop
}//end main



#ifdef __cplusplus
}
#endif
