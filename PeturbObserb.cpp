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
	//this->delta_v = OS_AVG_VOL - voltage[PREVIOUS];
	if (delta_p >= 0.0f){								//if power has increased
			
		if(delta_v >= 0.0f ){                           //if Voltage and power have increased
			next_duty = duty[NOW] - DUTY_STEP[DOWN];    //decrease duty (something ... load resistance)
    }else{                                          //if power has increased but voltage has decreased
			next_duty = duty[NOW] + DUTY_STEP[UP];      //increase duty
    }
	}else{										            //if power has decreased
     if (delta_v >= 0.0f){                               //if power has decreased and voltage has increased 
			next_duty = duty[NOW] + DUTY_STEP[UP];          //increase duty 
     }else{                                              //if power has decreased and voltage has decreased
			next_duty = duty[NOW] - DUTY_STEP[DOWN];        //decrease duty ()
     }	
	}
	
	
	duty[PREVIOUS] = duty[NOW];
	power[PREVIOUS] = OS_AVG_PWR;
//	if (powerGood() == false){
//		set_duty(MAX_POWER_DUTY);	//if power isnt good, set duty to value used while hitting max power
//	}else{
//		set_duty(next_duty);
//	}
	set_duty(next_duty);
	voltage[PREVIOUS] = voltage[NOW];

}

bool PeturbObserb::powerGood(){
	if (avg_power > MAX_POWER*threshold){
		return true;	//if within threshold, return true
	}
	
	return false;
}