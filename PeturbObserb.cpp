#include "PeturbObserb.h"
#include "main.h"

PeturbObserb::PeturbObserb(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.2f;
	this->DUTY_STEP[UP] 	= 0.005f;
	this->DUTY_STEP[DOWN] = 0.005f;

}
void PeturbObserb::evaluate(){

	this->read_adc();
	this->delta_p = power[NOW] - power[PREVIOUS]; //calculate power differance
	this->delta_d = duty[NOW] - duty[PREVIOUS];		//calculate duty differance
	
	if (delta_p > 0.0f){										//if power has increased
		green_led_on();
		red_led_off();

		next_duty = duty[NOW] + DUTY_STEP[UP];
	}else{																	//if power has decreased
		red_led_on();
		green_led_off();

		next_duty = duty[NOW] - DUTY_STEP[DOWN];
	}
	green_led_off();
	red_led_off();
	orange_led_off();
	blue_led_off();
	
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(next_duty);
	//set_duty(0.5);
	power[PREVIOUS] = power[NOW];
}

