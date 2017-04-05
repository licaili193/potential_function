#include "rectangle.h"
#include <cmath>

using namespace std;

Rect::Rect()
{

}

Rect::Rect(double x, double y, double r, double sx, double sy, double _s) : Obstacle(x, y)
{
    radius = r;
    scaleX = sx;
    scaleY = sy;
    s = _s;
}

void Rect::SetRadius(double r)
{
    radius = r;
}

void Rect::SetScale(double sx, double sy, double _s)
{
    scaleX = sx;
    scaleY = sy;
    s = _s;
}

double Rect::Beta(double x, double y)
{
    return pow(x-centerX,2)+pow(y-centerY,2)-pow(scaleX,2)-pow(scaleY,2)+sqrt(pow(pow(x-centerX,2)-pow(scaleX,2)-pow(y-centerY,2)+pow(scaleY,2),2)+(1-s*s)*pow(x-centerX,2)*pow(y-centerY,2));
}

double Rect::Rho(double x, double y)
{
    return 0;
}

double Rect::GetMax()
{
    double m = scaleX<scaleY?scaleX:scaleY;
    return 2*m*m;
}
