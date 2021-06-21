#pragma once

#include <opencv2/core/types.hpp>
#include "Vizor.h"
#include "Coordinate.h"
#include "Asteroid.h"

/*
* Asteroid class with all attributes and functions
*/
class Asteroid {

public:
	int diameter;
	int x;
	int y;
	int z;
	int rotation;
	int reward;
	Asteroid();
	Asteroid(int diameter, int z, int rotation, int reward, Coordinate spawnPoint);
	bool shotCheck(Vizor vizor, Asteroid asteroid);

};

/*
* Checks if a asteroid is shot
*/
bool shotCheck(Vizor, Asteroid*);

