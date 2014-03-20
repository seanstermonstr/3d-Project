#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
  #include <GLUT/glut.h>         // glut.h includes gl.h and glu.h
#else
  #include <GL/glut.h>         // glut.h includes gl.h and glu.h
#endif
#define PI 3.1415926535897


class Camera {
public:
	 

	void Init();
	Camera::Camera(){ Init(); }  // Constructor
	~Camera(){};  // Destructor

	void zoomIn();
	void zoomOut();
	void rotateLeft();
	void rotateRight();
	void cameraX();
	void cameraY();
	void cameraZ();
	void moveCamera();
	void key();

	void lookY(int x, int y);
	void lookXZ(int x, int y);
	void mouse(int button, int state, int x, int y);

	void getInput(unsigned char key, int x, int y);

	// Test functions


	void Refresh();
	void SetPos(float x, float y, float z);
	void GetPos(float &x, float &y, float &z);
	void GetDirectionVector(float &x, float &y, float &z);
	void SetYaw(float angle);
	void SetPitch(float angle);
	void SetRotation(float angle);

		// Navigation
	void Move(float incr);
	void Strafe(float incr);
	void Fly(float incr);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRotate(float angle);

	double getX();
	double getY();
	double getZ();

	// End of test functions

	// Data Members

	//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the current angle between the vector (1,0,0) and (eyex, eyey, eyez)
double C_angle;
float scale;

double speed; 
int neg;

GLdouble radius;
//const double PI = 3.14156;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the radius of the camera's orbit
double C_Radius;

//Camera on y = 0 plan, circling around (0,0,0)
//The following variable records the rotation speed of the camera
double C_increment;

//Camera on y = 0 plan, circling around (0,0,0)
//Recording the currnet position of the camera.
double eyex, eyey, eyez; 

//Camera on y = 0 plan, circling around (0,0,0)
//Specifies the position of the point looked at
double centerx, centery, centerz; 
	

//Specifies the direction of the up vector. 
double upx, upy, upz;

//private:
	// for storing the input received in getInput
	char input;
	char eyeStore;

	int mousex;
	int mousey;

	// Data members for test functions

	friend class Utility;
	friend class ship;

private:
	float m_x, m_y, m_z;   // Position

	// The direction vector is what the object is in relation to the xyz axis
	// ie what direction it is pointing in a 3 dimentional plain
    float m_lx, m_ly, m_lz; // Direction vector of where we are looking at

	// yaw refers to rotation of the camera that changes the direction it is facing
	// ie right or left

	// pitch refers to the up or the lateral axis of the camera
	// ie if the camera is facing up or down
	float m_yaw, m_pitch; // Various rotation angles


	float m_strafe_lx, m_strafe_lz; // Always 90 degree to direction vector

};
#endif