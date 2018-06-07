#include "sphereWorld.h"
#include <cmath>
#include "world.h"

using namespace std;

SphereWorld::SphereWorld() : World() {}

SphereWorld::SphereWorld(double xs, double xe, double ys, double ye, double st,
                         Obstacle* o)
    : World(xs, xe, ys, ye, st, o) {}

double SphereWorld::PotentialValue(double x, double y, double kappa) {
  double ommitProduct, temp;
  temp = mainObs->Beta(x, y);
  if (temp > 0) return -1;
  ommitProduct = -temp;
  int length = obsArray.size();
  for (int i = 0; i < length; i++) {
    temp = obsArray[i]->Beta(x, y);
    if (temp < 0) return -1;
    ommitProduct *= temp;
  }
  return (GoalFunction(x, y) /
          pow((pow(GoalFunction(x, y), kappa) + ommitProduct), 1 / kappa));
}
