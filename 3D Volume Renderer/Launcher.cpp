#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include "RayCaster.h"

int main(){
	//RayCaster * test = new RayCaster("CThead", "CThead");
	//RayCaster * test = new RayCaster("MRbrain", "MRbrain", 256, 256, 109);
	//RayCaster * test = new RayCaster("Bonsai", "Bonsai",256,256,256);
	//RayCaster * test = new RayCaster("Engine", "Engine", 256,256,128);
	//RayCaster * test = new RayCaster("Teapot", "Teapot", 256,256,178);
	//RayCaster * test = new RayCaster("Leg", "Leg");
	RayCaster * test = new RayCaster("Skull", "Skull", 256,256,256);
	
	//test->setKnots();
	test->generateImagePlane();
	test->constructRays();
	test->printImagePlane("Skull_1D_Presetation5");
	//test->getCT().logSlice(45,"Slice 45");
	//test->getCT().logSlice(40,"slice 40");
	//test->getCT().logSliceToTXT(40, "slice 40");
	//test->printFrequency("Skull_frequency_array");

	system("PAUSE");
	return 1;
}