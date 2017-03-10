#ifndef __WORLD
#define __WORLD

#include <vector>
#include "obstacle.h"

using namespace std;

class World
{
    double _steps,_xStart,_xEnd,_yStart,_yEnd;
public:
    Obstacle *mainObs;
    vector<Obstacle *>obsArray;

    World();
    World(double xs, double xe, double ys, double ye, double st, Obstacle* o);
    void SetFrame(double xs, double xe, double ys, double ye, double st);
    void GetFrame(double &xs, double &xe, double &ys, double &ye, double &st);
};

#endif
