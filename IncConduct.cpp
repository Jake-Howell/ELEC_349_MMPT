#include "IncConduct.h"


IncConduct::IncConduct(){
	duty[NOW] = 0.1; //default value
}

void IncConduct::evaluate()
{
	
	this->read_adc();
	
	
	
	if(delta_v == 0)
	{
		if(delta_c == 0)
		{
			//return
		}else if(delta_c>0)
		{
				next_duty = duty[NOW] - DUTY_STEP[DOWN]; //increase vref
		}else{ //less than
			next_duty = duty[NOW] + DUTY_STEP[UP]; //decrease vref
		}
	}else 
	{
		if((delta_c/delta_v) == -(current[NOW]/voltage[NOW]))
		{
			//return
		}else if((delta_c/delta_v) > -(current[NOW]/voltage[NOW]))
		{
			next_duty = duty[NOW] - DUTY_STEP[DOWN];
		}else //less than
		{
			next_duty = duty[NOW] + DUTY_STEP[UP];
		}
	}
		
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(next_duty);
	voltage[PREVIOUS] = voltage[NOW];
	current[PREVIOUS] = current[NOW];
}
