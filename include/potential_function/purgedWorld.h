#ifndef __PURGEDWORLD
#define __PURGEDWORLD

#include "world.h"
#include "obstacle.h"

#include "starWorld.h"

class PurgedWorld : public World
{
    void Ti(double x, double y, StarTiInfo &ti, double &resX, double &resY);

public:
    Obstacle *virtObs;
    Obstacle *newObs;

    double gap;

    PurgedWorld();
    PurgedWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o);

    double PotentialValue(double x, double y, double kappa);   
};

#endif
