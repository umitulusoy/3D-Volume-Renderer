#include "TransferControlPoint.h"


TransferControlPoint::TransferControlPoint(double alpha, int isovalue)
{
	color.Red = 0.0f;
	color.Green = 0.0f;
	color.Blue = 0.0f;
	color.Alpha = alpha;
	isoValue = isovalue;
 
}

TransferControlPoint::TransferControlPoint(double r, double g, double b, int isovalue)
{
	color.Red = r;
	color.Green = g;
	color.Blue = b;
	color.Alpha = 1.0f;
	isoValue = isovalue;
}

TransferControlPoint::~TransferControlPoint()
{
}
