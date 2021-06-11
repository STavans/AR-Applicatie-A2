#pragma once

#include <opencv2/core/types.hpp>

class Vizor {

public: 
	int diameter;
	int x;
	int y;
	Vizor();
	Vizor(int left, int x, int y);

};