#pragma once
#ifndef HITSPHERE_H
#define HITSPHERE_H

class HitSphere
{
	double x, y, radius;

public:
	HitSphere(double, double, double);
	static bool hit(HitSphere, HitSphere);
	static bool hitBase(HitSphere);
};

#endif