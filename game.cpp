/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
using namespace std;


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(UFO &obj1, UFO &obj2) 
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

// step through the game state, check if things have collided this frame, and resolve any collisions
void Game::handleCollisions()
{
	// let's start with bullets vs rocks
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < rocks.size(); j++)
		{
			if (getClosestDistance(bullets[i], *(rocks[j])) < rocks[j]->getSize())
			{
				bullets[i].kill();
				score += level;
				std::vector<Rock*> rockFrags = rocks[j]->killRock();
				for (int k = 0; k < rockFrags.size(); k++)
					rocks.push_back(rockFrags[k]);
			}
		}
	}

	// now let's blow up the ship when it hits a rock
	for (int i = 0; i < rocks.size(); i++)
	{
		if (getClosestDistance(ship, *(rocks[i])) < (rocks[i]->getSize() + ship.getSize()))
			ship.kill();
	}
}


void Game::advance()
{
	advanceBullets();
	advanceRocks();
	ship.advance();
	// check if ship needs to wrap, then maybe wrap it.
	if (!isOnScreen(ship.getPoint()))
		ship.wrap();

	handleCollisions();
	cleanUpZombies();
	shieldChargeCheck();

	levelEnd();
}

void Game::draw(const Interface & ui)
{
	ship.draw();

	// draw the rocks
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->draw();
		}
	}

	// draw the bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	// draw the level name and number in the top-left corner
	Point nameLocation;
	Point numberLocation;
	nameLocation.setX(topLeft.getX() + 5);
	nameLocation.setY(topLeft.getY() - 15);
	numberLocation.setX(topLeft.getX() + 43);
	numberLocation.setY(topLeft.getY() - 5);

	drawText(nameLocation, "Level ");
	drawNumber(numberLocation, level);

	// draw the score right below it
	Point scoreLocation;
	scoreLocation.setX(topLeft.getX() + 5);
	scoreLocation.setY(topLeft.getY() - 25);

	drawNumber(scoreLocation, score);
}

void Game::handleInput(const Interface & ui)
{
	if (ship.isAlive())
	{
		// turn the ship left
		if (ui.isLeft())
			ship.turnLeft();

		// turn the ship right
		if (ui.isRight())
			ship.turnRight();

		// apply thrust
		if (ui.isUp())
			ship.thrust();

		// shoot bullet
		if (ui.isSpace())
		{
			Bullet newBullet;
			newBullet.fire(ship.getPoint(), ship.getAngle(), ship.getVelocity());

			bullets.push_back(newBullet);
		}
	}
	else
		drawText(Point(), "Game Over");
}

// move the rocks
void Game::advanceRocks()
{
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i]->isAlive())
		{
			rocks[i]->advance();
			rocks[i]->wrap();
		}
	}
}

// move the bullets
void Game::advanceBullets()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].advance();
			bullets[i].wrap();
		}
	}
}

void Game::createBigRock()
{
	// create a velocity object with a random direction
	Velocity velocity;
	double angle = random(0, 360);
	velocity.setDx(1 * (-sin(M_PI / 180.0 * angle)));
	velocity.setDy(1 * (cos(M_PI / 180.0 * angle)));

	// create a random point on-screen to start at
	Point location;
	location.setX(random(-150, 150));
	location.setY(random(-150, 150));

	Rock* newRock = new BigRock(location, velocity);
	rocks.push_back(newRock);
}

// check if a thing is off-screen

#define OFF_SCREEN_BORDER_AMOUNT 10

bool Game::isOnScreen(const Point & point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

void Game::cleanUpZombies()
{
	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();
	while (bulletIt != bullets.end())
	{
		Bullet bullet = *bulletIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!bullet.isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...


			// remove from list and advance
			bulletIt = bullets.erase(bulletIt);
		}
		else
		{
			bulletIt++; // advance
		}
	}

	// Look for dead rocks
	vector<Rock*>::iterator rockIt = rocks.begin();
	while (rockIt != rocks.end())
	{
		Rock* pRock = *rockIt;
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (!pRock->isAlive())
		{
			// If we had a list of pointers, we would need to delete the memory here...
			delete pRock;

			// remove from list and advance
			rockIt = (rocks).erase(rockIt);
		}
		else
		{
			rockIt++; // advance
		}
	}
}

void Game::levelUp()
{
	std::cout << clearTimer << endl;
	clearTimer = 0;
	std::cout << clearTimer << endl;
	level++;
	std::cout << level << endl;

	ship.turnInvincible();
	std::cout << "invinc.\n";
	ship.shieldUp();
	std::cout << "shieldUp\n";
	spawnRocks();
	std::cout << "Rock On.\n";
}

// check if the level should end, and set up the next level if needed.
void Game::levelEnd()
{
	if (rocks.size() == 0 && clearTimer >= 100)
	{
		levelUp();
	}
	else if (rocks.size() == 0 && clearTimer < 100)
	{
		drawText(Point(), "Level Clear!");
		clearTimer++;
	}
}

// check whether the shield just went down, is up, or has been down
void Game::shieldChargeCheck()
{
	// if the shield is gone, but not yet recharging, fix that.
	if (ship.isShielded() == false && shieldCharging == false)
	{
		rechargeScore = score + 10 * level;
		shieldCharging = true;
	}
	
	// if the shield is recharging, and the rechargeScore has been reached,
	// re-up the shield.
	if (ship.isShielded() == false && shieldCharging == true && score >= rechargeScore)
	{
		ship.shieldUp();
		shieldCharging = false;
	}
}