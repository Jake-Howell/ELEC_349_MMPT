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

	while(delay_nms(1))
	{

		PandO.evaluate();
		//ICon.evaluate();
				

	}//end loop
}//end main



#ifdef __cplusplus
}
#endif
