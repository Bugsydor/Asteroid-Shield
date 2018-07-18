#pragma once
#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40
#define _USE_MATH_DEFINES

#include <cmath>
#include "UFO.h"
#include "uiDraw.h"

// Put your Bullet class here
class Bullet : public UFO
{
	public:
		Bullet() : UFO(), lifetime(0) {}

		void fire(Point position, float angle, Velocity oldVelocity);

		void advance()
		{
			position.addX(velocity.getDx());
			position.addY(velocity.getDy());
			if (lifetime > BULLET_LIFE)
			{
				kill();
			}
			lifetime++;
		}

		void draw() { drawDot(position); }

	private:
		int lifetime;
};



#endif /* bullet_h */
