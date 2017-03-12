#ifndef __WORLD
#define __WORLD

#include <vector>
#include "obstacle.h"

using namespace std;

class World
{
protected:
    double _steps,_xStart,_xEnd,_yStart,_yEnd;
    World *_parentWorld;
public:
    Obstacle *mainObs;
    vector<Obstacle *>obsArray;

    double destX, destY, rBubble;
    double kappa;

    World();
    World(double xs, double xe, double ys, double ye, double st, Obstacle* o);
    void SetFrame(double xs, double xe, double ys, double ye, double st);
    void GetFrame(double &xs, double &xe, double &ys, double &ye, double &st);

    void SetParentWorld(World *p);

    double GoalFunction(double x, double y);
    virtual double PotentialValue(double x, double y, double kappa) {return 0;}
};

#endif
