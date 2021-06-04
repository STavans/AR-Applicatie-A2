#pragma once

struct Menu {
	int current;
}Menu;

const int START = 1;
const int GAME_RUNNING = 2;
const int GAME_OVER = 3;

void drawMenuStart();		//Draws the start screen
void drawMenuGameOver();	//Draws the game over screen
void menuSetup(GLFWwindow* window);     //init method
int inputHandler();         //Handles the inputs and determines what screen the window needs to go to