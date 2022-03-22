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


};

#ifdef __cplusplus
}
#endif
#endif