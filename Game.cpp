#include <iostream>
#include <Windows.h>
#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"
#include "SpawnPoints.cpp"
#include "Timer.h"
#include "Global.h"
#include "Vision.h"
#include "Game.h"
#include "Visuals.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include "SubModules.h"
#include "GameLogic.h"

//-----------------------Vars-------------------
Vizor leftVizor{ 50, 0, 0 }, rightVizor{ 50, 0, 0 };

int score;
int state = 1;

std::vector<Asteroid*> asteroidList{};
vector<Coordinate> SpawnPoints;

Coordinate* centerPoint = new Coordinate();
int rotationSpeed = 15;
double debtSpeed = (maxDepth - minDepth) / 10.0;

//--------------

void initializeGame() {
	state = StartScreen;
	drawStartScreen();

	// make an array of spawnpoints: int are screen parameters, need to change to stand values
	//SpawnPoints = RandomSpawnPoints(screenWidth, screenHeight);
	SpawnPoints = RandomSpawnPoints(200, 150);
}

void gamePlay() {
	updateVision();
	Coordinate left = getLeftVizorCoord();
	Coordinate right = getRightVizorCoord();
	
	leftVizor.x = left.x;
	leftVizor.y = left.y;

	rightVizor.x = right.x;
	rightVizor.y = right.y;
	std::cout << "right coord x = " << right.x <<endl;
	std::cout << "rightvisor x" << rightVizor.x<<endl;
}

void startGame() {
	state = GameScreen;
	openGameScreen();
	//TODE: CODE Generate asteroid list with spawnpoint / delete/done?

	timerStart();
}

void runStartScreenState() {
	if (enterButtonPressed())
	{
		startGame();
	}
}

void runGameScreenState() {
	openGameScreen();
	gamePlay();
	gameCheck();
	increaseSpawn(true);

}

void runEndScreenState() {
	if (readyToReset())
	{
		drawStartScreen();
		ResetAll();
	}
}

void stateMachine() {
	switch (state)
	{
	case StartScreen:
		runStartScreenState();
		break;
	case GameScreen:
		runGameScreenState();
		break;
	case EndScreen:
		runEndScreenState();
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

bool readyToReset() {
	if (GetAsyncKeyState(VK_BACK))
	{
		state = StartScreen;
		return true;
	}
	return false;
}

void ResetAll() {
	//            if settings used do NOT reset Settings!!!

	for (Asteroid* roid : asteroidList)        //Loops through the asteroids to delete them all.
	{
		asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
	}
	
	score = 0;
}

void gameCheck() {
	if (!isOutTime() && !GetAsyncKeyState(VK_ESCAPE)) {		//Checks if either the time is up or if escape key is pressed
		checkSpawnable();
		checkAsteroids();
		updateAsteroidsLocation();
		spawnAsteroid();// verwijdert achtergrond
		//TODO: remainder of the game logic -> lives if opted into the game

	}
	else {
		endGame();
	}
}

void checkAsteroids() {
	for(Asteroid* roid : asteroidList)
	{
		if ((vizorAsteroidOverlapCheck(leftVizor, roid)||vizorAsteroidOverlapCheck(rightVizor, roid))&&roid->z > minDepth) {
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

void checkSpawnable() {
	double t = (10 - getDifficulty()) / 2;

	if (fmod(getElapsedSeconds(), t) == 0) {
		spawnAsteroid();
	}
}

Coordinate generateRandomSpawn() {
	return SpawnPoints[rand() % 30];
}

void spawnAsteroid() {
	Asteroid* roid = new Asteroid(5, 100, 50, 100, generateRandomSpawn());
	asteroidList.push_back(roid);
}

void updateAsteroidsLocation() {
	//centerPoint->x = halfScreenWidth;
	centerPoint->x = 0;
	centerPoint->y = 0;

	for (Asteroid* roid : asteroidList) {
		double a;
		if (centerPoint->x - roid->x == 0) {
			a = 0;
		}
		else {
			a = (centerPoint->y - roid->y) / (centerPoint->x - roid->x);
		}
		double b = -a * roid->x + roid->y;

		if (roid->x < centerPoint->x)
		{
			roid->x += gameSpeed;
		}
		else if (roid->x > centerPoint->x) {
			roid->x -= gameSpeed;
		}
		
		double y = a * (roid->x) + b;

		roid->y = y;
		roid->z -= debtSpeed;
		roid->rotation += rotationSpeed;
	}
}

bool isOutTime() {
	if (getElapsedSeconds() > 30.0)
	{
		return true;
	}
	return false;
}

void endGame() {
	state = EndScreen;
	timerStop();
	increaseSpawn(false);
	drawEndScreen(score);
}

//-------------OPENGL/visuals-------------
//Move these to open GL later

void openGameScreen() {
	//TODO: CODE Switch to game screen
	initScreen();

	std::cout << "draw vizors" << std::endl;
	drawVizor(leftVizor, rightVizor);

	for (Asteroid* roid : asteroidList)
	{
		std::cout << "draw asteroid: (" << roid->x << "," << roid->y << "," << roid->y << ")" << std::endl;
		drawAsteroid(roid->x, roid->y, roid->z);
	}

	finalizeScreen();
}

void explodeAsteroid(Asteroid* roid) {
//TODO: OPENGL CODE EXPLOSION!!!
	drawExplosion(roid->x, roid->y, roid->z);
}
