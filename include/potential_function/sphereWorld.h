#ifndef __SPHEREWORLD
#define __SPHEREWORLD

#include "world.h"
#include "obstacle.h"

class SphereWorld : public World
{
public:
    SphereWorld();
    SphereWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o);

    double PotentialValue(double x, double y, double kappa);    
};

#endif