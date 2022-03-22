#ifndef _FOCV_H__
#define _FOCV_H__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "PowerTracking.h"
	
class FOCV : public PowerTracking{
		public:
			FOCV();
			FOCV(float K, float VOC);
			void evaluate() override;
			float get_K();
			float get_VOC();
		private:
			const float K;
			float VOC;

};

#ifdef __cplusplus
}
#endif
#endif