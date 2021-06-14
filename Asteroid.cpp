#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"

/*
* Checks if the vizor and asteroid align
*/
bool shotCheck(Vizor vizor, Asteroid asteroid) {
    int distSq = (asteroid.x - vizor.x) * (asteroid.x - vizor.x) +
        (asteroid.y - vizor.y) * (asteroid.y - vizor.y);
    int radSumSq = (asteroid.diameter + vizor.diameter) * (asteroid.diameter + vizor.diameter);
 if (distSq > radSumSq)
        return false;
    else
        return true;
}

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

