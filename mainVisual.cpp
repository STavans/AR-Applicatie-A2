#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "ObjModel.h"
#include "Game.h"
#include <glm/gtc/matrix_transform.hpp>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
ObjModel* asteroidModel;
ObjModel* vizorModel;
ObjModel* explosionModel;
Game* game;


int widthWindow = 1920;
int heightWindow = 1080;

void init();
void update();
void draw();
void windowInit();
void updateGameFrame();

int main(void)
{
    windowInit();
    game->startUp();

    while (!glfwWindowShouldClose(window))
    {
        updateGameFrame();
    }

    glfwTerminate();


    return 0;
}

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

    init();
}

void updateGameFrame() {
    update();
    draw();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    });


    asteroidModel = new ObjModel("models/asteroid/asteroid4.obj");
    vizorModel = new ObjModel("models/vizor/vizor.obj");
    explosionModel = new ObjModel("models/explosion/explosion2.obj");
}

float rotation = 0;

void update()
{
    rotation += 5.0f;
}

void drawBackground() {
    glm::vec4 purple = glm::vec4(0.15f, 0.0f, 0.19f, 1);
    glm::vec4 darkgray = glm::vec4(0.1f, 0.10f, 0.1f, 1);

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

void drawAsteroid(float x, float y, float z) {
    //asteroidModel->draw(glm::vec3(10.0f, 0.0f, 10.0f));
    asteroidModel->draw(glm::vec3(x, y, z));
}

void clearWindow() {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void startLighting() {
    tigl::shader->enableLighting(true);
    glShadeModel(GL_SMOOTH);
    tigl::shader->setLightCount(1);
    glm::vec3 lightPosDiffuse = glm::vec3(0, 0, -10);
    tigl::shader->setLightPosition(0, lightPosDiffuse);
    tigl::shader->setLightDiffuse(0, glm::vec4(0.8f, 0.8f, 0.8f, 0.8f));
}

void endLighting() {
    tigl::shader->enableLighting(false);
}

void draw()
{
    //Clear window
    clearWindow();

    //What does this do?
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 500.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(glm::lookAt(glm::vec3(0,0,-15), glm::vec3(0,0,0), glm::vec3(0,1,0)));

    glEnable(GL_DEPTH_TEST);
    tigl::shader->enableColor(true);

    drawBackground();

    //Draw lighting
    startLighting();

    asteroidModel->draw(glm::vec3(0.0f, 0.0f, 20.0f));
    //vizorModel->draw(glm::vec3(5.0f, 0.0f, 1.0f));
    //vizorModel->draw(glm::vec3(-5.0f, 0.0f, 1.0f));
    //vizorModel->draw(glm::vec3(0.0f, 5.0f, 1.0f));
    vizorModel->draw(glm::vec3(0.0f, -5.0f, 1.0f), glm::vec4(0.95f, 0.35f, 0.35f, 1.0f));
    explosionModel->draw(glm::vec3(0.0f, 0.0f, 20.0f));
    //draw asteroids and vizor here

    endLighting();

}