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

const int StartScreen = 1;
const int GameScreen = 2;
const int EndScreen = 3;

void stateMachine();
void spawnAsteroid();
void openGameScreen();
void explodeAsteroid(Asteroid* roid);
void checkAsteroids();
bool isOutTime();
void checkSpawnable();
void endGame();
Coordinate generateRandomSpawn();
void mainLoop();
bool enterButtonPressed();
void startGame();
void gamePlay();
bool readyToReset();
void gameCheck();
void ResetAll();
void updateAsteroidsLocation();

void runStartScreenState();
void runGameScreenState();
void runEndScreenState();