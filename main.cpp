#ifdef __cplusplus
extern "C" {
#endif

#include "PLL_Config.h"
#include "main.h"
#include "init.h"
#include "delay.h"
#include "USART.h"
#include "PeturbObserb.h"


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//ELEC 344 EXAMPLE CODE FOR MPPT
//BY STUART MACVEIGH		22/03/2016
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//REMEMBER TO TO KEEP ALL FILES TOGETHER, WHEN TRANSPORTING FILES BETWEEN PCs KEEP THEM ALL IN THE FOLDER!!


//CALL THE "read_adc()" FUNCTION TO READ ANALOGUE VALUES FROM PA1 AND PA2
//PA1 VALUE IS STORED IN "PA1_DATA" VARIABLE AND PA2 VALUE IS STORED IN "PA2_DATA" VARIABLE.

//THE SWITCH SIGNAL IS OUTPUT FROM PB0
//PB0 CAN BE OPERATED IN 2 MODES, DIRECT CONTROL MODE, OR PWM MODE.
//BY DEFAULT PB0 OPERATES IN DIRECT CONTROL MODE, TO CHANGE IT TO PWM MODE CALL THE "set_PB0_PWM_mode(<FREQ>)" FUNCTION IN THE INIT STAGE WHERE <FREQ> IS THE PWM FREQUENCY.
//WHEN OPERATING IN DIRECT CONTROL MODE CALL THE "set_PB0()" FUNCTION TO SEND PB0 HIGH AND THE "clr_PB0()" FUNCTION TO SEND PB0 LOW.
//WHEN OPERATING IN PWM MODE CALL THE "set_PWM_duty(<D>)" FUNCTION TO SET THE DUTY CYCLE WHERE <D> IS THE DESIRED DUTY CYCLE IN PERCENT FROM 0 TO 100

//TO CONTROL THE ON-BOARD LEDS CALL THE FOLLOWING
//"<colour>_led_on()" TO TURN ON THE LED
//"<colour>_led_off()" TO TURN OFF THE LED
//	<colour> IS THE COLOUR OF LED TO CONTROL (green,orange,red,blue), AN EXAMPLE IS PROVIDED IN THE MAIN CODE.

//DELAYS
//CALL THE "delay_nus(<val>)" TO GENERATE AN ACCURATE MICROSECONDS DELAY, <val> IS THE NUMBER OF MICROSECONDS TO DELAY
//CALL THE "delay_nms(<val>)" TO GENERATE AN ACCURATE MILLISECONDS DELAY, <val> IS THE NUMBER OF MILLISECONDS TO DELAY
PeturbObserb PandO();
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
