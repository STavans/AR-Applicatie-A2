#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "FpsCam.h"
#include "Menu.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>		//Includes copied from main.cpp, might nod need them all
using tigl::Vertex;

GLFWwindow* window;
FpsCam* camera; //Potentially not needed?

void drawMenuStart();		//Draws the start screen
void drawMenuGameOver();	//Draws the game over screen
void menuSetup(GLFWwindow* window);     //init method
int inputHandler();         //Handles the inputs and determines what screen the window needs to go to

void menuSetup(GLFWwindow* newWindow) {
    window = newWindow;
    Menu.current = START;  //We set the current menu to start with the assumption that we start the game on the start menu screen
}

int inputHandler() {
    switch (Menu.current){
    case START:
        //Check input
        if (false) {      //This will be input-dependant later
            Menu.current = GAME_RUNNING;    //Assumption is made here that we can only go to Gaame_running from start
        }
        break;
    case GAME_RUNNING:
        //Check inputs
        if (false) {
            Menu.current = GAME_OVER;       //Assumption made that we always go to game over screen from game running
        }
        break;
    case GAME_OVER:
        //Check inputs
        if (false) {   //If input for back to main menu
            Menu.current = START;
        }
        else if (false) {   //If input for retry
            Menu.current = GAME_RUNNING;
        }
        break;
    default:
        break;
    }
}

void drawMenuStart() {
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(camera->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(true);

    glEnable(GL_DEPTH_TEST);

    tigl::begin(GL_TRIANGLES);
    tigl::addVertex(Vertex::PC(glm::vec3(-2, -1, -4), glm::vec4(1, 0, 0, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(2, -1, -4), glm::vec4(0, 1, 0, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(0, 1, -4), glm::vec4(0, 0, 1, 1)));


    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, 10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

    tigl::addVertex(Vertex::PC(glm::vec3(-10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, -10), glm::vec4(1, 1, 1, 1)));
    tigl::addVertex(Vertex::PC(glm::vec3(10, -1, 10), glm::vec4(1, 1, 1, 1)));

    tigl::end();
}

void drawMenuGameOver() {

}