#include "PLL_Config.h"
#include "main.h"

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

int main(void)
{
	PLL_Config_HSE();
	init();	//run basic init - DO NOT REMOVE
	green_led_on();	
	
//ANY OTHER INIT CODE GOES HERE
//-----------------------------
	unsigned short power = 0;
	unsigned short power_prev = 0;
	unsigned short duty = 0;
	set_PB0_PWM_mode(1000000); //set PWM to 1MHz frequency
	
	
	
//-----------------------------
	while(1)
	{
		
	//MAIN LOOP CODE GOES HERE
	//------------------------
		read_adc();
		power = 6.06*PA1_DATA * PA2_DATA; //PA1 (voltage) * PA2(current)
		
		if(power > power_prev){
			//if current power if greater than previous power
			duty += 1;
			green_led_on();
			orange_led_off();
			red_led_off();
			
		}else if(power < power_prev){
			//if current power if less than previous power
			duty -= 1;
			green_led_off();
			orange_led_off();
			red_led_on();
			
		}else{
			//if power hasn't changed, do nothing
			green_led_off();
			orange_led_on();
			red_led_off();
		}
		
		//adding max and min boundries
		if(duty > MAX_DUTY){
			duty = MAX_DUTY;
		}
		if(duty < MIN_DUTY){
			duty = MIN_DUTY;
		}
		
		set_PWM_duty(duty);
		power_prev = power; //after change, store power in previous power
		
		
		
		
		//example code - THIS CAN BE DELETED
		orange_led_on();	//turn on the orange led
		delay_nms(100);		//delay 100ms
		orange_led_off();	//turn off the orange led
		delay_nms(200);		//delay 50ms

	

		
		

	//------------------------
	}//end loop
}//end main

