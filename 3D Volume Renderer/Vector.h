#pragma once
#include "Color.h"

class Vector
{
public:
	Vector();
	Vector(double, double, double);
	~Vector();

	//set methods
	void setVector(double, double, double);
	void setX(double);
	void setY(double);
	void setZ(double);
	void setColor(Color *);

	//get methods
	double* getVector();
	double getX();
	double getY();
	double getZ();
	Color* getColor();

	//operator overloading methods
	Vector operator+(const Vector&);
	Vector operator-(const Vector&);
	//dot product
	Vector operator*(const Vector&);
	Vector operator/(const Vector&);
	//cross product
	Vector crossProduct(const Vector&);
	//print vector method
	void print();

private:
	double x, y, z;
	Color * color;
};

