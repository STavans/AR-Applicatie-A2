#include <iostream>
#include "Coordinate.h"
#include <vector>
using namespace std;



/*
* Makes an array of 30 coordinates which are used to randomize spawn
*/
inline vector<Coordinate>  RandomSpawnPoints(int x, int y)
{
    vector<Coordinate> vecCoor{};

    // adds 10 spawnpoints on the left of the screen
    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = x - (x/6 + (rand() % x/2));
        c.y = y - (rand() % y / 2);

        vecCoor.push_back(c);
    }

    // adds 10 spawnpoints on the upper part of the screen
    for (int i = 0; i < 10; i++) {
        Coordinate c;
        c.x = x - (rand() % x);
        c.y = y;

        vecCoor.push_back(c);
    }

    // adds 10 spawnpoints on the right side of the screen
    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = x;
        c.y = y - (rand() % y);

        vecCoor.push_back(c);
    }

    // returns array of spawnpoints
    return vecCoor;
}