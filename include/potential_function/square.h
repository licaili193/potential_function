#ifndef __SQUARE
#define __SQUARE

#include "obstacle.h"

class Square : public Obstacle
{
    double radius, scaleX, scaleY, s;
public:
    Square();
    Square(double x, double y, double r, double sx, double sy, double _s = 0.99);
    double Beta(double x, double y);
    double Rho(double x, double y);
    void SetRadius(double r);
    void SetScale(double sx, double sy, double _s = 0.99);
    double GetMax();
};

#endif
