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
Vizor leftVizor{ 0, 0, 0 }, rightVizor{ 0, 0, 0 };

int score;
int state = 1;
int spawnCounter = 0;


std::vector<Asteroid*> asteroidList{};
vector<Coordinate> SpawnPoints;
vector<Explosion*> explosions{};
void visionLoop();
Coordinate* centerPoint = new Coordinate();
int rotationSpeed = 15;
double debtSpeed = (maxDepth - minDepth) / 40.0;

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

/*
* Starts the timer and starts the gameScreen
*/
void startGame() {
	state = GameScreen;
	openGameScreen();

	timerStart();

}

/*
* Updates the vision camera
*/
void visionLoop() {
	while (state == GameScreen) {
		updateVision();
	}
}

/*
* Starts the game when EnterButtonPressed
*/
void runStartScreenState() {
	if (enterButtonPressed())
	{
		startGame();
	}
}

/*
* Starts playing the game, so starts Vision, opens the screen, and plays and checks the game.
*/
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

/*
* Resets everything and returns to startScreen.
*/
void runEndScreenState() {
	if (readyToReset())
	{
		drawStartScreen();
		ResetAll();
	}
}

/*
* switch case for keeping the current game state.
*/
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

/*
* Checkes if enterButton is pressed.
*/
bool enterButtonPressed() {
	short keyStateEscape = GetAsyncKeyState(VK_ESCAPE);	//This one doesn't have any explicit function here, but improves functionality in gameCheck
	short keyStateEnter = GetAsyncKeyState(VK_RETURN);
	if (keyStateEnter < 0)
	{
		return true;
	}
	return false;
}

/*
* Checks if Backspace is pressed and returnes to startScreen.
*/
bool readyToReset() {
	short keyStateBack = GetAsyncKeyState(VK_BACK);
	if (keyStateBack < 0)
	{
		state = StartScreen;
		return true;
	}
	return false;
}

/*
* Resets all the asteroids, explosions and score.
*/
void ResetAll() {
	asteroidList.clear();
	explosions.clear();

	score = 0;
}

/*
* Calls all methods used for gameLogic, also checks if game has ended via timelimit or escape pressed.
*/
void gameCheck() {
	if (!isOutTime() && !GetAsyncKeyState(VK_ESCAPE)) {
		checkSpawnable();
		checkAsteroids();
		updateAsteroidsLocation();
		spawnAsteroid();
		checkExplosions();
	}
	else {
		endGame();
	}
}

/*
* Checks if a Explosions is required on the screen and removes it when no longer needed.
*/
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


/*
* Checks if the asteroid and vizors overlap.
*/
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
			explodeAsteroid(roid);
			asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
		}
	}
}

/*
* Checks if asteroids need to be spawned based on the difficulty, not fully integrated yet.
*/
void checkSpawnable() {
	double t = (10 - getDifficulty()) / 2;

	if (fmod(getElapsedSeconds(), t) == 0) {
		spawnAsteroid();
	}
}

/*
* Chooses a random spawnpoint out of the list.
*/
Coordinate generateRandomSpawn() {
	return SpawnPoints[rand() % 30];
}

/*
* Spawns an asteroid, every 6 iterations, with a random spawnpoint.
*/
void spawnAsteroid() {
	if (fmod(spawnCounter, 6) == 0)
	{
		Asteroid* roid = new Asteroid(10, 100, 50, 100, generateRandomSpawn());
		asteroidList.push_back(roid);
	}
	spawnCounter++;
}

/*
* Updates the location of all asteroids on the screen.
*/
void updateAsteroidsLocation() {
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

/*
* Checks if the game time has expired.
*/
bool isOutTime() {
	if (getElapsedSeconds() > 300.0)
	{
		return true;
	}
	return false;
}

/*
* Calls all usefull methods when the game has ended.
*/
void endGame() {
	state = EndScreen;
	timerStop();
	increaseSpawn(false);
	drawEndScreen(score);
}

/*
* Gives the instructions to draw Asteroids, vizors and explosions on the right locations.
*/
void openGameScreen() {
	initScreen();
	drawVizor(leftVizor, rightVizor);

	for (Asteroid* roid : asteroidList)
	{
		drawAsteroid(roid->x, roid->y, roid->z);
	}

	for (Explosion* splo : explosions)
	{
		drawExplosion(splo->x, splo->y, splo->z);
	}
	finalizeScreen();
}

/*
* Logic for drawing and creating the explosions.
*/
void explodeAsteroid(Asteroid* roid) {
	Explosion* explosion = new Explosion(roid->x, roid->y, roid->z, 3);
	explosions.push_back(explosion);
	drawExplosion(roid->x, roid->y, roid->z);
}
