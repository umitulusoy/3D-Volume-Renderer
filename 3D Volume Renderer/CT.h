#include "EasyBMP.h"
#include <cstdint>
#include <list>
#include "TransferControlPoint.h"

#pragma once

#define BIT_16_MAX 65536
#define BIT_8_MAX 256

class CT
{
public:
	CT();
	CT(int, int, int);
	~CT();

	void CTLoaderCT16(std::string, std::string);
	void CTLoaderRAW8(std::string, std::string);
	
	void setCT(double*);
	void setVoxel(int, int, int, double);
	void setColorKnots(std::list<TransferControlPoint>);
	void setAlphaKnots(std::list<TransferControlPoint>);
	void setDimensions(int, int, int);

	std::list<TransferControlPoint> getColorKnots();
	std::list<TransferControlPoint> getAlphaKnots();
	double getVoxel(int, int, int);
	int getDimensionX();
	int getDimensionY();
	int getDimensionZ();

	void logSlice(int, std::string);
	void logSliceToTXT(int, std::string);


private:
	double ***ct;
	std::list<TransferControlPoint> colorKnots;
	std::list<TransferControlPoint> alphaKnots;
	int dimensionX;
	int dimensionY;
	int dimensionZ;
};
