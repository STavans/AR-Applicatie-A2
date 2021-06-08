#pragma once
#ifndef TIMER_H
#define TIMER_H

class Timer
{
	void start();
	void stop();
	double elapsedMilliseconds();
	double elapsedSeconds();
	void increaseSpawn();
};

#endif