#include <iostream>
#include "Coordinate.h"
using namespace std;

Coordinate * RandomSpawnPoints(int x, int y)
{
    Coordinate cArray[30];


    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = 0;
        c.y = rand() % y;

        cArray[i] = c;
    }

    for (int i = 0; i < 10; i++) {
        Coordinate c;
        c.x = rand() % x;
        c.y = y;

        cArray[i + 10] = c;
    }

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

    return cArray;
}