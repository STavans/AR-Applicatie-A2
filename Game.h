#include <iostream>
#include <Windows.h>
#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"
#include "Timer.h"
#include "Global.h"
#include "Vision.h"
#include <cmath>
#include <vector>
#include <algorithm>

class Game {

public:
	Vizor leftVizor, rightVizor;

	int score;
	int state;

	std::vector<Asteroid*> asteroidList;

	void startUp();
	void spawnAsteroid();
	void openGameScreen();
	void explodeAsteroid(Asteroid* roid);
	void updateLeftVizor(Coordinate left);
	void updateRightVizor(Coordinate right);
	void checkAsteroids();
	bool isOutTime();
	void checkSpawnable();
	void endGame();
	Coordinate generateRandomSpawn();
	void mainLoop();
	void stateLoopSwitch();
	bool enterButtonPressed();
	void startGame();
	void gamePlay();
	bool readyToReset();
	void gameCheck();
	void ResetAll();
	void updateAsteroidsLocation();
};