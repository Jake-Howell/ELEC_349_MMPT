#include "PowerTracking.h"
PowerTracking::PowerTracking(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.1f;
	this->DUTY_STEP = 0.01f;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.0f;
	this->voltage = 0.0f;
	this->current = 0.0f;
}
PowerTracking::PowerTracking(float max_duty, float min_duty, float duty_step){
	this->MAX_DUTY = max_duty;
	this->MIN_DUTY = min_duty;
	this->DUTY_STEP = duty_step;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.
	this->voltage = 0.0f;
	this->current = 0.0f;
}

void PowerTracking::read_adc(){
	unsigned char i;
	float adc_data[2];
	ADC1_START();
	for(i=0; i<2; i++)
	{
		while(!(ADC1_EOC));
		adc_data[i]=ADC1->DR;
	}
	this->voltage = adc_data[0];
	this->current = adc_data[1];
	this->power[NOW] = voltage*current;
}

float PowerTracking::get_power(int index){
	return this->power[index];
}
	
float PowerTracking::get_avg_power(){
	return this->avg_power;
}
	
float PowerTracking::get_duty(int index){
	return this->duty[index];
}

float PowerTracking::get_max_duty(){
	return this->MAX_DUTY;
}
float PowerTracking::get_min_duty(){
	return this->MIN_DUTY;
}
	
float PowerTracking::get_duty_step(){
	return this->DUTY_STEP;
}

void PowerTracking::set_power(float val){
	this->power[NOW] = val;
}
void PowerTracking::set_avg_power(float val){
	this->avg_power = val;
}

void PowerTracking::set_duty(float d){
	this->duty[NOW] = d;
	if(d>1.0f) d=1.0f;
	T3CCR3=(unsigned short)(d*(float)PR3);
}
void PowerTracking::set_max_duty(float val){
	this->MAX_DUTY = val;
}
void PowerTracking::set_min_duty(float val){
	this->MIN_DUTY = val;
}
void PowerTracking::set_duty_step(float val){
	this->DUTY_STEP = val;
}