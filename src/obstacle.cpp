#include "obstacle.h"

Obstacle::Obstacle()
{
   centerX = centerY = 0;
   parentObs = nullptr;
}

Obstacle::Obstacle(double x, double y)
{
   centerX = x;
   centerY = y;
   parentObs = nullptr;
}

void Obstacle::SetCenter(double x, double y)
{
   centerX = x;
   centerY = y;
}

