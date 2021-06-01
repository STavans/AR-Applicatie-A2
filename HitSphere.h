#pragma once
#ifndef HITSPHERE_H
#define HITSPHERE_H

class HitSphere
{

public:
	double x, y, z, radius;
	HitSphere(double, double, double, double);
	static bool hit(HitSphere, HitSphere);
	static bool hitBase(HitSphere);
};

#endif