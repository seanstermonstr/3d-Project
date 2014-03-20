#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include "camera.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

class Utility{

public:

	//constructor
	Utility::Utility(){ Init(); }
	~Utility(){} // Destructor

	void Init();
	void Refresh();
	void getCameraLocation(double x, double y, double z);
	void printw(float x, float y, float z, char *format);
	void displayText();

	bool locationChange();

private:
	// class specific data members
	double xCoord;
	double yCoord;
	double zCoord;
	double xLast, yLast, zLast;

	// holds location of bitmap
	float x, y, z;
	char *xprint;

	GLvoid *fontStyle;
};

#endif