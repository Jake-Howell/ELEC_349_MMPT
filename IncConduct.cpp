#include "IncConduct.h"


IncConduct::IncConduct(){
	duty[NOW] = 0.1; //default value
}

void IncConduct::evaluate()
{
	
	this->read_adc();
	
	V[NOW] = this->voltage;
	I[NOW] = this->current;
	
	deltaV = V[NOW] - V[PREVIOUS];
	deltaI = I[NOW] - I[PREVIOUS];
	
	if(deltaV == 0)
	{
		if(deltaI == 0)
		{
			//return
		}else if(deltaI>0)
		{
				next_duty = duty[NOW] + DUTY_STEP[UP];
		}else{ //less than
			next_duty = duty[NOW] - DUTY_STEP[DOWN];
		}
	}else 
	{
		if( (deltaI/deltaV) == -(I[NOW]/V[NOW]))
		{
			//return
		}else if((deltaI/deltaV) > -(I[NOW]/V[NOW]))
		{
			next_duty = duty[NOW] + DUTY_STEP[UP];
		}else //less than
		{
			next_duty = duty[NOW] - DUTY_STEP[DOWN];
		}
	}
		
	duty[PREVIOUS] = duty[NOW];
	duty[NOW] = next_duty;
	set_duty(next_duty);
	V[PREVIOUS] = V[NOW];
	I[PREVIOUS] = I[NOW];
}
