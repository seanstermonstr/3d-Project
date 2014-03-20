#include "camera.h"
#include "SolarSystem.h"
#include "Utility.h"
//#include "collision.h"
#include "AI.h"
#include "tga.h"
#include <cstdlib>

#define ONE_SECOND 1
#define MAX_TEXTURES 6
#define WORLD_SIZE 1000

void Timer(int value);
void KeyboardUp(unsigned char key, int x, int y);
void CamCoords();
void collision();
void texturedCube();

static int window;
static int menuId;
static int value = 0;
static int num;

bool FPSmode = false;
bool mouseRightDown = false;
bool mouseLeftDown = false;
bool shiftDown = false;
bool _key[256];
int viewportWidth = 0;
int viewportHeight = 0;
int numPlanets = 4;

Camera CamObj;
Utility UtilObj;
ship ShipObj;
Solar_System SolObj(numPlanets);

//Collision ColObj;



GLuint g_TexturesArray[MAX_TEXTURES];
const float translationSpeed = 1.0;


const float rotationSpeed = PI / 180.0;

void init()
{
	//init the SolObj
	SolObj.Init();

	GLfloat lightPos[] = {.0, .0, 1.0, 0.0};    
	GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };
	
	glClearColor(0, 0.1, 0.1, 0);
	glColor3f(1, 1, 1);
	
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glEnable(GL_DEPTH_TEST);


	//lighting
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   //glLightfv(GL_LIGHT_POSITION)
	

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   // glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	
	
	
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glEnable(GL_LIGHTING);

	//loads textures
	CreateTexture(g_TexturesArray, "stars4.tga", 0);
//	CreateTexture(g_TexturesArray, "stars1.tga", 1);
	//CreateTexture(g_TexturesArray, "stars2.tga", 2);
	//CreateTexture(g_TexturesArray, "stars3.tga", 3);
	//CreateTexture(g_TexturesArray, "stars4.tga", 4);
	//CreateTexture(g_TexturesArray, "stars5.tga", 5);
	 
}

void CamCoords()
{
	UtilObj.getCameraLocation(CamObj.eyex, CamObj.eyey, CamObj.eyez);
	//ShipObj.getCameraLocation(CamObj);
	
}

void Timer(int value)
{
	if (FPSmode)
	{
		if (_key['w'] || _key['W'])
			CamObj.Move(translationSpeed);
		if (_key['s'] || _key['S'])
			CamObj.Move(-translationSpeed);
		if (_key['a'] || _key['A'])
			CamObj.Strafe(translationSpeed);
		if (_key['d'] || _key['D'])
			CamObj.Strafe(-translationSpeed);
		if (mouseLeftDown)
			CamObj.Fly(-translationSpeed);
		if (_key[' '])
			CamObj.Fly(translationSpeed);
			

	}

	glutTimerFunc(1, Timer, 0);
}

void Reshape(int w, int h)
{
	viewportWidth = w;
	viewportHeight = h;
	
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 5000.0);
	glMatrixMode(GL_MODELVIEW);


	//for ()
}

// a grid used for eairly testing
void Grid()
{
    glPushMatrix();
    glColor3f(1,1,1);



    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }


	/*
	for(int i = -50; i < 50; i++){
		glBegin(GL_LINES);
		glVertex3f();
		glEnd();
	}
	*/
    glPopMatrix();
}



void Display(void)
{

	GLfloat pos[4] = {5, 0, 0, 1};

	glMatrixMode(GL_MODELVIEW);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//glLightfv(GL_LIGHT0, GL_POSITION, pos);

	// refereshes all the class objects at once
	CamObj.Refresh();
	SolObj.Refresh();
	//passes new cam coords to utilObj
	CamCoords();
	//UtilObj.getCoords(CamObj.getX(), CamObj.getY(), CamObj.getZ());
	//UtilObj.Refresh();
	//ShipObj.Refresh();
	

	glColor3f(1, 1, 0);
	//glutWireTeapot(0.5);
	glutWireSphere(50,100,100);

	
	ShipObj.texturedCube(g_TexturesArray[0], WORLD_SIZE);

	ShipObj.getCameraLocation(CamObj);

	ShipObj.Refresh();

	//Grid();

	glutSwapBuffers();

	/*
	if (value == 1)
		CamObj.eyeStore = 'x';
	else if (value == 2)
		CamObj.eyeStore = 'y';
	else if (value == 3)
		CamObj.eyeStore = 'z';
	else if (value == 4)
		 if (FPSmode)
			 FPSmode = false;
		else 
			 FPSmode = true;
			 */
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			mouseLeftDown = true;
		else if (button == GLUT_RIGHT_BUTTON)
			mouseRightDown = true;
	}
	else if (state == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
			mouseLeftDown = false;
		else if (button == GLUT_RIGHT_BUTTON)
			mouseRightDown = false;
	}
}

void MouseMotion(int x, int y)
{
	static bool just_warped = false;

	if (just_warped){
		just_warped = false;
		return;
	}
	
	if(FPSmode){
		int dx = x - viewportWidth / 2;
		int dy = y - viewportHeight / 2;

		if (dx)
			CamObj.RotateYaw(rotationSpeed * dx);
		if (dy)
			CamObj.RotatePitch(rotationSpeed * dy);

		glutWarpPointer(viewportWidth / 2, viewportHeight / 2);

		just_warped = true;
			
	}

}

void Keyboard(unsigned char key, int x, int y)
{
	// if escape is pressed quits the program
	if (key == 27){
		glutDestroyWindow(window);
		exit(0);
	}
	// if space is pressed
	if(key == 'f'){
		FPSmode = !FPSmode; // toggles fps
		
		// if fpsmode gets rid of the cursor and sets viewport(??)
		if(FPSmode){
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(viewportWidth / 2, viewportHeight / 2);
		}
		else // gets cursor of fpsmode is toggles off
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	}

	// checks if shift is down
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT){
		shiftDown = true;
	}
	else 
		shiftDown = false;



	/*  IMPORTANT FOR CAMERA ROTATION
	// if fpsmode if toggles off starts movement
	if (!FPSmode){
		CamObj.getInput(key, x, y);
		return;
	}
	*/
	// sets the key pressed to true.
	_key[key] = true;

}

void KeyboardUp(unsigned char key, int x, int y)
{
	_key[key] = false;
}

void Idle()
{
	if (FPSmode)
		Display();
	else
		CamObj.moveCamera();
}

void Menu(int num)
{
	if (num == 0)
	{
		glutDestroyWindow(window);
		exit(0);
	}
	else value = num;
}


void createMenu()
{
	menuId = glutCreateMenu(Menu);
	glutAddMenuEntry("Exit", 0);
	glutAddMenuEntry("Rotate X", 1);
	glutAddMenuEntry("Rotate Y", 2);
	glutAddMenuEntry("Rotate Z", 3);
	glutAddMenuEntry("FPS mode", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1600, 900);
	window = glutCreateWindow("Final Project");
	glutInitWindowPosition(0, 0);

	glutIgnoreKeyRepeat(1);

	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	createMenu();

	glutIdleFunc(Idle);
	init();

	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	return 0;
}