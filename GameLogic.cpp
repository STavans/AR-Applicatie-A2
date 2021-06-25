#include "GameLogic.h"

/*
* Checks if the vizor and asteroid align
*/
bool vizorAsteroidOverlapCheck(Vizor vizor, Asteroid* asteroid) {
    Asteroid roid = *asteroid;
    int distSq = (roid.x - vizor.x) * (roid.x - vizor.x) +
        (roid.y - vizor.y) * (roid.y - vizor.y);
    int radSumSq = (roid.diameter + vizor.diameter) * (roid.diameter + vizor.diameter);
    if (distSq > radSumSq)
        return false;
    else
        return true;
}