#include "PeturbObserb.h"
#include "main.h"

PeturbObserb::PeturbObserb(){
	this->MAX_DUTY = 0.95f;
	this->MIN_DUTY = 0.05f;
	this->DUTY_STEP[UP] 	= 0.004f;
	this->DUTY_STEP[DOWN] = 0.002f;
}
void PeturbObserb::evaluate(){

	updateValues();
	
	
	//this->delta_v = OS_AVG_VOL - voltage[PREVIOUS];
	if (delta_p >= 0.0f){								//if power has increased
			
		if(delta_v >= 0.0f ){                           //if Voltage and power have increased
			next_duty = duty[NOW] - DUTY_STEP[DOWN];    //decrease duty, increase Vref
    }else{                                          //if power has increased but voltage has decreased
			next_duty = duty[NOW] + DUTY_STEP[UP];      //increase duty, decrease Vref
    }
	}else{										            							//if power has decreased
     if (delta_v >= 0.0f){                            //if power has decreased and voltage has increased 
			next_duty = duty[NOW] + DUTY_STEP[UP];          //increase duty, decrease Vref 
     }else{                                            //if power has decreased and voltage has decreased
			next_duty = duty[NOW] - DUTY_STEP[DOWN];        //decrease duty, increase Vref
     }	
	}
	
//	if (powerGood() == false){
//		set_duty(MAX_POWER_DUTY);	//if power isnt good, set duty to value used while hitting max power
//	}else{
//		set_duty(next_duty);
//	}
	set_duty(next_duty);
	delay_nms(30); //delay until buffer is full of new samples

}

bool PeturbObserb::powerGood(){
	if (avg_power > MAX_POWER*threshold){
		return true;	//if within threshold, return true
	}
	
	return false;
}
