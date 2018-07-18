#include "bullet.h"


// Put your bullet methods here

void Bullet::fire(Point position, float angle, Velocity oldVelocity)
{
	this->position = position;

	velocity.setDx(BULLET_SPEED * (-sin(M_PI / 180.0 * angle)) + oldVelocity.getDx());
	velocity.setDy(BULLET_SPEED * (cos(M_PI / 180.0 * angle)) + oldVelocity.getDy());
}