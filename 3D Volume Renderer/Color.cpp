#include "Color.h"


Color::Color()
{
	r = 0.0;
	g = 0.0;
	b = 0.0;
	alpha = 0.0;
}

Color::Color(double param1, double param2, double param3, double param4)
{
	r = param1;
	g = param2;
	b = param3;
	alpha = param4;
}

void Color::setAlpha(double param)
{
	alpha = param;
}

void Color::setR( double param)
{
	r = param;
}

void Color::setG(double param)
{
	g = param;
}

void Color::setB(double param)
{
	b = param;
}

double Color::getR()
{
	return r;
}

double Color::getG()
{
	return g;
}

double Color::getB()
{
	return b;
}

double Color::getAlpha()
{
	return alpha;
}

void Color::multiplyRGBwithAlpha( double param)
{
	r *= param;
	g *= param;
	b *= param;
}

void Color::add( Color param)
{
	r += param.getR();
	g += param.getG();
	b += param.getB();
	alpha += param.getAlpha();
}

Color::~Color()
{
}
