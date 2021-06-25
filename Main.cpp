#include "Game.h"
#include "SubModules.h"

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

