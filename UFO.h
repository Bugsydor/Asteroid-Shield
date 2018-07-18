#pragma once
/*************************************************************
* Header File: UFO.h
* Author: Ben Bragg
*
* Description: Short for Undifferentiated Flying Object.Parent
* class for all flying objects (i.e. bullets, birds)
*************************************************************/

//#define _USE_MATH_DEFINES

//#include <cmath>
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class UFO
{
public:
	UFO() : alive(true) {}
	~UFO();

	// returns the object's position
	Point getPoint() { return position; }

	// return the object's velocity
	Velocity getVelocity() { return velocity; }

	// return the object's size
	double getSize() { return size; }

	// return whether the object is alive or not
	bool isAlive() { return alive; }

	// set the object's position
	void setPoint(Point position) { this->position = position; }

	// set the object's velocity
	void setVelocity(Velocity velocity) { this->velocity = velocity; }

	// kill the object
	virtual void kill() { alive = false; }

	// move the object
	virtual void advance() = 0;

	// around the world
	void wrap();

	// draw the object
	virtual void draw() = 0;

protected:
	bool alive;
	Point position;
	Velocity velocity;
	double size;
};

inline UFO::~UFO()
{
}