/**********************************************************
 * testimage.cpp -- part of CS225 MP2
 *
 * This file performs some basic tests of the Image class.
 * It is not intended to catch every possible error.You may 
 * modifty this or write your own testimage.cpp to perform 
 * additional tests.
 *
 *   Author: Jonathan Ray
 *   Date: 02 Feb 2007
 */

#include "image.h"
#include <iostream>
using namespace std;
int main()
{
	Image* myImage = new Image();
	myImage->readFromFile("warmStreamflow3.png");
	myImage->doEverything();
	myImage->writeToFile("out.png");
	delete myImage;
	
	return 0;
}

