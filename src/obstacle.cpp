#include "obstacle.h"
#include <cstddef>

Obstacle::Obstacle() {
  centerX = centerY = 0;
  parentObs = NULL;
}

Obstacle::Obstacle(double x, double y) {
  centerX = x;
  centerY = y;
  parentObs = NULL;
}

void Obstacle::SetCenter(double x, double y) {
  centerX = x;
  centerY = y;
}
