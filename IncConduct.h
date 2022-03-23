#ifndef _FOCV_H__
#define _FOCV_H__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "PowerTracking.h"
	
class IncConduct : public PowerTracking{
		public:
			IncConduct();
			//IncConduct();
			void evaluate() override;

		private:
			
		volatile float V[2];
		volatile float I[2];
		volatile float deltaV;
		volatile float deltaI;
};

#ifdef __cplusplus
}
#endif
#endif