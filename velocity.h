#pragma once
/***********************************************************************
* Header File:
*    Velocity : The vehicle's vector of speed and direction, broken into
*    x and y components.
* Author:
*    Ben Bragg
* Summary:
*    Has an x component and a y component that says how many units the
*    parent object will be displaced the following frame.
************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

class Velocity
{
private:
	float dx;
	float dy;

public:
	Velocity() { dx = 0; dy = 0; } // default constructor: zero out vel.
	float getDx();
	float getDy();

	void setDx(float dx);
	void setDy(float dy);
	void addXVelocity(float dx);
	void addYVelocity(float dy);
};

#endif // !VELOCITY_H
