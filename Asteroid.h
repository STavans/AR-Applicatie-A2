#pragma once

#include <opencv2/core/types.hpp>
#include "Vizor.h"


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
	Asteroid(int diameter, int x, int y, int z, int rotation, int reward);
	bool shotCheck(Vizor vizor, Asteroid asteroid);

};