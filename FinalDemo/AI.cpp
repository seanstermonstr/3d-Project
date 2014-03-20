#include "AI.h"

void ship::Init(int numShips)
{
	CreateTexture(texture, "asteroid.tga", 0);
	//astrPtr = new asteroid[numShips];
	astrSize = 12;
	radius = 24;
	slices = 10;
	stacks = 10;
	srand(time(NULL));

	astr.resize(numShips);

	for (int i = 0; i < numShips; i++)
	{
		newShip(astr[i]);
	}
}

//randomizes the locations of the asteroids
void ship::newShip(asteroid &astr)
{
	int temp;

	//srand((unsigned)time(0));
	temp = 0 + (rand() % 1);

	if (temp = 0)
		astr.eyex = 0 + ((float)rand() / 150.0);
	else 
		astr.eyex = (0 + ((float)rand() / 150.0)) - 150;

	temp = 0 + (rand() % 1);

	if (temp = 0)
		astr.eyey = 0 + ((float)rand() / 150);
	else 
		astr.eyey = (0 + ((float)rand() / 150)) - 150;

	temp = 0 + (rand() % 1);

	if (temp = 0)
		astr.eyez = 0 + ((float)rand() / 150);
	else 
		astr.eyez = (0 + ((float)rand() / 150)) - 150;



	astr.collected = false;

	//srand (time(NULL));
	//return astr;
}


// handles the collision detection
void ship::collision(asteroid &astr)
{
	// gets the collision vector
	Col.vectorX = astr.eyex - cameraX;
	Col.vectorY = astr.eyey - cameraY;
	Col.vectorZ = astr.eyez - cameraZ;
	
	// gets the distance
	Col.distance = ((Col.vectorX * Col.vectorX) +
				    (Col.vectorY * Col.vectorY) +
				    (Col.vectorZ * Col.vectorZ));

	if (Col.distance <= radius + cameraR)
		astr.collected = true;
}

// draws the asteroids
void ship::Refresh()
{
	

	for (int i = 0; i < astr.size(); i++)
	{
		collision(astr[i]);

		if (!astr[i].collected){
			//glPushMatrix();
			glTranslated(astr[i].eyex, astr[i].eyey, astr[i].eyez);
			texturedCube(texture[0], astrSize);
			glColor3f(1, 1, 1);
			glutSolidSphere(radius, slices, stacks);
			//glPopMatrix();
			//glutSolidCube(astrSize);
		}
	}
}

void ship::locationRefresh(int i)
{
	
}

//gets camera info for collision function
void ship::getCameraLocation(Camera &CamObj)
{
	cameraX = CamObj.eyex;
	cameraY = CamObj.eyey;
	cameraZ = CamObj.eyez;
	cameraR = CamObj.radius;

}

void ship::Move(float incr)
{
	//float lx = 
}

//takes care of texture mapping cubes
void ship::texturedCube(GLuint value, float size)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, value);

    glBegin(GL_QUADS);
		// Front Face, red
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size,  size);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size,  size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size,  size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size,  size);
		// Back Face, green
		//glBindTexture(GL_TEXTURE_2D, g_TexturesArray[1]);
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size, -size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size, -size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size, -size);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size, -size);
		// Top Face, blue
		//glBindTexture(GL_TEXTURE_2D, g_TexturesArray[2]);
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size, -size);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size,  size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size,  size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size, -size);
		// Bottom Face, yellow
		//glBindTexture(GL_TEXTURE_2D, g_TexturesArray[3]);
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size, -size);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size, -size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size,  size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size,  size);
		// Right face, cyan
		//glBindTexture(GL_TEXTURE_2D, g_TexturesArray[4]);
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size, -size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size, -size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size,  size,  size);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f( size, -size,  size);
		// Left Face, magenta
		//glBindTexture(GL_TEXTURE_2D, g_TexturesArray[5]);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size, -size);
		glTexCoord2f(1.0f, 0.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size, -size,  size);
		glTexCoord2f(1.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size,  size);
		glTexCoord2f(0.0f, 1.0f); glColor3f(0.5f, 1.0f, .5f); glVertex3f(-size,  size, -size);
    glEnd();
    glPopMatrix();
	glFlush();
	glDisable(GL_TEXTURE_2D);
}