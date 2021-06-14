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

//-----------------------Vars-------------------
Vizor leftVizor, rightVizor;

int score;
int state;

std::vector<Asteroid*> asteroidList;
Coordinate* SpawnPoints;

const int StartScreen = 1;
const int GameScreen = 2;
const int EndScreen = 3;

//--------------

void Startup() {
	state = StartScreen;
	openStartScreen();

	// make an array of spawnpoints: int are screen parameters, need to change to stand values
	SpawnPoints = RandomSpawnPoints(1000, 1000);
	mainLoop();
}

void mainLoop(){
	while (true)
	{
		stateLoopSwitch();
	}
}

void gamePlay() {
	CVView();
	Coordinate left = getLeftVizor();
	Coordinate right = getRightVizor();
	updateLeftVizor(left);
	updateRightVizor(right);
}

void stateLoopSwitch() {
	switch (state)
	{
		case StartScreen:
			if (enterButtonPressed())
			{
				startGame();
			}
			break;
		case GameScreen:
			gamePlay();
			gameCheck();
			increaseSpawn(true);
			break;
		case EndScreen:
			if (readyToReset())
			{
				openStartScreen();
				ResetAll();
			}
			break;
	default:
		break;
	}
}

bool enterButtonPressed() {
	if (GetAsyncKeyState(VK_RETURN))
	{
		return true;
	}
	return false;
}

void startGame() {
	state = GameScreen;
	openGameScreen();
	//TODE: CODE Generate asteroid list with spawnpoint / delete/done?

	timerStart();
}

bool readyToReset() {
	if (GetAsyncKeyState(VK_BACK))
	{
		return true;
	}
	return false;
}

void ResetAll() {
	//TODO: CODE reset all values of score, asteroid list.
	//			if settings used do NOT reset Settings!!!

	score = 0;
}

void gameCheck() {
	if (!isOutTime() && !GetAsyncKeyState(VK_ESCAPE)) {		//Checks if either the time is up or if escape key is pressed
		checkSpawnable();
		checkAsteroids();
		updateAsteroidsLocation();
		//TODO: remainder of the game logic -> lives if opted into the game

	}
	else {
		endGame();
	}
}

void checkAsteroids() {
	for(Asteroid* roid : asteroidList)
	{
		if ((shotCheck(leftVizor, roid)||shotCheck(rightVizor, roid))&&roid->z > minDepth) {
			score += roid->reward;
			explodeAsteroid(roid);
			asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
		}else if(roid->z <= minDepth)
		{
			score -= roid->reward;
			explodeAsteroid(roid);
			asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
		}
	}
}

Coordinate* centerPoint = new Coordinate();
int rotationSpeed = 15;
double debtSpeed = (maxDepth - minDepth) / 10.0;

void updateAsteroidsLocation() {
	centerPoint->x = halfScreenWidth;
	centerPoint->y = 0;

	for (Asteroid* roid : asteroidList) {
		double a = (centerPoint->y - roid->y) / (centerPoint->x - roid->x);
		double b = -a * roid->x + roid->y;

		if (roid->x < halfScreenWidth)
		{
			roid->x += gameSpeed;
		}
		else if (roid->x > halfScreenWidth) {
			roid->x -= gameSpeed;
		}
		
		double y = a * (roid->x) + b;

		roid->y = y;
		roid->z -= debtSpeed;
		roid->rotation += rotationSpeed;
	}
}

bool isOutTime() {
	if (getElapsedSeconds() > 300.0)
	{
		return true;
	}
	return false;
}

void endGame() {
	state = EndScreen;
	timerStop();
	increaseSpawn(false);
	openGameOverScreen();
	//TODE: TODO: OPT: Show Score on Screen
	//showScore(score);
}

Coordinate generateRandomSpawn() {
	return SpawnPoints[rand() % 30];
}

void checkSpawnable() {
	double t = (10 - getDifficulty()) / 2;

	if (fmod(getElapsedSeconds() , t) == 0) {
		spawnAsteroid();
	}
}

void spawnAsteroid() {
	Asteroid* roid = new Asteroid(5, 100, 0, 100, generateRandomSpawn());
	asteroidList.push_back(roid);
}

//-------------OPENGL/visuals-------------
//Move these to open GL later

void openGameOverScreen() {
//TODO: CODE Switch to game over screen
}

void openGameScreen() {
	//TODO: CODE Switch to game screen
}

void openStartScreen() {
	//TODO: CODE Switch to start screen
}

void explodeAsteroid(Asteroid* roid) {
//TODO: OPENGL CODE EXPLOSION!!!
}

void updateLeftVizor(Coordinate left) {
	//TODO: OPENGL CODE update the leftVizor to a new position
}
void updateRightVizor(Coordinate right) {
	//TODO: OPENGL CODE updtae the rightVizor to new position
}
