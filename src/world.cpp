#include "world.h"
#include <cmath>

using namespace std;

World::World(double xs, double xe, double ys, double ye, double st, Obstacle* o)
{
    SetFrame(xs,xe,ys,ye,st);
    mainObs = o;
}

World::World()
{
    destX = destY = 0;
    _parentWorld = nullptr;
}

void World::SetFrame(double xs, double xe, double ys, double ye, double st)
{
    _xStart = xs;
    _xEnd = xe;
    _yStart = ys;
    _yEnd = ye;
    _steps = st;

    destX = destY = rBubble = 0;
    _parentWorld = nullptr;
}

void World::GetFrame(double &xs, double &xe, double &ys, double &ye, double &st)
{
    xs = _xStart;
    xe = _xEnd;
    ys = _yStart;
    ye = _yEnd;
    st = _steps;
}

void World::SetParentWorld(World *p)
{
    _parentWorld = p;
}

double World::GoalFunction(double x, double y)
{
    return pow(sqrt((x-destX)*(x-destX)+(y-destY)*(y-destY))-rBubble,1);
}
