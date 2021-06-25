#include "Game.h"
#include "SubModules.h"

void stateMachine();
void mainLoop();
void initializeSubModels();

void main() {
	initializeSubModels();
	mainLoop();
}

void initializeSubModels() {
	windowInit();
	initializeGame();
}

void mainLoop() {
	while (true) {
		stateMachine();
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