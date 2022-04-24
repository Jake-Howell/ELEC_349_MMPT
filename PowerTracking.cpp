#include "PowerTracking.h"
PowerTracking::PowerTracking(){
	this->MAX_DUTY = 0.95f;
	this->MIN_DUTY = 0.05f;
	this->DUTY_STEP[UP] = 0.01f;
	this->DUTY_STEP[DOWN] = 0.02f;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.0f;
	this->voltage[NOW] = 0.0f;
	this->current[NOW] = 0.0f;
	this->head = 0;
	this->tail =0;
	this->currentBuffSize = 0;
}
PowerTracking::PowerTracking(float max_duty, float min_duty){
	this->MAX_DUTY = max_duty;
	this->MIN_DUTY = min_duty;
	this->duty[PREVIOUS] = 0.0f;
	this->duty[NOW] = 0.0f;
	this->power[PREVIOUS] = 0.0f;
	this->power[NOW] = 0.0f;
	this->avg_power = 0.0f;
	this->voltage[NOW] = 0.0f;
	this->current[NOW] = 0.0f;
	this->head = 0;
	this->tail =0;
	this->currentBuffSize = 0;
}


void PowerTracking::bufferPut(float data[2]){
	//buffer[0][head] = data[0];
	//buffer[1][head] = data[1];
	buffer[head].voltage = data[0];
	buffer[head].current = data[1];
	head++;
	if (head >= BUFFER_SIZE){
		head = 0;
	}
	if (currentBuffSize < (BUFFER_SIZE)){
		currentBuffSize++;
	}
}

sample_t PowerTracking::bufferPop()
{
	sample_t hack;
	hack.voltage = buffer[tail].voltage;
	hack.current = buffer[tail].current;
	tail++;
	return hack;
}


void PowerTracking::sweep_duty(){

	for (float i = MIN_DUTY; i < MAX_DUTY; i += DUTY_STEP[UP]){
				set_duty(i);
				delay_nms(100);
				updateValues();
				peakCheck();
			}
	
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
sample_t PowerTracking::read_adc(){
	sample_t sample;
	red_led_on();
	red_led_off();
	float adc_data[2];
	ADC1_START();
	for(int i=0; i<2; i++){
		while(!(ADC1_EOC));
		adc_data[i]= (float)(ADC1->DR)/4096;
		//get
	}
	
	sample.voltage = adc_data[0];
	sample.current = adc_data[1];
	
	bufferPut(adc_data);
	
	return sample;
}

void PowerTracking::calculateRMS(){
	sample_t sum_x2;
	sample_t avg_x2;
	sample_t RMS;
	
		for (int i = 0; i<BUFFER_SIZE; i++){
			//sum_x2[x] += buffer[x][i]*buffer[x][i]; //calculate square and add to total
			sum_x2.voltage += buffer[i].voltage*buffer[i].voltage;
			sum_x2.current += buffer[i].current*buffer[i].current;
			
		}
		avg_x2.voltage = sum_x2.voltage/BUFFER_SIZE;		//average samples
		avg_x2.current = sum_x2.current/BUFFER_SIZE;		//average samples
		RMS.voltage = sqrtf(avg_x2.voltage);
		RMS.current = sqrtf(avg_x2.current);
	
	
	V_RMS[PREVIOUS] = V_RMS[NOW];
	I_RMS[PREVIOUS] = I_RMS[NOW];
	P_RMS[PREVIOUS] = P_RMS[NOW];
		
	V_RMS[NOW] = RMS.voltage;
	I_RMS[NOW] = RMS.current;
	P_RMS[NOW] = RMS.current*RMS.voltage;
}

void PowerTracking::updateValues(){
	
	

	voltage[PREVIOUS] = voltage[NOW];
	current[PREVIOUS] = current[NOW];
	power[PREVIOUS] = power[NOW];
//	this->voltage[NOW] = buffer[head].voltage; //get latest data off the buffer
//	this->current[NOW] = buffer[head].current;
	//delta_v = V_RMS[NOW] - V_RMS[PREVIOUS];
	//delta_c = I_RMS[NOW] - I_RMS[PREVIOUS];

	
	
	//IF INSTANT
//	//sample_t newsample = bufferPop();	//get last item on buffer
//	this->voltage[NOW] = buffer[head].voltage; //get latest data off the buffer
//	this->current[NOW] = buffer[head].current;
	
	
	//IF RMS
	calculateRMS();
	this->voltage[NOW] = V_RMS[NOW];
	this->current[NOW] = I_RMS[NOW];
	
	//Power depends on above
	this->power[NOW] = voltage[NOW]*current[NOW];
	
	
	
	//update deltas
	delta_v = voltage[NOW] - voltage[PREVIOUS];
	delta_c = current[NOW] - current[PREVIOUS];
	this->delta_p = power[NOW] - power[PREVIOUS]; //calculate power differance
	
	
}

void PowerTracking::set_OS_AVG_PWR(float p)
{
	OS_AVG_PWR = p;
}

void PowerTracking::set_OS_AVG_VOL(float v)
{
	OS_AVG_VOL = v;
}

void PowerTracking::set_OS_AVG_CUR(float c)
{
	OS_AVG_CUR = c;
}
void PowerTracking::set_sampleRate(int Frq){
	sampleFrq = Frq;
	dynamicDelay_ms = ((BUFFER_SIZE*1000)/Frq); //calculate time taken to fill buffer in micro seconds
	
	volatile int psc, arr;
	const int scalar = 12000000;
	//SCC = 168 000 000
	psc = ((SystemCoreClock/2)/scalar); //calculate PSC to get 1/24th us ticks
	arr = (scalar/Frq);				//work out how many nano seconds for given freq
	
	TIM2->PSC = psc -1;
	TIM2->ARR = arr -1;
}
void PowerTracking::set_PB0_PWM_mode(unsigned int Fsw)
{
	PWMFsw = Fsw;
	GPIO_setmode(GPIOB,0,2);	//PB0 alternate function
	config_TIM3();
	PSC3=0;
	TMR3=0;
	PR3=(unsigned short)(SystemCoreClock/(2*Fsw));
	T3CCR3=(unsigned short)(PR3/10);
	start_timer3();
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
	this->duty[PREVIOUS] = duty[NOW];
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

float PowerTracking::getVoltage()
{
	return this->voltage[NOW];
}

float PowerTracking::getCurrent()
{
	return this->current[NOW];
}