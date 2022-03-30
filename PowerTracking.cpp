#include "PowerTracking.h"
PowerTracking::PowerTracking(){
	this->MAX_DUTY = 0.9f;
	this->MIN_DUTY = 0.1f;
	this->DUTY_STEP[UP] = 0.01f;
	this->DUTY_STEP[DOWN] = 0.02f;
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
void PowerTracking::sweep_duty(){
	float step = 0.01f;
	for (float i = MIN_DUTY; i < MAX_DUTY; i += step){
				set_duty(i);
				delay_nms(100);
				read_adc();
				peakCheck();
			}
//	for (float i = MAX_DUTY; i > MIN_DUTY; i -= step){
//				set_duty(i);
//				delay_nms(100);
//			}
	
}

void PowerTracking::set_threshold(float t){
	if(t > 1.0f){t=1.0f;}
	else if(t<0.0f){t= 0.0f;}
	this->threshold = t;
}

float PowerTracking::get_peak_duty(){
	return MAX_POWER_DUTY;
}

bool PowerTracking::peakCheck(){
	if (power[NOW] > MAX_POWER){
		MAX_POWER = power[NOW];
		MAX_POWER_DUTY = duty[NOW];
		return true;
	}
	return false; //if new peak not detected return false
}
float PowerTracking::read_adc(){
	unsigned char i;
	float pwr;
	float adc_data[2];
	ADC1_START();
	for(i=0; i<2; i++)
	{
		while(!(ADC1_EOC));
		adc_data[i]= (float)(ADC1->DR)/4096;
	}
	this->voltage = adc_data[0];
	this->current = adc_data[1];
	pwr = voltage*current;
	if (pwr > MAX_POWER){
		this->MAX_POWER = pwr;
		this->MAX_POWER_DUTY = duty[NOW];
	}
	this->avg_power += (avg_power + pwr)/2;
	return pwr;
}

void PowerTracking::set_OS_AVG_PWR(float p){
	OS_AVG_PWR = p;
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
