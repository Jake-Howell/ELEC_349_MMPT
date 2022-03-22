#ifdef __cplusplus
extern "C" {
#endif

#include "PLL_Config.h"
#include "main.h"
#include "init.h"
#include "delay.h"
#include "PeturbObserb.h"


PeturbObserb PandO;
int main(void)
{
	PLL_Config_HSE();
	init();	//run basic init - DO NOT REMOVE
	set_PB0_PWM_mode(10000); //set PWM to 10KHz frequency

	while(1)
	{
		PandO.evaluate();
				

	}//end loop
}//end main
#ifdef __cplusplus
}
#endif
