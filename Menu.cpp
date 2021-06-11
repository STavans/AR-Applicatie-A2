#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "Menu.h"
#include <iostream>
#include <Windows.h>
#include <glm/gtc/matrix_transform.hpp>		//Includes copied from main.cpp, might nod need them all
using tigl::Vertex;

struct Menu {
    int current;
}Menu;

void drawMenuStart();		//Draws the start screen
void drawMenuGameOver();	//Draws the game over screen
void menuSetup();     //init method
int inputHandler();         //Handles the inputs and determines what screen the window needs to go to

void menuSetup() {
    Menu.current = START;  //We set the current menu to start with the assumption that we start the game on the start menu screen
}

int inputHandler() {
    //TODO: THIS STILL NEEDS TO LOOP SOMEHOW
    while (true) {

    

    switch (Menu.current){
    case START:
        if (GetAsyncKeyState(VK_RETURN)) {  //Check for enter key
            Menu.current = GAME_RUNNING;    //Assumption is made here that we can only go to Gaame_running from start
            std::cout << "Game Running";
        }
        break;
    case GAME_RUNNING:
        if (GetAsyncKeyState(VK_ESCAPE)) {  //Check for escape key
            Menu.current = GAME_OVER;       //Assumption made that we always go to game over screen from game running
            drawMenuGameOver();
        }
        break;
    case GAME_OVER:
        if (GetAsyncKeyState(VK_BACK)) {   //If input for back to main menu (backspace)
            Menu.current = START;
            drawMenuStart();
        }
        else if (GetAsyncKeyState(VK_RBUTTON)) {   //If input for retry (Right click, might need to be a different button)
            Menu.current = GAME_RUNNING;
            std::cout << "Game Running";
        }
        break;
    default:
        break;
    }
    Sleep(100);
    }
    return 0;
}

void drawMenuStart() {
    //Lacking knowldedge
    std::cout << "Start menu!";
}

void drawMenuGameOver() {
    std::cout << "Game Over Menu!";
}