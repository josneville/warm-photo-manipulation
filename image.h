/*
 * =====================================================================================
 *
 *       Filename:  image.h
 *
 *    Description:  Image Class is a subclass of the PNG class. This is it's header file
 *
 *        Version:  1.0
 *        Created:  01/29/2014 09:18:33 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#ifndef IMAGE_H
#define IMAGE_H
#include "png.h"
class Image : public PNG
{
	public:
		void printBox(int x, int y, int flagType);
		void doEverything();
		int *xCoords;
		int *yCoords;
		int *location;
		int * xBoxL;
		int * yBoxL;
	private:
		void updateCoords();
		void finalMap();
		void discoverStations();	
		bool checkEmpty(int x, int y, int flagType);
		int stationCount();
		int max;
		 
};
#endif
