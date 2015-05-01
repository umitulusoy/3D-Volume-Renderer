#include "CT.h"
#include <fstream>
#include <string>
#include <iostream>
#include <cstdint>
using namespace std;

CT::CT(int param_x, int param_y, int param_z)
{
	//set dimensions
	setDimensions(param_x, param_y, param_z);

	//ct array 3D allocation  
	ct = new double**[param_x];
	for (int x = 0; x < param_x; ++x){
		ct[x] = new double*[param_y];
		for (int y = 0; y < param_y; ++y){
			ct[x][y] = new double[param_y];
		}	
	}
}

CT::~CT()
{
}

void CT::setAlphaKnots(std::list<TransferControlPoint> param)
{
	alphaKnots = param;
}

void CT::setDimensions(int param_x, int param_y, int param_z)
{
	dimensionX = param_x;
	dimensionY = param_y;
	dimensionZ = param_z;
}

void CT::setColorKnots(std::list<TransferControlPoint> param)
{
	colorKnots = param;
}

std::list<TransferControlPoint> CT::getAlphaKnots()
{
	return alphaKnots;
}

std::list<TransferControlPoint> CT::getColorKnots()
{
	return colorKnots;
}

/*
void CT::setCT(double param[][CT_Y][CT_Z]){
	for (int i = 0; i < CT_X; i++)
	{
		for (int j = 0; j < CT_Y; j++)
		{
			for (int k = 0; k < CT_Z; k++)
			{
				ct[i][j][k] = param[i][j][k];
			}
		}
	}
}
*/

void CT::CTLoaderCT16(string location, string name){
	cout << "---Volume loading to memory." << endl;
	unsigned __int16 temp;
	for (int z = 0; z < dimensionZ; z++)	//iterates through slices(z)									
	{
		string	filePath = location + "\\" + name + "." + to_string(z+1);
		ifstream ctFile(filePath, ios::binary | ios::in);
		if (ctFile.is_open())
		{
			ctFile.clear();
			ctFile.seekg(0);
			for (int y = 0; y < dimensionY; y++)	//iterates through height(y)
			{
				for (int x = 0; x < dimensionX; x++) //iterates through width(x)
				{
					ctFile.read((char*)&temp, sizeof(temp));
					ct[x][y][z] = (double)temp / BIT_16_MAX;
					if (temp < 0)
						cout << "negative intensity: " << temp << endl;
				}
			}
			ctFile.close();
		}
		else
		{
			cout << filePath << "---File could not opened." << endl;
		}
	}
	cout << "---Volume loaded to memory." << endl;
}

void CT::CTLoaderRAW8(string location, string filename){
	cout << "---Volume loading to memory." << endl;
	unsigned __int8 temp;
	string	filePath = location + "\\" + filename + ".raw";
	ifstream ctFile(filePath, ios::binary | ios::in);
	if (ctFile.is_open())
	{
		ctFile.clear();
		ctFile.seekg(0);
		for (int z = 0; z < dimensionZ; z++)	//iterates through slices(z)									
		{
			for (int y = 0; y < dimensionY; y++)	//iterates through height(y)
			{
				for (int x = 0; x < dimensionX; x++) //iterates through width(x)
				{
					ctFile.read((char*)&temp, sizeof(temp));
					ct[x][y][z] = (double)temp / BIT_8_MAX;
				}
			}
		}
		ctFile.close();
		cout << "---Volume loaded to memory." << endl;
	}
	else
	{
		cout << filePath << "---File could not opened." << endl;
	}
}

void CT::setVoxel(int paramX, int paramY, int paramZ, double param){
	ct[paramX][paramY][paramZ] = param;
}

double CT::getVoxel(int paramX, int paramY, int paramZ){
	return ct[paramX][paramY][paramZ];
}

void CT::logSlice(int param, string param1){
	string	outputFileName = param1 + ".bmp";
	BMP output;
	RGBApixel temp;
	output.SetBitDepth(16);
	output.SetSize(dimensionX, dimensionY);
	double r, g, b;

	for (int j = 0; j < dimensionY; j++)
	{
		for (int i = 0; i < dimensionX; i++)
		{
			r = (ct[i][j][param]) * BIT_8_MAX;
			g = (ct[i][j][param]) * BIT_8_MAX;
			b = (ct[i][j][param]) * BIT_8_MAX;
			temp.Red = (int)r;
			temp.Blue = (int)b;
			temp.Green = (int)g;
			output.SetPixel(i,j, temp);
		}
	}
	output.WriteToFile(outputFileName.c_str());
}

void CT::logSliceToTXT(int param, string param1){
	string	outputFileName = param1 + ".txt";
	ofstream myfile;
	myfile.open(outputFileName);
	int temp;
	for (int j = 0; j < dimensionY; j++)
	{
		for (int i = 0; i < dimensionX; i++)
		{
			temp = (int)((ct[i][j][param]) * BIT_8_MAX);
			myfile << temp <<" ";
		}
		myfile << endl;
	}
	//cout << (ct[138][77][40]) << endl << ct[44][74][param] << endl;
	myfile.close();
}

int CT::getDimensionX()
{
	return dimensionX;
}

int CT::getDimensionY()
{
	return dimensionY;
}

int CT::getDimensionZ()
{
	return dimensionZ;
}