#include "Point.h"


Point::Point()
{
}

Point::Point(double param1, double param2, double param3)
{
	x = param1;
	y = param2;
	z = param3;
}

void Point::setPoint(double param1, double param2, double param3)
{
	x = param1;
	y = param2;
	z = param3;
}

void Point::setX(double param)
{
	x = param;
}

void Point::setY(double param)
{
	y = param;
}

void Point::setZ(double param)
{
	z = param;
}

double Point::getX()
{
	return x;
}

double Point::getY()
{
	return y;
}

double Point::getZ()
{
	return z;
}

double Point::getIntensity()
{
	return intensity;
}

void Point::setIntensity(double param)
{
	intensity = param;
}

Point::~Point()
{
}
