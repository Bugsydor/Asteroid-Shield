#include "rocks.h"

// Put your Rock methods here
std::vector<Rock*> BigRock::killRock()
{
	// create a vector of rock fragments to pass back to the main rock vector
	std::vector<Rock*> rockFrags;
	Velocity newVelocity;
	newVelocity = velocity;
	Rock* newRock;

	alive = false;

	// upward midRock
	newVelocity.setDy(velocity.getDy() - 1);
	newRock = new MidRock(position, newVelocity);
	rockFrags.push_back(newRock);

	// downward midRock
	newVelocity.setDy(velocity.getDy() + 1);
	newRock = new MidRock(position, newVelocity);
	rockFrags.push_back(newRock);

	// rightward littleRock
	newVelocity.setDy(velocity.getDy());
	newVelocity.setDx(velocity.getDx() + 1);
	newRock = new LittleRock(position, newVelocity);
	rockFrags.push_back(newRock);

	return rockFrags;
}

std::vector<Rock*> MidRock::killRock()
{
	// create a vector of rock fragments to pass back to the main rock vector
	std::vector<Rock*> rockFrags;
	Velocity newVelocity;
	newVelocity = velocity;
	Rock* newRock;

	alive = false;

	// rightward LittleRock
	newVelocity.setDx(velocity.getDx() + 3);
	newRock = new LittleRock(position, newVelocity);
	rockFrags.push_back(newRock);

	// leftward LittleRock
	newVelocity.setDx(velocity.getDx() - 3);
	newRock = new LittleRock(position, newVelocity);
	rockFrags.push_back(newRock);

	return rockFrags;
}