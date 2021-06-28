#include <iostream>
#include <Windows.h>
#include "Asteroid.h"
#include "Vizor.h"
#include "Coordinate.h"
#include "SpawnPoints.cpp"
#include "Timer.h"
#include "Global.h"
//#include "Vision.h"
#include "Game.h"
#include "Visuals.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include "SubModules.h"
#include "Explosion.h"
#include "GameLogic.h"
#include <thread>

//-----------------------Vars-------------------
Vizor leftVizor{ 50, 0, 0 }, rightVizor{ 50, 0, 0 };

int score;
int state = 1;
int spawnCounter = 0;


std::vector<Asteroid*> asteroidList{};
vector<Coordinate> SpawnPoints;
vector<Explosion*> explosions{};
void visionLoop();
Coordinate* centerPoint = new Coordinate();
int rotationSpeed = 15;
double debtSpeed = (maxDepth - minDepth) / 10.0;

//--------------
void checkExplosions();

void initializeGame() {
	state = StartScreen;
	drawStartScreen();

	// make an array of spawnpoints: int are screen parameters, need to change to stand values
	//SpawnPoints = RandomSpawnPoints(screenWidth, screenHeight);
	SpawnPoints = RandomSpawnPoints(350, 150);
}

void gamePlay() {
	
	Coordinate left = getLeftVizorCoord();
	Coordinate right = getRightVizorCoord();
	
	leftVizor.x = (left.x/50.0);
	leftVizor.y = ((-1*left.y)/50.0);

	rightVizor.x = (right.x/50.0);
	rightVizor.y = ((-1*right.y)/50.0);
	//std::cout << "right coord x = " << right.x <<endl;
	//std::cout << "rightvisor x" << rightVizor.x<<endl;
}

void startGame() {
	state = GameScreen;
	openGameScreen();
	//TODE: CODE Generate asteroid list with spawnpoint / delete/done?

	timerStart();

}

void visionLoop() {
	while (state == GameScreen) {
		updateVision();
	}
}

void runStartScreenState() {
	if (enterButtonPressed())
	{
		startGame();
	}
}

void runGameScreenState() {
	thread visionThread(visionLoop);
	while (state == GameScreen) {
		openGameScreen();
		gamePlay();
		gameCheck();
		increaseSpawn(true);
	}
	visionThread.join();
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
	short keyStateEscape = GetAsyncKeyState(VK_ESCAPE);	//This one doesn't have any explicit function here, but improves functionality in gameCheck
	short keyStateEnter = GetAsyncKeyState(VK_RETURN);
	if (keyStateEnter < 0)
	{
		return true;
	}
	return false;
}

bool readyToReset() {
	short keyStateBack = GetAsyncKeyState(VK_BACK);
	if (keyStateBack < 0)
	{
		state = StartScreen;
		return true;
	}
	return false;
}

void ResetAll() {
	//            if settings used do NOT reset Settings!!!

	asteroidList.clear();
	explosions.clear();

	score = 0;
}

void gameCheck() {
	if (!isOutTime() && !GetAsyncKeyState(VK_ESCAPE)) {		//Checks if either the time is up or if escape key is pressed
		checkSpawnable();
		checkAsteroids();
		updateAsteroidsLocation();
		spawnAsteroid();// verwijdert achtergrond
		checkExplosions();
		//TODO: remainder of the game logic -> lives if opted into the game

	}
	else {
		endGame();
	}
}

void checkExplosions() {
	for(Explosion* splo : explosions)
	{
		if (splo->Duration != 0) {
			splo->Duration--;
		}
		else {
			explosions.erase(std::remove(explosions.begin(), explosions.end(), splo), explosions.end());
		}
	}
}

void checkAsteroids() {
	for(Asteroid* roid : asteroidList)
	{
		
		if ((vizorAsteroidOverlapCheck(leftVizor, roid)||vizorAsteroidOverlapCheck(rightVizor, roid))) {
			score += roid->reward;
			cout << "vizor placement: " << rightVizor.x << "" << rightVizor.y << endl;
			cout << "Score added to: " << score << endl;
			explodeAsteroid(roid);
			asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
		}else 
			if(roid->z <= minDepth)
		{
				if (score>0)
				{
					score -= roid->reward;
				}
			
			//cout << "Score reduced to: " << score << endl;
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
	if (fmod(spawnCounter, 2) == 0)
	{
		Asteroid* roid = new Asteroid(50, 100, 50, 100, generateRandomSpawn());
		asteroidList.push_back(roid);
	}
	spawnCounter++;
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
	//STOP Thread
	drawEndScreen(score);
}

//-------------OPENGL/visuals-------------
//Move these to open GL later

void openGameScreen() {
	//TODO: CODE Switch to game screen
	initScreen();

	//std::cout << "draw vizors" << std::endl;
	drawVizor(leftVizor, rightVizor);

	for (Asteroid* roid : asteroidList)
	{
		//std::cout << "draw asteroid: (" << roid->x << "," << roid->y << "," << roid->y << ")" << std::endl;
		drawAsteroid(roid->x, roid->y, roid->z);
	}

	for (Explosion* splo : explosions)
	{
		//std::cout << "draw explosion: (" << splo->x << "," << splo->y << "," << splo->y << ")" << std::endl;
		drawExplosion(splo->x, splo->y, splo->z);
	}
	finalizeScreen();
}

void explodeAsteroid(Asteroid* roid) {
//TODO: OPENGL CODE EXPLOSION!!!
	Explosion* explosion = new Explosion(roid->x, roid->y, roid->z, 3);
	explosions.push_back(explosion);
	drawExplosion(roid->x, roid->y, roid->z);
}
