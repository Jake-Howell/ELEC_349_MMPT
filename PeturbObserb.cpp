#include "PeturbObserb.h"
#include "main.h"

PeturbObserb::PeturbObserb(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.05f;
	this->DUTY_STEP[UP] 	= 0.01f;
	this->DUTY_STEP[DOWN] = 0.01f;
}
void PeturbObserb::evaluate(){

	this->read_adc();
	this->delta_p = OS_AVG_PWR - power[PREVIOUS]; //calculate power differance
	
	if (delta_p > 0.0f){													//if power has increased
		green_led_on();
		red_led_off();
		next_duty = duty[NOW] + DUTY_STEP[UP];			//increase duty
		
	}else if(delta_p == 0){__NOP();}
	else{																	//if power has decreased
		red_led_on();
		green_led_off();

		next_duty = duty[NOW] - DUTY_STEP[DOWN];// decrease duty 
	}
	green_led_off();
	red_led_off();
	orange_led_off();
	blue_led_off();
	
	duty[PREVIOUS] = duty[NOW];
	power[PREVIOUS] = OS_AVG_PWR;
//	if (powerGood() == false){
//		set_duty(MAX_POWER_DUTY);	//if power isnt good, set duty to value used while hitting max power
//	}else{
//		set_duty(next_duty);
//	}
	set_duty(next_duty);
}

bool PeturbObserb::powerGood(){
	if (avg_power > MAX_POWER*threshold){
		return true;	//if within threshold, return true
	}
	
	return false;
}