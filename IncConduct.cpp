#include "IncConduct.h"


IncConduct::IncConduct(){
	this->MAX_DUTY = 0.95f;
	this->MIN_DUTY = 0.05f;
	this->DUTY_STEP[UP] 	= 0.005f;
	this->DUTY_STEP[DOWN] = 0.005f;
}

void IncConduct::evaluate()
{
	
	updateValues();
	
	
	
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
		
	
	set_duty(next_duty);
	delay_nms(10);
	
}
