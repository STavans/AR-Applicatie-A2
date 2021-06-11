#include <iostream>
#include <Windows.h>
#include "Asteroid.h"
#include "Vizor.h"

//-----------------------Vars-------------------
Vizor leftVizor, rightVizor;

int score;
int state;

//TODO: ARRAYLIST/LIST of Asteroids

const int StartScreen = 1;
const int GameScreen = 2;
const int EndScreen = 3;

//--------------

void Startup() {
	state = StartScreen;
	openStartScreen();
	CVSettup();
	mainLoop();
}

void mainLoop(){
	while (true)
	{
		stateLoopSwitch();
		//Button check? 
		//Timer run?
	}
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
			gameCheck();
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
	//TODO: CODE Button waiting
	if (GetAsyncKeyState(VK_RETURN))
	{
		return true;
	}
	return false;
}

void startGame() {
	state = GameScreen;
	openGameScreen();
	//TODO: CODE Start the game
}

bool readyToReset() {
//TODE: TODO: CODE wait for button pressed \/ wait for timer
	if (GetAsyncKeyState(VK_BACK))
	{
		return true;
	}
	return false;
}

void ResetAll() {
	//TODO: CODE reset all values of points, asteroids and the game
	//			if settings used do NOT reset Settings!!!
}

void gameCheck() {
	if (!isOutTime() && !GetAsyncKeyState(VK_ESCAPE)) {		//Checks if either the time is up or if escape key is pressed
		checkAsteroids();
		//TODO: remainder of the game logic -> spawning asteroids and lives if opted into the game

		//TODE: OPT escape button when want to quit?
	}
	else {
		endGame();
	}
}

void checkAsteroids() {
	for(Asteroid roid : AsteroidList)
	{
		//TODO: use the asteroids check function or check this using different technic.
		if (shotCheck(leftVizor, roid)||shotCheck(rightVizor, roid)) {
			score += 100;
			explodeAsteroid(roid);

			//TODE: TODO: CODE Remove asteroid from array or set it to dead
			//AsteroidList.remove(roid); (this wont work, but is example)
			//roid.state = dead;
		}
	}
}

bool isOutTime() {
	//TODO: CODE check whether time is zero or less. retrieve it from the time system
	if (true)
	{
		return true;
	}
	return false;
}

void endGame() {
	state = EndScreen;
	
	openGameOverScreen();
	//TODE: TODO: OPT: Show Score on Screen
	//showScore(score);
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

void explodeAsteroid(Asteroid roid) {
//TODO: OPENGL CODE EXPLOSION!!!
}

//-------------OPENCV/controls-------------
//Move these to open cv later

void CVSettup() {
	//TODO: CODE settup entire open cv controls
}

