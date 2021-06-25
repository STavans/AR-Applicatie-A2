#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"

/*
* Basic constructor
*/
Asteroid::Asteroid() {
}

/*
* Second constructor used for the attributes of the asteroid
*/
Asteroid::Asteroid(int diameter, int z, int rotation, int reward, Coordinate spawnPoint) {
	this->diameter = diameter;
	this->x = spawnPoint.x;
	this->y = spawnPoint.y;
    this->z = z;
    this->reward = reward;
}

