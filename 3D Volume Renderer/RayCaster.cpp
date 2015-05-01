#include "RayCaster.h"
#include "Point.h"
#include <iostream>
#include <string>
#include <fstream>
#define RAY_PRECISION 0.5 

RayCaster::RayCaster()
{
}

RayCaster::RayCaster(std::string volumeFolderName, std::string fileName, int param_x, int param_y, int param_z)
{
	volume = new CT(param_x, param_y, param_z);
	//volume->CTLoaderCT16(volumeFolderName, fileName);
	volume->CTLoaderRAW8(volumeFolderName, fileName);
	ray = new Vector();

}

RayCaster::~RayCaster()
{
}

void RayCaster::setImagePlane(Color**param)
{
	imagePlane = param;
}

void RayCaster::setCT( CT * param)
{
	volume = param;
}

Color** RayCaster::getImagePlane()
{
	return imagePlane;
}

CT* RayCaster::getCT()
{
	return volume;
}

void RayCaster::generateImagePlane()
{
	imagePlane = new Color*[volume->getDimensionX()];
	for (int i = 0; i < volume->getDimensionX(); i++)
		imagePlane[i] = new Color[volume->getDimensionY()];

	/*
	for (int x = 0; x < volume->getDimensionX(); x++)
	{
		for (int y = 0; y < volume->getDimensionY(); y++)
		{
			imagePlane[x][y] = new Color();
		}
	}
	*/
}

void RayCaster::constructRays()
{
	Color value;
	Point p0;
	std::cout << "---Casting rays." << std::endl;
	for (double y = 0.5; y < volume->getDimensionY() - 1; y++)
	{
		for (double x = 0.5; x < volume->getDimensionX() - 1; x++)
		{
			p0.setPoint(x, y, -1);
			ray->setVector(0, 0, 1);			//call vector's constructor for refreshing alpha and color
			value = frontBackRayComposition(p0, ray);
			setPixelOnImagePlane( p0, value);	
		}
	}
}

void RayCaster::setPixelOnImagePlane(Point p, Color param)
{
	imagePlane[(int)p.getX()][(int)p.getY()] = param;
}

Color RayCaster::frontBackRayComposition(Point p0, Vector* vector)
{
	Color * cFinal = new Color();
	Color source, destination;
	bool hit = false;
	Point p;
	double immediateIntensity, temp;

	p.setPoint(0, 0, 0);
	for (double d = 0; d < volume->getDimensionZ(); d = d + RAY_PRECISION)
	{
		// Go through equation p = p0 + d*V where d = distance among each step
		p.setX(p0.getX() + d*vector->getX());
		p.setY(p0.getY() + d*vector->getY());
		p.setZ(p0.getZ() + d*vector->getZ());			
		
		hit = isPointInTheVolume(p);
		if (hit)
		{
			immediateIntensity = threeDimensionalInterpolation(p);			//intersection found calculate interpolation
			source = oneDimensionalTransferFunction(immediateIntensity);	//get rgba from transfer function
			source.setAlpha(source.getAlpha() * 0.1);						//reduce the alpha for more transparent result
			source.multiplyRGBwithAlpha(source.getAlpha());					// rgb * a

			//Front to back blending
			// dst.rgb = dst.rgb + (1 - dst.a) * src.a * src.rgb
			// dst.a   = dst.a   + (1 - dst.a) * src.a     
			
			destination = *ray->getColor();									//dst = (1.0f - dst.a)*src + dst
			temp = (1.0 - destination.getAlpha());
			source.multiplyRGBwithAlpha(temp);
			destination.add(source);
			
			ray->setColor(&destination);
			//kills the iteration when alpha gets high enough
			if (ray->getColor()->getAlpha() > 0.95)
				return *ray->getColor();
		}
		hit = false;
	} 
	return *ray->getColor();													//alpha did not reached high enough
}

Color RayCaster::oneDimensionalTransferFunction(double intesity)
{
	double actualIntesity = intesity * BIT_8_MAX;
	Color c;
	if (actualIntesity > 70)
	{
		c.setAlpha(intesity);
		c.setR(actualIntesity + 150);
		c.setG(actualIntesity + 150);
		c.setB(actualIntesity + 150);
	}
	else
	{
		/*c.setAlpha(intesity);
		c.setR(actualIntesity);
		c.setG(actualIntesity);
		c.setB(actualIntesity);*/
	}
	return c;
}

bool RayCaster::isPointInTheVolume(Point p)
{
	double x, y, z;
	x = (double)volume->getDimensionX();
	y = (double)volume->getDimensionY();
	z = (double)volume->getDimensionZ();

	if (p.getX() > x || p.getY() > y || p.getZ() > z)
	{
		return false;
	}
	else if (p.getX() < 0 || p.getY() < 0 || p.getZ() < 0)
	{
		return false;
	}

	else
	{
		return true;
	}
}

bool RayCaster::isIntensityAvailableToSet(Point p)
{
	double intensity = threeDimensionalInterpolation(p) * BIT_8_MAX;
	if (intensity >= 60 && intensity <= 200 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void RayCaster::printImagePlane(std::string filename)
{
	filename += ".bmp";
	BMP output;
	RGBApixel temp;
	output.SetBitDepth(16);
	output.SetSize(volume->getDimensionX(), volume->getDimensionY());

	for (int j = 0; j < volume->getDimensionY(); j++)
	{
		for (int i = 0; i < volume->getDimensionY(); i++)
		{
			temp.Red = (int)imagePlane[i][j].getR();
			temp.Blue = (int)imagePlane[i][j].getB();
			temp.Green = (int)imagePlane[i][j].getG();
			temp.Alpha = (int)imagePlane[i][j].getAlpha();
			output.SetPixel(i, j, temp);
		}
	}
	output.WriteToFile(filename.c_str());
	std::cout << "---Projection has been saved as: " << filename << std::endl;
}

void RayCaster::printFrequency(std::string filename)
{
	frequency = new int[volume->getDimensionX()];

	for (int i = 0; i < volume->getDimensionX(); i++)
		frequency[i] = 0;

	filename += ".txt";
	std::ofstream myfile;
	myfile.open(filename);
	int temp;
	for (int i = 0; i < volume->getDimensionX(); i++)
	{
		for (int j = 0; j < volume->getDimensionY(); j++)
		{
			for (int k = 0; k < volume->getDimensionZ(); k++)
			{
				temp = (int)(volume->getVoxel(i, j, k) * BIT_8_MAX);
				frequency[temp]++;
			}
		}
	}
	for (int i = 0; i < volume->getDimensionX(); i++)
	{
		myfile << frequency[i];
		myfile << std::endl;
	}
	myfile.close();
}

double RayCaster::threeDimensionalInterpolation(Point c)
{
	double x_interpolation[4];
	double y_interpolation[2];
	double z_interpolation;

	int x = (int)c.getX();
	int y = (int)c.getY();
	int z = (int)c.getZ();
	 
	Point Volume[8];
	int counter = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Volume[counter].setPoint(x + k, y + j, z + i);
				counter++;
			}
		}
	}

	x_interpolation[0] = (c.getX() - Volume[0].getX()) / (Volume[1].getX() - Volume[0].getX()) *(volume->getVoxel(x + 1, y, z) - volume->getVoxel(x, y, z)) + volume->getVoxel(x, y, z);
	x_interpolation[1] = (c.getX() - Volume[2].getX()) / (Volume[3].getX() - Volume[2].getX()) *(volume->getVoxel(x + 1, y + 1, z) - volume->getVoxel(x, y + 1, z)) + volume->getVoxel(x, y + 1, z);
	x_interpolation[2] = (c.getX() - Volume[4].getX()) / (Volume[5].getX() - Volume[4].getX()) *(volume->getVoxel(x + 1, y, z + 1) - volume->getVoxel(x, y, z + 1)) + volume->getVoxel(x, y, z + 1);
	x_interpolation[3] = (c.getX() - Volume[6].getX()) / (Volume[7].getX() - Volume[6].getX()) *(volume->getVoxel(x + 1, y + 1, z + 1) - volume->getVoxel(x, y + 1, z + 1)) + volume->getVoxel(x, y + 1, z + 1);

	y_interpolation[0] = (c.getY() - Volume[0].getY()) / (Volume[2].getY() - Volume[0].getY()) * (x_interpolation[1] - x_interpolation[0]) + x_interpolation[0];
	y_interpolation[1] = (c.getY() - Volume[4].getY()) / (Volume[6].getY() - Volume[4].getY()) * (x_interpolation[3] - x_interpolation[2]) + x_interpolation[2];

	z_interpolation = ((c.getZ() - Volume[0].getZ()) / (Volume[4].getZ() - Volume[0].getZ()) *(y_interpolation[1] - y_interpolation[0])) + y_interpolation[0];

	return z_interpolation;
}

void RayCaster::setKnots()
{
	std::list<TransferControlPoint> color = std::list < TransferControlPoint > {
		TransferControlPoint(.91f, .7f, .61f, 0),
		TransferControlPoint(.91f, .7f, .61f, 80),
		TransferControlPoint(1.0f, 1.0f, .85f, 82),
		TransferControlPoint(1.0f, 1.0f, .85f, 256)
	};

	std::list<TransferControlPoint> alpha = std::list<TransferControlPoint>{
		TransferControlPoint(0.0, 0),
		TransferControlPoint(0.0, 40),
		TransferControlPoint(0.2, 60),
		TransferControlPoint(0.05, 63),
		TransferControlPoint(0.0, 80),
		TransferControlPoint(0.9, 82),
		TransferControlPoint(1, 256)
	};

	volume->setAlphaKnots(alpha);
	volume->setColorKnots(color);
}