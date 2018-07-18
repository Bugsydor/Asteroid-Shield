#include "velocity.h"

// returns the horizontal velocity component
float Velocity::getDx()
{
	return dx;
}

// returns the vertical velocity component
float Velocity::getDy()
{
	return dy;
}

// sets the horizontal velocity to the given number
void Velocity::setDx(float dx)
{
	this->dx = dx;
}

// sets the vertical velocity to the given number
void Velocity::setDy(float dy)
{
	this->dy = dy;
}

// adds a given number to the horizontal velocity
void Velocity::addXVelocity(float dx)
{
	this->dx += dx;
}

// adds a given number to the vertical velocity
void Velocity::addYVelocity(float dy)
{
	this->dy += dy;
}
