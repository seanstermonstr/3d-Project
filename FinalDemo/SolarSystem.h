#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <vector>

#define PI 3.1415926535897

class Solar_System {

private:
	// struct that holds the data
	// for the different planets
	struct planet{

		float rOrbit, xOrbit, yOrbit;
		float angle, speed;
		float red, green, blue;
		GLdouble radius;
		GLint slices, stacks;
	};

public:

	Solar_System::Solar_System(int num) { initSol = false;
										  num = 4;}
	~Solar_System(){ delete [] planetPtr; };
	void Init();
	void setColor(float r, float g, float b, int i);
	void getMemberValue();
	void setMemberValue();
	void initStruct(planet &x, int i);

	void Refresh(); // refereshes the orbits
	void OrbitRefresh(int i); // does the math for refresh
	void Reshape(int w, int h);

	friend class Collision;

	// Data members

private:



	//std::vector<planet> planets;
	planet *planetPtr;
	static const int num = 4;

	bool initSol;


	/*
	std::vector<float> rOrbit;
	std::vector<float> xOrbit;
	std::vector<float> yOrbit;
	std::vector<float> angle;
	std::vector<float> speed;
	std::vector<float> red;
	std::vector<float> green;
	std::vector<float> blue;
	*/
};

#endif