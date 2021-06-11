#include "Asteroid.h"
#include "Vizor.h"

bool shotCheck(Vizor vizor, Asteroid asteroid) {
    int distSq = (asteroid.x - vizor.x) * (asteroid.x - vizor.x) +
        (asteroid.y - vizor.y) * (asteroid.y - vizor.y);
    int radSumSq = (asteroid.diameter + vizor.diameter) * (asteroid.diameter + vizor.diameter);
 if (distSq > radSumSq)
        return false;
    else
        return true;
}

Asteroid::Asteroid() {
}

Asteroid::Asteroid(int diameter, int x, int y, int z, int rotation, int reward) {
	this->diameter = diameter;
	this->x = x;
	this->y = y;
    this->reward = reward;
}

