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

    // adds 30 random spawnpoints
    for (int i = 0; i < 30; i++)
    {
        Coordinate c;
        c.x = -0.5f * x + (rand() % x);
        c.y = -0.5f * y + (rand() % y);

         vecCoor.push_back(c);
    }

    return vecCoor;
}