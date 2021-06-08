#pragma once
#include <iostream>
using namespace std;

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