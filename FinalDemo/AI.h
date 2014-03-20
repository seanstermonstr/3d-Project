#ifndef AI_H
#define AI_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include "camera.h"
#include <ctime>
#include <vector>
#include "tga.h"

#define MAX_TEXTURES 1

class ship {
	
private:
	struct asteroid {
		float eyex, eyey, eyez;
		bool collected;
	};

	// for the collision vector
	struct Vector {
		
		float vectorX, vectorY, vectorZ;
		float distance;
	} Col;  // for collision
public:

	ship(){ Init(10); };
	//~ship();

	void Init(int numShip);
	void newShip(asteroid &astr);
	void Refresh();
	void locationRefresh(int i);
	void getCameraLocation(Camera &CamObj);
	void Move(float incr);
	void texturedCube(GLuint value, float size);
	void collision(asteroid &astr);
	void getCamObj(Camera &CamObj);

private:

	float cameraX, cameraY, cameraZ;
	std::vector<asteroid> astr;
	GLuint texture[MAX_TEXTURES];

	float cameraR;
	GLdouble radius;
	GLint slices, stacks;

	float distanceX, distanceY, distanceZ;

	float astrSize;

	//asteroid *astrPtr;

	const static int shipInit = 100;
};

#endif