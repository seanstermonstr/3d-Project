/***********************************************
*                                              *
*         Bruce's GLUT OpenGL Basecode         *
*  Specially made for Nehe's Gamedev Website   *
*            http://nehe.gamedev.net           *
*                April 2003                    *
*                                              *
************************************************
* Project Information:
*
* Author: Bruce "Sinner" Barrera
* E-mail: sinner@opengl.com.br
* Date  : around April 2003 :-)
* Glut Version: 3.7.6
*
* Very special thanks to all people who
* contributed with any online tutors or
* help files. Keep coding!
*
***********************************************/

#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "frames.h"
#include "tga.h"
#include <GL/glut.h>

#define ONE_SECOND 	 1	// one second
#define MAX_TEXTURES 	 1  	// max textures displayed

/* creates a enum type for mouse buttons */
enum {
    BUTTON_LEFT = 0,
    BUTTON_RIGHT,
    BUTTON_LEFT_TRANSLATE,
};

/* set global variables */
int mButton = -1;
int mOldY, mOldX;

/* vectors that makes the rotation and translation of the cube */
float eye[3] = {0.0f, 0.0f, 7.0f};
float rot[3] = {45.0f, 45.0f, 0.0f};

const int ESC = 27;

int wireframe = 0;

/* windows size and position constants */
const int GL_WIN_WIDTH = 640;
const int GL_WIN_HEIGHT = 480;
const int GL_WIN_INITIAL_X = 0;
const int GL_WIN_INITIAL_Y = 0;

/* array to hold texture handles */
GLuint g_TexturesArray[MAX_TEXTURES];


//------------------------------------------------------------------------
// Window resize function
//------------------------------------------------------------------------
void glutResize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
      /* modify this line to change perspective values */
	gluPerspective(45.0, (float)width/(float)height, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//------------------------------------------------------------------------
// Function that handles keyboard inputs
//------------------------------------------------------------------------
void glutKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case ESC:
			exit(0);
		case 'W':
		case 'w':
		    wireframe = !wireframe;
	}
}

//------------------------------------------------------------------------
// If rotation angle is greater of 360 or lesser than -360,
// resets it back to zero.
//------------------------------------------------------------------------
void clamp(float *v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0;
}

//------------------------------------------------------------------------
// Moves the screen based on mouse pressed button
//------------------------------------------------------------------------
void glutMotion(int x, int y)
{
    if (mButton == BUTTON_LEFT)
    {
        /* rotates screen */
        rot[0] -= (mOldY - y);
        rot[1] -= (mOldX - x);
        clamp (rot);
    }
	else if (mButton == BUTTON_RIGHT)
    {
        /*
           translate the screen, z axis
           gives the idea of zooming in and out 
        */        
        eye[2] -= (mOldY - y) * 0.05f; // here I multiply by a 0.2 factor to 
                                      // slow down the zoom
        clamp (rot);
    } 
    else if (mButton == BUTTON_LEFT_TRANSLATE)
    {
        eye[0] += (mOldX - x) * 0.01f;
        eye[1] -= (mOldY - y) * 0.01f;
        clamp (rot);
    }

    mOldX = x;
    mOldY = y;
}

//------------------------------------------------------------------------
// Function that handles mouse input
//------------------------------------------------------------------------
void glutMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        mOldX = x;
        mOldY = y;
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
                {
                   mButton = BUTTON_LEFT_TRANSLATE;
                   break;
                } else
                {
                   mButton = BUTTON_LEFT;
                   break;
                }
            case GLUT_RIGHT_BUTTON:
                mButton = BUTTON_RIGHT;
                break;
        }
    } else if (state == GLUT_UP)
      mButton = -1;
}

//------------------------------------------------------------------------
// The glut's menu callback function. Called every time an option is selected
//------------------------------------------------------------------------
void glutMenu(int value)
{
	switch (value)
	{
		case 1:
			glutFullScreen();
			return;

		case 2:
			exit(0);
	}
}

//------------------------------------------------------------------------
// Function that handles special keyboards input (SHIFT, CTRL, ALT)
//------------------------------------------------------------------------
void glutSpecial(int value, int x, int y)
{
    switch (value)
    {
        case GLUT_KEY_F1:
                glutFullScreen();
                return;
    }
}

//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//vvvvvvvvvvvvvvvvvvvvvv ATTENTION HERE!!! vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
//************************************************************************
// The draw function. Replaces code listed here for your own drawing code.
// For demo of the framework i drawed i simple cube that can be freely
// rotated with mouse buttons.
//************************************************************************
//vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void glutDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glPushMatrix();

    /* translate camera to the coordinates provided by eye array */
    glTranslatef (-eye[0], -eye[1], -eye[2]);

    /* rotates the screen by the angles provided by rot array */
    glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
    glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rot[2], 0.0f, 0.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, g_TexturesArray[0]);

    glBegin(GL_QUADS);
		// Front Face, red
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(1.0f, 0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.7f, 0.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.7f, 0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face, green
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.0f, 0.7f, 0.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.0f, 0.7f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face, blue
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.0f, 0.0f, 0.7f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.0f, 0.0f, 0.7f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face, yellow
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(1.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(1.0f, 1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.7f, 0.7f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.7f, 0.7f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face, cyan
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.0f, 1.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.0f, 1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.0f, 0.7f, 0.7f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.0f, 0.7f, 0.7f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face, magenta
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.7f, 0.0f, 0.7f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.7f, 0.0f, 0.7f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

    // here I increment y-axis value to give a rotating animation to the cube
    // greater values here gives more speed to the animation
    rot[1] += 0.05;
}

///vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
/// The code here can be freely altered too. It's mainly designed to set
/// OpenGl's initial value and configuration.
///vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
void InitializeOGL()
{
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

	// enable texture and binds a texture to the first element of the array
    glEnable(GL_TEXTURE_2D);	
    CreateTexture(g_TexturesArray,"logo.tga",0);

    return;
}

//------------------------------------------------------------------------
//   It's the main application function. Note the clean code you can
//   obtain using he GLUT library. No calls to dark windows API
//   functions with many obscure parameters list. =)
//------------------------------------------------------------------------
int main(int argc, char** argv)
{
    /*
        Glut's initialization code. Set window's size and type of display.
        Window size is put half the 800x600 resolution as defined by above
	constants. The windows is positioned at the top leftmost area of
	the screen.
    */
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA | GLUT_MULTISAMPLE );
    glutInitWindowPosition( GL_WIN_INITIAL_X, GL_WIN_INITIAL_Y );
    glutInitWindowSize( GL_WIN_WIDTH, GL_WIN_HEIGHT );
    glutInit( &argc, argv );

    glutCreateWindow("glutbasecode");

    /*
       The function below are called when the respective event
       is triggered. Very simple, isn't it?
    */
    glutReshapeFunc(glutResize);       // called every time  the screen is resized
    glutDisplayFunc(glutDisplay);      // called when window needs to be redisplayed
    glutIdleFunc(glutDisplay);         // called whenever the application is idle
    glutKeyboardFunc(glutKeyboard);    // called when the application receives a input from the keyboard
    glutMouseFunc(glutMouse);          // called when the application receives a input from the mouse
    glutMotionFunc(glutMotion);        // called when the mouse moves over the screen with one of this button pressed
    glutSpecialFunc(glutSpecial);      // called when a special key is pressed like SHIFT

    /*
        Do any lighting, material, alpha, etc initialization or
        configuration here.
    */
    InitializeOGL();

    /*
        Creates a menu attached to the mouses middle button
        the menu here consists in two options, one to toggle
        fullscreen mode and another for exiting the application.
    */
	glutCreateMenu(glutMenu);
	glutAddMenuEntry("Full Screen", 1);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

    /*
       Application's main loop. All the above functions
	 are called whe the respective events are triggered
    */
	glutMainLoop();

	return 0;
}

//---------------------------------------------------------------------------
//    Special Notes: Look the above program and realize how simple it was
//    to write a full working OpenGL application! Most of the
//    ready-to-work codes in internet are big ones with many Windows API
//    calls and so on. Another advantage of this code is that with the right
//    implementation it can be REALLY ported to others OS with ease.
//    Should compile and work with Mesa implementation without problems!
//    I tested it a lot in SuSE Linux 8.2 and of course Windows XP.
//---------------------------------------------------------------------------

