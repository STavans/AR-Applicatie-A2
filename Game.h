#include <iostream>
#include <Windows.h>
#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"
#include "SpawnPoints.cpp"
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

	const int StartScreen = 1;
	const int GameScreen = 2;
	const int EndScreen = 3;

	void startUp();
	void openGameOverScreen();
	void spawnAsteroid();
	void openGameOverScreen();
	void openGameScreen();
	void openStartScreen();
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
	void startGame();
	bool readyToReset();
	void gameCheck();
	void ResetAll();
	void updateAsteroidsLocation();
};