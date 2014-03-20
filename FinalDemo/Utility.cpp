#include "Utility.h"

void Utility::Init()
{
	//xCoord = 0;
	//yCoord = 0;
	//zCoord = 0;
	xprint = new char[10];

	x = 10; y = 10; z = 0;
	fontStyle = GLUT_BITMAP_TIMES_ROMAN_24;
}

void Utility::Refresh()
{
	printw(10, 10 , 0, "x = ");

	/*
	if (locationChange())
	{
		std::cout<< "x = " << xCoord << "\n";
		std::cout<< "y = " << yCoord << "\n";
		std::cout<< "z = " << zCoord << "\n";
	}
	*/
}

void Utility::getCameraLocation(double x, double y, double z)
{
	xLast = xCoord;
	yLast = yCoord;
	zLast = zCoord;

	xCoord = x;
	yCoord = y;
	zCoord = z;
}

// pieced together this function from online sources
void Utility::printw(float x, float y, float z, char *format)
{
	va_list args;
	int len;
	int i;
	char *text;
	
	va_start(args, format);

	len = _vscprintf(format, args) + 1;

	text = new char[len];
	//text = (char *) malloc(len * sizeof(char));

	vsprintf_s(text, len, format, args);

	va_end(args);

	glRasterPos3f(x, y, z);

	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(fontStyle, text[i]);

	free(text);
}

void Utility::displayText()
{
	return;
}

bool Utility::locationChange()
{
	if (xCoord == xLast)
		return false;
	if (yCoord == yLast)
		return false;
	if (zCoord == zLast)
		return false;

	return true;

	/*
	if ( xCoord == xLast &&
		 yCoord == yLast &&
		 zCoord == zLast
		)
	{
		return false;
	}
	return true;
	*/
}