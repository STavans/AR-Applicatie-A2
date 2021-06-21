#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"

/*
* Checks if the vizor and asteroid align
*/
bool shotCheck(Vizor vizor, Asteroid* asteroid) {
    Asteroid roid = *asteroid;
    int distSq = (roid.x - vizor.x) * (roid.x - vizor.x) +
        (roid.y - vizor.y) * (roid.y - vizor.y);
    int radSumSq = (roid.diameter + vizor.diameter) * (roid.diameter + vizor.diameter);
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

