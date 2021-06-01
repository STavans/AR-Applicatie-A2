#pragma once
#ifndef HITSPHERE_H
#define HITSPHERE_H

class HitSphere
{
	double x, y, radius;

public:
	HitSphere(double, double, double);
	static int hit(HitSphere, HitSphere);
};

int hit(HitSphere, HitSphere);

#endif