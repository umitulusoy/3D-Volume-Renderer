#pragma once
#include "EasyBMP.h"

class TransferControlPoint
{
public:
	TransferControlPoint(double, int);
	TransferControlPoint(double, double, double, int);
	~TransferControlPoint();
private:
	RGBApixel color;
	int isoValue;
};

