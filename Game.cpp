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
#include "mainVisual.h"
#include <cmath>
#include <vector>
#include <algorithm>

//-----------------------Vars-------------------
Vizor leftVizor{50, 0, 0}, rightVizor{50, 0, 0};

int score;
int state;

std::vector<Asteroid*> asteroidList{};
vector<Coordinate> SpawnPoints;

const int StartScreen = 1;
const int GameScreen = 2;
const int EndScreen = 3;

//--------------

void Game::startUp() {
	state = StartScreen;
	drawStartScreen();

	// make an array of spawnpoints: int are screen parameters, need to change to stand values
	SpawnPoints = RandomSpawnPoints(100, 100);
	mainLoop();
}

void Game::mainLoop(){
	while (true)
	{
		stateLoopSwitch();
	}
}

void Game::gamePlay() {
	CVView();
	Coordinate left = getLeftVizor();
	Coordinate right = getRightVizor();
	
	leftVizor.x = left.x;
	leftVizor.y = left.y;
	
	rightVizor.x = right.x;
	rightVizor.y = right.y;
	std::cout << "right coord x = " << right.x <<endl;
	std::cout << "rightvisor x" << rightVizor.x<<endl;
}

void Game::stateLoopSwitch() {
	switch (state)
	{
		case StartScreen:
			if (enterButtonPressed())
			{
				startGame();
			}
			break;
		case GameScreen:
			//FIX: MOVE openGameScreen before gameCheck
			openGameScreen();
			gamePlay();
			gameCheck(); 
			increaseSpawn(true);
			
			break;
		case EndScreen:
			if (readyToReset())
			{
				drawStartScreen();
				ResetAll();
			}
			break;
	default:
		break;
	}
}

bool Game::enterButtonPressed() {
	if (GetAsyncKeyState(VK_RETURN))
	{
		return true;
	}
	return false;
}

void Game::startGame() {
	state = GameScreen;
	openGameScreen();
	//TODE: CODE Generate asteroid list with spawnpoint / delete/done?

	timerStart();
}

bool Game::readyToReset() {
	if (GetAsyncKeyState(VK_BACK))
	{
		state = StartScreen;
		return true;
	}
	return false;
}

void Game::ResetAll() {
	//            if settings used do NOT reset Settings!!!

	for (Asteroid* roid : asteroidList)        //Loops through the asteroids to delete them all.
	{
		asteroidList.erase(std::remove(asteroidList.begin(), asteroidList.end(), roid), asteroidList.end());
	}
	
	score = 0;
}

void Game::gameCheck() {
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

void Game::checkAsteroids() {
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

void Game::updateAsteroidsLocation() {
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
		//double a = (centerPoint->y - roid->y) / (centerPoint->x - roid->x);
		double b = -a * roid->x + roid->y;

		if (roid->x < 0)
		{
			roid->x += gameSpeed;
		}
		else if (roid->x > 0) {
			roid->x -= gameSpeed;
		}
		
		double y = a * (roid->x) + b;

		roid->y = y;
		roid->z -= debtSpeed;
		roid->rotation += rotationSpeed;
	}
}

bool Game::isOutTime() {
	if (getElapsedSeconds() > 30.0)
	{
		return true;
	}
	return false;
}

void Game::endGame() {
	state = EndScreen;
	timerStop();
	increaseSpawn(false);
	drawEndScreen();
	//TODE: TODO: OPT: Show Score on Screen
	//showScore(score);
}

Coordinate Game::generateRandomSpawn() {
	return SpawnPoints[rand() % 30];
}

void Game::checkSpawnable() {
	double t = (10 - getDifficulty()) / 2;
	
	if (fmod(getElapsedSeconds() , t) == 0) {
		spawnAsteroid();
	}
}

void Game::spawnAsteroid() {
	Asteroid* roid = new Asteroid(5, 100, 50, 100, generateRandomSpawn());
	asteroidList.push_back(roid);
}

//-------------OPENGL/visuals-------------
//Move these to open GL later

void Game::openGameScreen() {
	//TODO: CODE Switch to game screen
	initScreen();

	std::cout << "draw left vizor" << std::endl;
	drawVizor(leftVizor.x, leftVizor.y);
	std::cout << "draw right vizor" << std::endl;
	drawVizor(rightVizor.x, rightVizor.y);

	for (Asteroid* roid : asteroidList)
	{
		std::cout << "draw asteroid: (" << roid->x << "," << roid->y << "," << roid-> y << ")" << std::endl;
		drawAsteroid(roid->x, roid->y, roid->z);
	}

	finalizeScreen();

}

void Game::explodeAsteroid(Asteroid* roid) {
//TODO: OPENGL CODE EXPLOSION!!!
	drawExplosion(roid->x, roid->y, roid->z);
}