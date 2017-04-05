#ifndef __RECTANGLE
#define __RECTANGLE

#include "obstacle.h"

class Rect : public Obstacle
{
    double radius, scaleX, scaleY, s;
public:
    Rect();
    Rect(double x, double y, double r, double sx, double sy, double _s = 0.99);
    double Beta(double x, double y);
    double Rho(double x, double y);
    void SetRadius(double r);
    void SetScale(double sx, double sy, double _s = 0.99);
    double GetMax();
};

#endif
