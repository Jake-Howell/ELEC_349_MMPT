#include "PeturbObserb.h"

PeturbObserb::PeturbObserb(){
}
void PeturbObserb::evaluate(){
	float next_duty;
	this->read_adc();
	delta_p = power[NOW] - power[PREVIOUS]; //calculate power differance
	delta_d = duty[NOW] - duty[PREVIOUS];		//calculate duty differance
	
	if (delta_p > 0.0f){										//if power has increased
		if(duty[PREVIOUS] > duty[NOW]){				//if duty has decreased
			next_duty = duty[NOW] + delta_d;		//calculate updated duty cycle
		}else{
			next_duty = duty[NOW] - delta_d;		//calculate updated duty cycle
		}
	}else{																	//if power has decreased
		if(duty[PREVIOUS] < duty[NOW]){									//
			next_duty = duty[NOW] - delta_d;
		}else{
			next_duty = duty[NOW] + delta_d;
		}
	}
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(duty[NOW]);
	power[PREVIOUS] = power[NOW];
}

