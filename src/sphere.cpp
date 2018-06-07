#include "sphere.h"
#include <cmath>

using namespace std;

Sphere::Sphere() {}

Sphere::Sphere(double x, double y, double r) : Obstacle(x, y) { radius = r; }

void Sphere::SetRadius(double r) { radius = r; }

double Sphere::Beta(double x, double y) {
  return (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY) -
         radius * radius;
}

double Sphere::Rho(double x, double y) { return radius; }

double Sphere::GetMax() { return radius * radius; }
