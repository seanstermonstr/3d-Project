#include "SolarSystem.h"

void Solar_System::Init()
{
	glShadeModel(GL_SMOOTH);

	// using dynamic memory allocation so that i do not have to manually
	// initialize the vectors.  It seems like a cleaner solution.
	// also i just need practice using pointers and dynamic memory
	// allocation
	planetPtr = new planet[num];
	
	//initializez the structures
	for(int i = 0; i < num; i++)
		initStruct(planetPtr[i], i);
}

void Solar_System::initStruct(planet &x, int i)
{
	//stores all the data in seperate arrays
	float rOrbit[num] = {100, 150, 350, 550}; 
	float xOrbit[num] = {0, 0, 0, 0};
	float yOrbit[num] = {9, 25, 45, 65};
	float angle[num] = {0, 0, 0, 0}; 
	float speed[num] = {.0009, .001, .0008, .0007};
	float red[num] = {0, .5, 1, 0};
	float green[num] = {1, .5, .5, .5};
	float blue[num] = {.5, 1, 0, 0};
	GLdouble radius[num] = {10 ,20, 30, 50};
	GLint slices = 100;
	GLint stacks = 100;

	// actually assignes values to each individual member of the structure
	x.rOrbit = rOrbit[i]; x.xOrbit = xOrbit[i]; x.yOrbit = yOrbit[i];
	x.red = red[i]; x.green = green[i]; x.blue = blue[i];
	x.angle = angle[i];  x.speed = speed[i]; 
	x.slices = slices; x.stacks = stacks;
	x.radius = radius[i];

}

// Refreshed the orbits of the planets
// Mostly code from project 2
void Solar_System::Refresh()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	/*
	// figures out where they all need to be drawn
	for (int i = 0; i < numPlanets; i++){
		OrbitRefresh(i);
	}
	*/
	for (int i = 0; i < num; i++){
		// takes where it needs to be drawn and draws it.  
		glPushMatrix();
		OrbitRefresh(i);
		glColor3f(planetPtr[i].red, planetPtr[i].green, planetPtr[i].blue);
		glTranslatef(planetPtr[i].xOrbit, planetPtr[i].yOrbit, 0);
		glutSolidSphere(planetPtr[i].radius, planetPtr[i].slices, planetPtr[i].stacks);
		glPopMatrix();
	}
	// will be solid later when light source added
	

	glPopMatrix();
}

void Solar_System::OrbitRefresh(int i)
{
	planetPtr[i].angle += planetPtr[i].speed;
	planetPtr[i].xOrbit = planetPtr[i].rOrbit * cos(planetPtr[i].angle);
	planetPtr[i].yOrbit = planetPtr[i].rOrbit * sin(planetPtr[i].angle);

	glutPostRedisplay();
}

// sets the color of the planets. Will texture map them later
void Solar_System::setColor(float r, float g, float b, int i)
{
	planetPtr[i].red = r;
	planetPtr[i].green = g;
	planetPtr[i].blue = b;

}

void Solar_System::Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

