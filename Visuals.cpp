#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "ObjModel.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Visuals.h"
#include "SubModules.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
ObjModel* asteroidModel;
ObjModel* vizorModel;
ObjModel* explosionModel;
ObjModel* startScreenModel;
ObjModel* gameOver;
ObjModel* returnCommand;
ObjModel* scoreBase;

ObjModel* one;
ObjModel* two;
ObjModel* three;
ObjModel* four;
ObjModel* five;
ObjModel* six;
ObjModel* seven;
ObjModel* eight;
ObjModel* nine;
ObjModel* zero;



int widthWindow = 1920;
int heightWindow = 1080;
float rotation = 0;

void initVisuals();
void updateRotation();
void windowInit();
void updateGameFrame();
void print_each_digit(int x, int layer);
void scoreswitchcase(int digit, int layer);

/*
* inits the window
*/
void windowInit() {
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(widthWindow, heightWindow, "Asteroid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    initVisuals();
}

/*
* inits the objectmodels
*/
void initVisuals() {
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });

    asteroidModel = new ObjModel("models/asteroid/asteroid4.obj");
    vizorModel = new ObjModel("models/vizor/vizor.obj");
    explosionModel = new ObjModel("models/explosion/explosion2.obj");
    startScreenModel = new ObjModel("models/text/StartScreen.obj");
    gameOver = new ObjModel("models/text/gameover.obj");
    returnCommand = new ObjModel("models/text/returncommand.obj");
    scoreBase = new ObjModel("models/text/score.obj");

    one = new ObjModel("models/text/one.obj");
    two = new ObjModel("models/text/two.obj");
    three = new ObjModel("models/text/three.obj");
    four = new ObjModel("models/text/four.obj");
    five = new ObjModel("models/text/five.obj");
    six = new ObjModel("models/text/six.obj");
    seven = new ObjModel("models/text/seven.obj");
    eight = new ObjModel("models/text/eight.obj");
    nine = new ObjModel("models/text/nine.obj");
    zero = new ObjModel("models/text/zero.obj");

}

/*
* inits the lighting
*/
void initializeLighting() {
    tigl::shader->enableLighting(true);
    glShadeModel(GL_SMOOTH);
    tigl::shader->setLightCount(1);
    glm::vec3 lightPosDiffuse = glm::vec3(0, 0, -25);
    tigl::shader->setLightPosition(0, lightPosDiffuse);
    tigl::shader->setLightDiffuse(0, glm::vec4(0.8f, 0.8f, 0.8f, 0.8f));
}

/*
* clears the lighting
*/
void finalizeLighting() {
    tigl::shader->enableLighting(false);
}

/*
* clears the window
*/
void clearWindow() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*
* draws the background
*/
void drawBackground() {
    glm::vec4 purple = glm::vec4(0.15f, 0.0f, 0.19f, 1);
    glm::vec4 darkgray = glm::vec4(0.1f, 0.10f, 0.1f, 1);

    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    //Draw background
    tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PC(glm::vec3(200, -100, 100), darkgray));
    tigl::addVertex(Vertex::PC(glm::vec3(200, 0, 100), purple));
    tigl::addVertex(Vertex::PC(glm::vec3(-200, 0, 100), purple));
    tigl::addVertex(Vertex::PC(glm::vec3(-200, -100, 100), darkgray));
    tigl::end();

    tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PC(glm::vec3(200, 100, 100), darkgray));
    tigl::addVertex(Vertex::PC(glm::vec3(200, 0, 100), purple));
    tigl::addVertex(Vertex::PC(glm::vec3(-200, 0, 100), purple));
    tigl::addVertex(Vertex::PC(glm::vec3(-200, 100, 100), darkgray));
    tigl::end();
}

/*
* inits the screen 
*/
void initScreen() {
    //Clear window
    clearWindow();

    //What does this do?
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 500.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0, 0, -15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));

    glEnable(GL_DEPTH_TEST);
    tigl::shader->enableColor(true);

    drawBackground();

    //Draw lighting
    initializeLighting();
}

/*
* clears the screen
*/
void finalizeScreen() {
    finalizeLighting();
    updateGameFrame();
}

/*
*  updates the game
*/
void updateGameFrame() {
    updateRotation();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/*
* updates the rotation
*/
void updateRotation() {
    rotation += 5.0f;
}

/*
* draws the asteroids at the given location
*/
void drawAsteroid(int x, int y, int z) {
    asteroidModel->draw(glm::vec3(x, y, z));
}

/*
* Draws the text of the startScreen
*/
void drawStartScreen() {
    initScreen();

    startScreenModel->draw(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    finalizeScreen();
}

/*
* Draws the text of the endScreen
*/
void drawEndScreen(int score) {
    initScreen();

    gameOver->draw(glm::vec3(0.0f, 6.0f, 6.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    scoreBase->draw(glm::vec3(4.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    if (score == 0) {
        scoreswitchcase(0, 1);
        scoreswitchcase(0, 2);
        scoreswitchcase(0, 3);
        scoreswitchcase(0, 4);
    }
    else {
        print_each_digit(score, 0);
    }
    returnCommand->draw(glm::vec3(3.0f, -10.0f, 15.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    finalizeScreen();
}

/*
* Method for drawing digits
*/
void print_each_digit(int x, int layer)
{
    layer++;
    if (x >= 10) {
        
        print_each_digit(x / 10, layer);
    }
    int digit = x % 10;
    scoreswitchcase(digit, layer);
}

/*
* switch case for drawing the digits
*/
void scoreswitchcase(int digit, int layer) {
    glm::vec3 position = glm::vec3((-5 + layer), 0.0f, 0.0f);
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    switch (digit)
    {
    case 0:
        zero->draw(position, color);
        break;
    case 1:
        one->draw(position, color);
        break;
    case 2:
        two->draw(position, color);
        break;
    case 3:
        three->draw(position, color);
        break;
    case 4:
        four->draw(position, color);
        break;
    case 5:
        five->draw(position, color);
        break;
    case 6:
        six->draw(position, color);
        break;
    case 7:
        seven->draw(position, color);
        break;
    case 8:
        eight->draw(position, color);
        break;
    case 9:
        nine->draw(position, color);
        break;
    default:
        break;
    }

}

/*
* Draws the explosion
*/
void drawExplosion(int x, int y, int z) {
    explosionModel->draw(glm::vec3(x, y, z));
}

/*
* Draws the vizors
*/
void drawVizor(Vizor leftVizor, Vizor rightVizor) {
    vizorModel->draw(glm::vec3(leftVizor.x, leftVizor.y, 1.0f), glm::vec4(0.95f, 0.35f, 0.35f, 1.0f));
    vizorModel->draw(glm::vec3(rightVizor.x, rightVizor.y, 1.0f), glm::vec4(0.95f, 0.35f, 0.35f, 1.0f));
}