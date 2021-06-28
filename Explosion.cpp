#include "Explosion.h"

Explosion::Explosion() {
}

/*
* Second constructor used for the attributes of the explosion
*/
Explosion::Explosion(int x, int y, int z, int duration) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->Duration = duration;
}

