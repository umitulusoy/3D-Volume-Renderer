#pragma once
class Color
{
public:
	Color();
	Color(double, double, double, double);
	~Color();

	void setR(double);
	void setG(double);
	void setB(double);
	void setAlpha(double);
	void multiplyRGBwithAlpha( double );
	void add(Color);

	double getR();
	double getG();
	double getB();
	double getAlpha();
private:
	double r, g, b, alpha;

};

