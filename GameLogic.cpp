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
    if (distSq <= radSumSq) {
        return true;
    }
    else {
        return false;
    }

    /*
    glm::vec3 roidVector = glm::vec3(roid.x, roid.y, roid.z);
    glm::vec3 vizorVector = glm::vec3(vizor.x, vizor.y, 1.0);
    glm::vec3 crossproduct = glm::cross(vizorVector, roidVector);
    cout << "CrossProduct: " << crossproduct.x << ", "<< crossproduct.y << ", " << crossproduct.z << endl;
    if (-5 < crossproduct.x < 5 && -5 < crossproduct.y < 5 && -5 < crossproduct.z < 5)
    {
        return true;
    }
    return false;
*/

    /*
    double rcXYroid = 0;
    double rcXYvizor = 0;
    if (roid.y!=0){
        rcXYroid = roid.x / roid.y;
    }
    double rcXZroid = roid.x / roid.z;
    if (vizor.y != 0)
    {
        rcXYvizor = vizor.x / vizor.y;
    }
    
    double rcXZvizor = vizor.x / 1.0;

    if ( (-1 < rcXYroid - rcXYvizor < 1) && (-1 < rcXZroid - rcXZvizor < 1))
    {
        return true;
    }
    return false;
  */
}