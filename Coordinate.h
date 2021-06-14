#pragma once
#include <iostream>
using namespace std;

/*
* Coordinate class used for spawning asteroids on an x and y axis
*/
class Coordinate
{
public:

    int x;
    int y;

    void printCoordinate()
    {
        cout << "X_Coordinate: " << x << endl;
        cout << "Y_Coordinate: " << y << endl;
    }
};