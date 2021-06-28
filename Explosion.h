#pragma once
class Explosion {

public:
	int x;
	int y;
	int z;

	int Duration;
	Explosion();
	Explosion(int x, int y, int z, int duration);
};