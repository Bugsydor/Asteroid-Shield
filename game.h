/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "bullet.h"
#include "point.h"
#include "velocity.h"
#include "rocks.h"
#include "ship.h"
#include "uiDraw.h"
#include "uiInteract.h"

class Game
{
	public:
		Game(Point tl, Point br) : topLeft(tl), bottomRight(br), score(0), level(1),
		clearTimer(0), shieldCharging(false) { spawnRocks(); }

		void advance();
		void handleInput(const Interface & ui);
		void draw(const Interface & ui);

		void spawnRocks()
		{
			for (int i = 0; i < level + 4; i++)
			{
				createBigRock();
			}
		}

	private:
		// member variables
		Point topLeft;
		Point bottomRight;
		std::vector<Rock*> rocks;
		std::vector<Bullet> bullets;
		Ship ship;
		int level;
		int score;
		int rechargeScore;// the score at which the ship's shield recharges
		bool shieldCharging;
		int clearTimer;// time between level clear and level up

	// private methods
		// methods for advancing various pieces of the game
		void advanceBullets();
		void advanceRocks();
		void levelUp();
		void levelEnd();
		void shieldChargeCheck();

		// methods for calling things into existence
		void createBigRock();

		// methods for finding things' locations
		bool Game::isOnScreen(const Point & point);
		float getClosestDistance(UFO &obj1, UFO &obj2);
		void handleCollisions();

		// for cleaning up dead stuff
		void cleanUpZombies();
};

#endif /* GAME_H */
