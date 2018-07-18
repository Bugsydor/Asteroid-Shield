#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#define _USE_MATH_DEFINES
#define M_PI       3.14159265358979323846

#include "uiDraw.h"
#include <cmath>
#include "UFO.h"

// Put your Ship class here
class Ship : public UFO
{
	public:
		Ship() : angle(0), UFO(), thrusting(false)
		{
			position.setX(0); 
			position.setY(0); 
			size = SHIP_SIZE; 
			turnInvincible();
			shieldUp();
		}

		void turnLeft() { angle += ROTATE_AMOUNT; }
		void turnRight() { angle -= ROTATE_AMOUNT; }
		void thrust() 
		{ 
			velocity.addYVelocity(THRUST_AMOUNT * (cos(M_PI / 180.0 * angle)));
			velocity.addXVelocity(THRUST_AMOUNT * (-sin(M_PI / 180.0 * angle)));
		}

		double getAngle() { return angle; }

		// invincibility shenanigans
		bool isInvincible() { return invincible; }
		void turnInvincible() { invincible = true; invincibilityFrames = 50; }

		// shield stuff
		bool isShielded() { return shielded; }
		void shieldUp() { shielded = true; }

		void advance() 
		{ 
			position.addX(velocity.getDx()); 
			position.addY(velocity.getDy());

			// decrement invincibility frames, and turn invinc. off if they hit 0
			if (isInvincible())
			{
				if (invincibilityFrames-- <= 0)
					invincible = false;
			}
		}

		// special kill command that takes into account shield and invincibility
		void kill()
		{
			if (!invincible)
			{
				if (shielded)
				{
					shielded = false;
					turnInvincible();
				}
				else
					alive = false;
			}
		}

		void draw() 
		{ 
			if (isAlive())
			{
				drawShip(position, angle, thrusting);
				if (shielded)
					drawCircle(position, SHIP_SIZE);
			}
		}

	private:
		double angle;
		bool thrusting;
		bool shielded;
		bool invincible;
		int invincibilityFrames;
};

#endif /* ship_h */
