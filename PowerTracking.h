#ifndef _PT_H__
#define _PT_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "init.h"

class PowerTracking{
	public:
		PowerTracking();
		PowerTracking(float max_duty, float min_duty);
		virtual void 	evaluate() = 0;
		void 	read_adc();
		float get_power(int index);
		float get_duty(int index);
		float get_avg_power();
		float get_duty();
		float get_max_duty();
		float get_min_duty();

		
	
		void set_power(float val);
		void set_avg_power(float val);
		void set_duty(float val);
		void set_max_duty(float val);
		void set_min_duty(float val);

		enum{PREVIOUS = 0, NOW};
		enum{DOWN = 0, UP};
	protected:
		volatile float power[2];
		volatile float delta_p;
		volatile float avg_power;
		volatile float duty[2];
		volatile float next_duty;
		volatile float delta_d;
		volatile float MAX_DUTY;
		volatile float MIN_DUTY;
		volatile float DUTY_STEP[2];
		volatile float voltage;
		volatile float current;
		

};
#ifdef __cplusplus
}
#endif
#endif
