#pragma once
#ifndef HITSPHERE_H
#define HITSPHERE_H

class HitSphere
{

public:
	double x, y, radius;
	HitSphere(double, double, double);
	static bool hit(HitSphere, HitSphere);
	static bool hitBase(HitSphere);
};

#endif