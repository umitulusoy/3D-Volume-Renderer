#pragma once
#include "CT.h"
#include "Vector.h"
#include "Point.h"
#include "Color.h"

class RayCaster
{
public:
	RayCaster();
	RayCaster(std::string, std::string, int, int, int);
	~RayCaster();
	
	Color** getImagePlane();
	CT* getCT();

	void setImagePlane(Color**);
	void setPixelOnImagePlane(Point, Color);
	void setCT(CT*);
	void setKnots();

	void constructRays();
	Color oneDimensionalTransferFunction(double);
	double threeDimensionalInterpolation(Point);
	Color frontBackRayComposition(Point, Vector*);

	void generateImagePlane();
	void printImagePlane(std::string);
	void printFrequency(std::string);

	bool isPointInTheVolume(Point);
	bool isIntensityAvailableToSet(Point);

private:
	Color **imagePlane;
	CT *volume;
	int *frequency;
	Vector *ray;
};

