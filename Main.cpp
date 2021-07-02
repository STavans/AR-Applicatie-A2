#include "Game.h"
#include "SubModules.h"

void mainLoop();
void initializeSubModels();

int main() {
	initializeSubModels();
	mainLoop();
	return 1;
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

