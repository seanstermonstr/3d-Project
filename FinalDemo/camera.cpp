#include "camera.h"


void Camera::Init()
{
	//used for glOrtho
	scale = 30.0;

	C_angle = 0; //current angle between ventor (1,0,0) and (eyez, eyey, eyez)
	C_Radius = 20; // radius of cameras orbit
	radius = 6;
	//rotation speed of the camera
	neg = 1;
	speed = 2;
	C_increment = 2 * PI / (360 * speed);

	// Current pos of camera
	eyex = 1;  eyey = 1000;  eyez = C_Radius;

	// Position of the point looked at as 0,0,0
	centerx = 0; centery = 0; centerz = 0;

	//specifies the direction of the up vector.
	upx = 0; upy = 0; upz = 0;

	eyeStore = 'y'; // initiates movement

	// Init stuff for test functions

	m_yaw = 0.0;
	m_pitch = 0.0;

	SetPos(0,0,0);


	//CameraInit();
	//mousex = 500;
	//mousey = 500;
}

// gets user input and decides what to do with it
void Camera::getInput(unsigned char key, int x, int y)
{
	input = key;
	//Camera::key();	
}

// Uses user input 
void Camera::key()
{
	switch(input)
	{
	case 'i':
		zoomIn();
		break;

	case 'm':
		zoomOut();
		break;

	case 'j':
		rotateLeft();
		break;

	case 'k':
		rotateRight();
		break;

	case 'x':
		eyeStore = 'x';
		break;

	case 'y':
		eyeStore = 'y';
		break;

	case 'z':
		eyeStore = 'z';
		break;
		default:

			std::cout<<"Invalid option, please try again,\n";
			break;
		}
	//glutSwapBuffers();
}

// rotates the camera to the left
void Camera::rotateLeft()
{
	if (speed < 5 && neg == 1)
		speed += 0.2;
	else
	{
		neg = -1;
		speed -= 0.2;
	}
	//moveCamera();
}

// rotates the camera to the right
void Camera::rotateRight()
{
	if (speed < 5 && neg == -1)
		speed += 0.2;
	else
	{
		neg = 1;
		speed -= 0.2;
	}
	//moveCamera();	
}

// camera zooms in 
void Camera::zoomIn()
{
	C_Radius -= 0.2;
}

// camera zooms out
void Camera::zoomOut()
{
	C_Radius += 0.2;
}

// figures out camera location for rotation on x axis
void Camera::cameraX()
{
	eyex = 0;
	eyey = C_Radius * cos(C_angle);
	eyez = C_Radius * sin(C_angle);

	upx = 0;
	upy = cos(C_angle + PI/2);
	upz = sin(C_angle + PI/2);
}

// figures out camera location for rotation on the y axis
void Camera::cameraY()
{
	eyex = C_Radius * cos(C_angle);
	eyey = 0;
	eyez = C_Radius * sin(C_angle);

	upx = 0;
	upy = 1;
	upz = 0;
}

// figures out camera location for rotation on the z axis
void Camera::cameraZ()
{
	eyex = C_Radius * cos(C_angle);
	eyey = C_Radius * sin(C_angle);
	eyez = 0;

	upx = cos(C_angle + PI/2);
	upy = sin(C_angle + PI/2);
	upz = 0;
}

void Camera::moveCamera()
{
	C_increment = 2 * PI / (neg*360*(pow(2, speed)));
	C_angle += C_increment;
	if(C_angle > 2*PI)
		C_angle -= 2*PI;

	switch(eyeStore)
	{
	case 'x':
		cameraX();
		break;
	case 'y':
		cameraY();
		break;
	case 'z':
		cameraZ();
		break;
	}

	glutPostRedisplay();
}

void Camera::lookXZ(int x, int y)
{
	
}

void Camera::lookY(int x, int y)
{
	
}

void Camera::mouse(int button, int state, int x, int y)
{
	/*

	switch(button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			lookXZ(x, y);
			lookY(x, y);
		}
		break;

	default:
		//std::cout<<"Invalid input please try again.\n";
		break;
	}

	mousex = x;
	mousey = y;
	*/
}

//Test Functions from other code
// Intigrate with current functions if they work

void Camera::SetPos(float x, float y, float z)
{

	m_x = x;
	m_y = y;
	m_z =z;

	Refresh();
}

void Camera::GetPos(float &x, float &y, float &z)
{
    x = m_x;
    y = m_y;
    z = m_z;
}

void Camera::GetDirectionVector(float &x, float &y, float &z)
{
    x = m_lx;
    y = m_ly;
    z = m_lz;
}

void Camera::Refresh()
{
	// See Riegl's co-ordinate system
	// x/y for flat, z for height
	m_lx = cos(m_yaw) * cos(m_pitch);
	m_ly = sin(m_pitch); // the direction of the yaw vector (?)
	m_lz = sin(m_yaw) * cos(m_pitch);

	m_strafe_lx = cos(m_yaw - PI);
	m_strafe_lz = sin(m_yaw - PI);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	gluLookAt( m_x, m_y, m_z, 
		       m_x + m_lx, m_y + m_ly, m_z + m_lz, 
			   0.0,1.0,0.0); 
}

void Camera::Move(float incr)
{
	float lx = cos(m_yaw) * cos(m_pitch);
	float ly = sin(m_pitch);
	float lz = sin(m_yaw) * cos(m_pitch);

	m_x += (incr * lx);
	m_y += (incr * ly);
	m_z += (incr * lz);

	Refresh();
}

void Camera::Strafe(float incr)
{
	m_x = m_x + incr*m_strafe_lx;
	m_z = m_z + incr*m_strafe_lz;

	Refresh();
}

void Camera::Fly(float incr)
{
	m_y += incr;

	Refresh();
}

void Camera::RotateYaw(float angle)
{
	m_yaw += angle;

	Refresh();
}

void Camera::RotatePitch(float angle)
{
	const float limit = 89.0 * PI / 180.0;

	m_pitch -= angle;

	if(m_pitch < -limit)
		m_pitch = -limit;

	if(m_pitch > limit)
		m_pitch = limit;

	Refresh();
}

void Camera::RotateRotate(float angle)
{
	
}

void Camera::SetYaw(float angle)
{
	m_yaw = angle;

	Refresh();
}

void Camera::SetPitch(float angle)
{
	m_pitch = angle;

	Refresh();
}

void Camera::SetRotation(float angle)
{
	
}

double Camera::getX()
{
	return eyex;
}

double Camera::getY()
{
	return eyey;
}

double Camera::getZ()
{
	return eyez;
}
