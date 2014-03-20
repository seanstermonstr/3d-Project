#include "collision.h"

void Collision::Init()
{
	
}


void Collision::Refresh()
{
	try
	{
		if(checkOverlap())
			throw 0;
		else
			return;
	}
	catch (int e)
	{
		endScreen(e);
	}
}

bool Collision::checkOverlap()
{
	return false;
}

void Collision::getPtrInfo(Camera *Cam, Solar_System *Sol)
{
	
	CamObj = Cam;
	SolObj = Sol;
	
}


void Collision::endScreen(int e)
{
	std::cout<<"Exeption "<< e << "was thrown.\n";

	if (e == 0)
	{
		int x;
		std::cout <<"Thanks for playing! Press any key to exit.";
		std::cin >> x;

		exit(0);
	}

}