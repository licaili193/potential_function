#ifndef __SPHERE
#define __SPHERE

#include "obstacle.h"

class Sphere: public Obstacle
{
    double radius;
public:
    Sphere();
    Sphere(double x, double y, double r);
    double Beta(double x, double y);
    double Rho(double x, double y);
    void SetRadius(double r);
    double GetMax();
};

#endif
