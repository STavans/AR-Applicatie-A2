#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <math.h>

#define M_PI   3.14159265358979323846264338327950288
#define maxSpawnTime 30.0

class Timer
{
public:

private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool                                               m_bRunning = false;

    void start()
    {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }

    void stop()
    {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }

    double elapsedMilliseconds()
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (m_bRunning)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = m_EndTime;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }

    double elapsedSeconds()
    {
        return elapsedMilliseconds() / 1000.0;
    }

    double timeAlpha;

    void increaseSpawn() {
        Timer timer;

        if (timer.elapsedSeconds() <= 0.0 || timer.elapsedSeconds() >= 500.0)
        {
            timeAlpha = 0.0;
        }
        else
        {
            if (timer.elapsedSeconds() - timeAlpha == maxSpawnTime)
            {
                timeAlpha = timer.elapsedSeconds();
                //increase spawn amount here
            }
        }
    }
};