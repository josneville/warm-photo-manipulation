/*
 * =====================================================================================
 *
 *       Filename:  image.cpp
 *
 *    Description:  The image class is a subclass of the PNG class. This is it's CPP file.
 *
 *        Version:  1.0
 *        Created:  01/29/2014 09:19:11 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dr. Fritz Mehner (mn), mehner@fhswf.de
 *        Company:  FH Südwestfalen, Iserlohn
 *
 * =====================================================================================
 */

#include "image.h"
#include <iostream>
using namespace std;
void Image::discoverStations()
{	
	RGBAPixel black;
	black.red = 10;
	black.green = 10;
	black.blue = 10;
	RGBAPixel pureBlack;
	pureBlack.red = 0;
	pureBlack.green = 0;
	pureBlack.blue = 0;
	RGBAPixel white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;
	RGBAPixel temp;
	temp.red = 255;
	temp.green = 0;
	temp.blue = 0;
	yBoxL = new int[8];
	xBoxL = new int[8];
	xBoxL[0] = 23;
	yBoxL[0] = -24;
	xBoxL[1] =  -27;
	yBoxL[1] = -70;
	xBoxL[2] = -79;
	yBoxL[2] = -26;
	xBoxL[3] = -28;
	yBoxL[3] = 20;
	xBoxL[4] = xBoxL[0] - 5;
	yBoxL[4] = yBoxL[1] + 5;
	xBoxL[5] = xBoxL[2] + 5;
	yBoxL[5] = yBoxL[1] + 5;
	xBoxL[6] = xBoxL[2] + 5;
	yBoxL[6] = yBoxL[3] - 5;
	xBoxL[7] = xBoxL[0] - 5;
	yBoxL[7] = yBoxL[3] - 5;
	for(int y = 0; y < int(height()); y++)
	{
		for (int x = 0; x < int(width()); x++)
		{

			if (black < *this->operator()(x,y))
			{
				//*this->operator()(x,y) = white;
			}
			else
			{
				if (*this->operator()(x+3, y) < black && *this->operator()(x-3,y) < black && *this->operator()(x,y+3) < black && *this->operator()(x,y-3) < black && *this->operator()(x+2,y+2) < black && *this->operator()(x+2,y-2) < black && *this->operator()(x-2,y+2) < black && *this->operator()(x-2,y-2) < black)
				{
					*this->operator()(x,y) = temp;
				} 
			}
		}	
	}
	for(int y = 0; y < int(height()); y++)
	{
		for(int x = 0; x < int(width()); x++)
		{
			if(*this->operator()(x,y) == temp)
			{
				for(int i = -3; i < 4; i++)
				{
					for(int j = -3; j < 4; j++)
					{
						if (i != 0 || j != 0)
						{
							*this->operator()(x+i,y+j) = pureBlack;
						}
					}	
				}
				
			}
		}
	}
	for(int y = 0; y < int(height()); y++)
	{
		for(int x = 0; x < int(width()); x++)
		{
			if(*this->operator()(x,y) != pureBlack && *this->operator()(x,y) < black)
			{	
				*this->operator()(x,y) = white;
			}
		}
	}
}

void Image::updateCoords()
{
	discoverStations();	
	max = stationCount();
	xCoords = new int[max];
	yCoords = new int[max];
	location = new int[max];
	RGBAPixel temp;
	temp.red = 255;
	temp.green = 0;
	temp.blue = 0;
	int counter = 0;
	for (int y = 0; y < int(height()); y++)
	{
		for (int x = 0; x < int(width()); x++)
		{
			if(*this->operator()(x,y) == temp)
			{
				xCoords[counter] = x;
				yCoords[counter] = y;
				counter++;
			}
		}
	}
}

int Image::stationCount()
{
	
	int counter =  0;
	RGBAPixel temp;
	temp.red = 255;
	temp.green = 0;
	temp.blue = 0;
	for(int y = 0; y < int(height()); y++)
	{
		for (int x = 0; x < int(width()); x++)
		{
			if (*this->operator()(x,y) == temp) counter++;
		}	
	}
	return counter;
}

void Image::printBox(int x, int y, int flagType)
{
	RGBAPixel temp;
	temp.red = 128;
	temp.green = 128;
	temp.blue = 128;
	RGBAPixel white;
	white.red = 255;
	white.green = 255;
	white.blue = 255;

	int w = 55; 
	int h = 51;
	for (int q = x+xBoxL[flagType]; q<x+xBoxL[flagType]+w; q++)
	{
		for (int r = y+yBoxL[flagType]; r < y+h+yBoxL[flagType]; r++)
		{
			*this->operator()(q,r) = temp;
		}
	}
}

bool Image::checkEmpty(int x, int y, int flagType)
{
	RGBAPixel temp;
	temp.red = 128;
	temp.green = 128;
	temp.blue = 128;
	RGBAPixel black;
	black.red = 10;
	black.green = 10;
	black.blue = 10;
	int w = 55;
	int h = 51;
	int xStartPoint = x+xBoxL[flagType];
	int xEndPoint = xStartPoint + w;
	int yStartPoint = y + yBoxL[flagType];
	int yEndPoint = yStartPoint + h;
	switch (flagType)
	{
		case 0:
			xStartPoint = x + 4;
			break;
		case 1:
			yEndPoint = y - 4;
			break;
		case 2:
			xEndPoint = x - 4;
			break;
		case 3:
			yStartPoint = y + 4;
			break;	
		case 4:
			xStartPoint = x + 4;
			yEndPoint = y - 4;
			break;
		case 5:
			yEndPoint = y - 4;
			xEndPoint = x - 4;
			break;
		case 6:
			xEndPoint = x - 4;
			yStartPoint = y + 4;
			break;
		case 7:
			yStartPoint = y + 4;
			xStartPoint = x + 4;
			break;		
	}
	for (int q = xStartPoint; q<xEndPoint; q++)
	{
		for (int r = yStartPoint; r < yEndPoint; r++)
		{
			if (q >= int(width()) || q < 0) return false;
			if (r >= int(height()) || r < 0) return false;
			if (*this->operator()(q,r) == temp) return false;
			if (*this->operator()(q,r) < black) return false;
		}
	}
	return true;
}

void Image::finalMap()
{
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if(checkEmpty(xCoords[i], yCoords[i], j))
			{
				printBox(xCoords[i], yCoords[i], j);
				location[i] = j;
				cout << "Image Number: " << i << endl;
				cout << "Coordinates: (" << xCoords[i] + xBoxL[location[i]] << "," << yCoords[i] + yBoxL[location[i]] << ")" << endl;
				cout << "Map Type: " << location[i] << endl;
				cout << " " << endl;
				this->writeToFile("out.png");
				int banana;
				cout << "New Box" << endl;
				cin >> banana;
				break;
			}
		}
	}	
}

void Image::doEverything()
{
	updateCoords();
	finalMap();
	cout << "MAX: " << max << endl;
	for (int i = 0; i < max; i++)
	{
		cout << "Image Number: " << i << endl;
		cout << "Coordinates: (" << xCoords[i] + xBoxL[location[i]] << "," << yCoords[i] + yBoxL[location[i]] << ")" << endl;
		cout << "Map Type: " << location[i] << endl;
		cout << " " << endl;
	}	
}
