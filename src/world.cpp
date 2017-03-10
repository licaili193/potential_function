#include "world.h"

World::World(double xs, double xe, double ys, double ye, double st, Obstacle* o)
{
    SetFrame(xs,xe,ys,ye,st);
    mainObs = o;
}

World::World()
{
    
}

void World::SetFrame(double xs, double xe, double ys, double ye, double st)
{
    _xStart = xs;
    _xEnd = xe;
    _yStart = ys;
    _yEnd = ye;
    _steps = st;
}

void World::GetFrame(double &xs, double &xe, double &ys, double &ye, double &st)
{
    xs = _xStart;
    xe = _xEnd;
    ys = _yStart;
    ye = _yEnd;
    st = _steps;
}
