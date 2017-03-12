#ifndef __STARWORLD
#define __STARWORLD

#include "world.h"
#include "obstacle.h"

struct StarTiInfo
{
    double x0, y0, rhoParent, betaSon;
};

class StarWorld : public World
{
    void Ti(double x, double y, StarTiInfo &ti, double &resX, double &resY);

public:
    StarWorld();
    StarWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o);

    double PotentialValue(double x, double y, double kappa);   
};

#endif
