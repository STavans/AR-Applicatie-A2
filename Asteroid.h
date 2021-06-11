#pragma once

#include <opencv2/core/types.hpp>
#include "Vizor.h"
#include "Coordinate.h"


bool shotCheck(Vizor, Asteroid);


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