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
        c.y = 0;

        cArray[i + 10] = c;
    }

    for (int i = 0; i < 10; i++)
    {
        Coordinate c;
        c.x = rand() % 1000;
        c.y = 1000;

        cArray[i + 20] = c;
    }

    for (Coordinate c : cArray)
    {
        c.printCoordinate();
    }
}