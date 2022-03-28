#include "PowerTracking.h"
PowerTracking::PowerTracking(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.1f;
	this->DUTY_STEP[UP] = 0.01f;
	this->DUTY_STEP[DOWN] = 0.01f;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.0f;
	this->voltage = 0.0f;
	this->current = 0.0f;
}
PowerTracking::PowerTracking(float max_duty, float min_duty){
	this->MAX_DUTY = max_duty;
	this->MIN_DUTY = min_duty;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.0f;
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
		adc_data[i]= (float)(ADC1->DR)/4096;
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
	

void PowerTracking::set_power(float val){
	this->power[NOW] = val;
}
void PowerTracking::set_avg_power(float val){
	this->avg_power = val;
}

void PowerTracking::set_duty(float d){
	d = (d<this->MIN_DUTY) ? MIN_DUTY : d;
	d = (d>this->MAX_DUTY) ? MAX_DUTY : d;
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
