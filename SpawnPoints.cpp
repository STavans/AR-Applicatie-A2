#include <iostream>
#include "Coordinate.h"
using namespace std;

// Makes an array of 30 spawnpoints
Coordinate * RandomSpawnPoints(int x, int y)
{
    Coordinate cArray[30];

    // adds 10 spawnpoints on the left of the screen
    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = 0;
        c.y = rand() % y;

        cArray[i] = c;
    }

    // adds 10 spawnpoints on the upper part of the screen
    for (int i = 0; i < 10; i++) {
        Coordinate c;
        int checkX = rand() % x;
        if (checkX < x / 2 && checkX > x / 2) {
            c.x = checkX;
        }
        else {
            c.x = 200;
        }
        c.y = y;

        cArray[i + 10] = c;
    }

    // adds 10 spawnpoints on the right side of the screen
    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = x;
        c.y = rand() % y;

        cArray[i + 20] = c;
    }

    for (Coordinate c : cArray)
    {
        c.printCoordinate();
    }

    // returns array of spawnpoints
    return cArray;
}