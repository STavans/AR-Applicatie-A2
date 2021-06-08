#include <iostream>
#include "Coordinate.h"
using namespace std;

void RandomSpawnPoints()
{
    Coordinate cArray[30];

    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = 0;
        c.y = rand() % 1000;

        cArray[i] = c;
    }

    for (int i = 0; i < 10; i++) {
        Coordinate c;
        c.x = rand() % 1000;
        c.y = 1000;

        cArray[i + 10] = c;
    }

    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = 1000;
        c.y = rand() % 1000;

        cArray[i + 20] = c;
    }

    for (Coordinate c : cArray)
    {
        c.printCoordinate();
    }
}