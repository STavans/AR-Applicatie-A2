#pragma once
#ifndef TIMER_H
#define TIMER_H

void timerStart();
void timerStop();
double getElapsedMilliseconds();
double getElapsedSeconds();
void increaseSpawn(bool isRunning);
int getDifficulty();

#endif#
