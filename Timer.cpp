#include <iostream>
#include <chrono>
#include <ctime>

#define maxSpawnTime 30.0

std::chrono::time_point<std::chrono::system_clock> startTime;
std::chrono::time_point<std::chrono::system_clock> endTime;
bool                                               running = false;

//Starts the timer
void timerStart()
{
    startTime = std::chrono::system_clock::now();
    running = true;
}

//Stops the timer
void timerStop()
{
    endTime = std::chrono::system_clock::now();
    running = false;
}

//Returns the time in milliseconds
double elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTimeCurrent;

    if (running)
    {
        endTimeCurrent = std::chrono::system_clock::now();
    }
    else
    {
       endTimeCurrent = endTime;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTimeCurrent - startTime).count();
}

//Returns the time in seconds.
double elapsedSeconds()
{
    return elapsedMilliseconds() / 1000.0;
}

double timeAlpha;

//Increases spawn amount based on elapsed time
void increaseSpawn(bool isRunning) {
    if (!isRunning)
    {
        timeAlpha = 0.0;
    }
    else
    {
        if (elapsedSeconds() - timeAlpha == maxSpawnTime)
        {
                timeAlpha = elapsedSeconds();
                //increase spawn amount here
        }
    }
}