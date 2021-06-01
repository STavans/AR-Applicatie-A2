#include "HitSphere.h"

#include <math.h>

HitSphere::HitSphere(double xDouble, double yDouble, double radiusDouble)
{
	x = xDouble;
	y = yDouble;
	radius = radiusDouble;
}

int HitSphere::hit(HitSphere sphere1, HitSphere sphere2)
{
	double xDiff = fabs(sphere1.x - sphere2.x);
	double yDiff = fabs(sphere1.y - sphere2.y);
	double maxDistance = sphere1.radius + sphere2.radius;

	double distance = sqrt(xDiff * xDiff + yDiff * yDiff);

	return distance <= maxDistance;
}