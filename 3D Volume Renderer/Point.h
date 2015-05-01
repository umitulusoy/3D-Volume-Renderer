#pragma once
class Point
{
public:
	Point( double, double, double);
	Point();
	~Point();

	void setX(double);
	void setY(double);
	void setZ(double);
	void setPoint(double, double, double);
	void setIntensity(double);

	double getX();
	double getY();
	double getZ();
	double getIntensity();
private:
	double x, y, z;
	double intensity;
};

