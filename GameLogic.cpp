#include "GameLogic.h"
#include <glm/gtc/matrix_transform.hpp>
/*
* Checks if the vizor and asteroid align
*/
bool vizorAsteroidOverlapCheck(Vizor vizor, Asteroid* asteroid) {
    Asteroid roid = *asteroid;

    double asteroidx = (roid.x / (roid.z*0.75))*10.0;
    double asteroidy = (roid.y / (roid.z * 0.75))*10.0;
    double asteroidd = (roid.diameter*10.0)/(roid.z*0.75);

    double distSq = (asteroidx - vizor.x) * (asteroidx - vizor.x) +
        (asteroidy - vizor.y) * (asteroidy - vizor.y);
    double radSumSq = (vizor.diameter + asteroidd) * (vizor.diameter + asteroidd);
    cout << "logic check: " << distSq << ", " << radSumSq << endl;
    if (distSq <= radSumSq) {
        cout << "Explode: " << endl;
        cout << "asteroid: " << asteroidx << ", " << asteroidy << ", " << asteroidd << endl;
        cout << "roid: " << roid.x << ", " << roid.y << ", " << roid.z << endl;
        cout << "Vizor: " << vizor.x << ", " << vizor.y << ", " << vizor.diameter << endl;
        return true;
    }
    else {
     
        cout << "Not Explode: "  << endl;
        cout << "asteroid: " << asteroidx << ", " << asteroidy << ", " << asteroidd << endl;
        cout << "roid: " << roid.x << ", " << roid.y << ", " << roid.z << endl;
        cout << "Vizor: " << vizor.x << ", " << vizor.y << ", " << vizor.diameter << endl;
        return false;
    }
}