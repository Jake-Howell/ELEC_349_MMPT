#ifndef _PO_H__
#define _PO_H__
#ifdef __cplusplus
extern "C" {
#endif
	
#include "PowerTracking.h"
	
class PeturbObserb : public PowerTracking{
		public:
			PeturbObserb();
			void evaluate() override;
			bool powerGood(); //checks power within a set threshold

};

#ifdef __cplusplus
}
#endif
#endif
