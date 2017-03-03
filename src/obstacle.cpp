#include "obstacle.h"

Obstacle::Obstacle()
{
   centerX = centerY = 0;
}

Obstacle::Obstacle(double x, double y)
{
   centerX = x;
   centerY = y;
}

void Obstacle::SetCenter(double x, double y)
{
   centerX = x;
   centerY = y;
}

