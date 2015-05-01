#include "Vector.h"
#include <iostream>

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
	color = new Color();
}

Vector::Vector(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
	color = new Color();
}

Vector::~Vector()
{
}

void Vector::setVector(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

void Vector::setColor(Color* param)
{
	color = param;
}

Vector Vector::operator+(const Vector& b)
{
	Vector v;
	v.x = this->x + b.x;
	v.y = this->y + b.y;
	v.z = this->z + b.z;
	return v;
}

Vector Vector::operator-(const Vector& b)
{
	Vector v;
	v.x = this->x - b.x;
	v.y = this->y - b.y;
	v.z = this->z - b.z;
	return v;
}

Vector Vector::operator*(const Vector& b)
{
	Vector v;
	v.x = this->x * b.x;
	v.y = this->y * b.y;
	v.z = this->z * b.z;
	return v;
}

Vector Vector::operator/(const Vector& b)
{
	Vector v;
	v.x = this->x / b.x;
	v.y = this->y / b.y;
	v.z = this->z / b.z;
	return v;
}

Vector Vector::crossProduct(const Vector& b)
{
	Vector v;
	v.x = (this->y * b.z) - (this->z * b.y);
	v.y = (this->x * b.z) - (this->z * b.x);
	v.z = (this->x * b.y) - (this->y * b.x);
	return v;
}

void Vector::print()
{
	std::cout << "Vector = [" << this->x << " " << this->y << " " << this->z << "]" << std::endl;
}

double Vector::getX()
{
	return x;
}

double Vector::getY()
{
	return y;
}

double Vector::getZ()
{
	return z;
}

double* Vector::getVector()
{
	double* vector;
	vector = new double[3];
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	return vector;
}

Color* Vector::getColor()
{
	return color;
}
