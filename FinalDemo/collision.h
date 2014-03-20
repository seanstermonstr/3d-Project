#ifndef COLLISION_H
#define COLLISION_H

#include "SolarSystem.h"
#include "camera.h"


//This class will receive ptrs to all required objects, and 
//return if there is a collision.  

class Collision {

public:

	Collision::Collision(){ Init(); }
	~Collision();

	void Init();

	void getPtrInfo(Camera *Cam, Solar_System *Sol);
	bool checkOverlap();
	void Refresh();
	void endScreen(int e);


private:

	Camera *CamObj;
	Solar_System *SolObj;

};


#endif
