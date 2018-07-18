#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "uiDraw.h"
#include <vector>
#include <cmath>
#include "UFO.h"

// Define the following classes here:
//   Rock
class Rock : public UFO
{
	public:
		Rock() : UFO(), angle(0)
		{
			position.setX(random(-150, 150));
			position.setY(random(-150, 150));
		}

		void advance()
		{
			position.addX(velocity.getDx());
			position.addY(velocity.getDy());
			angle += rotationSpeed;
		}

		virtual std::vector<Rock*> killRock() 
		{ 
			alive = false; 
			std::vector<Rock*> rockFrags;
			return rockFrags; 
		}

	protected:
		double angle;
		double rotationSpeed;
};
//   BigRock
class BigRock : public Rock
{
	public:
		BigRock() : Rock() { rotationSpeed = BIG_ROCK_SPIN; size = BIG_ROCK_SIZE; }
		BigRock(Point location, Velocity velocity) : Rock() 
		{ 
			position = location; 
			this->velocity = velocity;
			rotationSpeed = BIG_ROCK_SPIN;
			size = BIG_ROCK_SIZE;
		}

		std::vector<Rock*> killRock();
		void draw() { drawLargeAsteroid(position, angle); }
};

//   MediumRock
class MidRock : public Rock
{
public:
	MidRock() : Rock() { rotationSpeed = MEDIUM_ROCK_SPIN; size = MEDIUM_ROCK_SIZE; }
	MidRock(Point location, Velocity velocity)
	{
		position = location;
		this->velocity = velocity;
		rotationSpeed = MEDIUM_ROCK_SPIN;
		size = MEDIUM_ROCK_SIZE;
	}

	std::vector<Rock*> killRock();
	void draw() { drawMediumAsteroid(position, angle); }
};

//   SmallRock
class LittleRock : public Rock
{
public:
	LittleRock() : Rock() { rotationSpeed = SMALL_ROCK_SPIN; size = SMALL_ROCK_SIZE; }
	LittleRock(Point location, Velocity velocity)
	{
		position = location;
		this->velocity = velocity;
		rotationSpeed = SMALL_ROCK_SPIN;
		size = SMALL_ROCK_SIZE;
	}

	void draw() { drawSmallAsteroid(position, angle); }
};


#endif /* rocks_h */
