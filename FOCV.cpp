#include "FOCV.h"
//MPP = K*VOC
//To get VOC measure solar panel without any load
//this needs to be done each time illumination changes

FOCV::FOCV():K(0.7){
	
}
FOCV::FOCV(float K, float VOC):K(K), VOC(VOC){

}
void FOCV::evaluate(){
	
}

float FOCV::get_K(){
	return this->K;
}

float FOCV::get_VOC(){
	return this->VOC;
}