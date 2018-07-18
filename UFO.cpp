#include "UFO.h"


// Put your FlyingObject method bodies here
void UFO::wrap()
{
	// wrap RtL
	if (position.getX() > 210)
		position.setX(-200);
	// wrap LtR
	if (position.getX() < -210)
		position.setX(200);
	// wrap TtB
	if (position.getY() > 210)
		position.setY(-200);
	// wrap BtT
	if (position.getY() < -210)
		position.setY(200);
}