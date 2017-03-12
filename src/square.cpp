#include "square.h"
#include <cmath>

using namespace std;

Square::Square()
{

}

Square::Square(double x, double y, double r, double sx, double sy, double _s) : Obstacle(x, y)
{
    radius = r;
    scaleX = sx;
    scaleY = sy;
    s = _s;
}

void Square::SetRadius(double r)
{
    radius = r;
}

void Square::SetScale(double sx, double sy, double _s)
{
    scaleX = sx;
    scaleY = sy;
    s = _s;
}

double Square::Beta(double x, double y)
{
    return (pow((x-centerX)/scaleX,2)+pow((y-centerY)/scaleY,2)+sqrt(pow(pow((x-centerX)/scaleX,2)+pow((y-centerY)/scaleY,2),2)-4*s*s*pow((x-centerX)/scaleX,2)*pow((y-centerY)/scaleY,2)))/2-radius*radius;
}

double Square::Rho(double x, double y)
{
    double XX = (x-centerX)/scaleX;
    double YY = (y-centerY)/scaleY;
    double no = sqrt(XX*XX+YY*YY);
    double nno = sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
    return sqrt(pow(scaleX*(x-centerX)/nno,2)+pow(scaleY*(y-centerY)/nno,2))*sqrt(2)*radius/sqrt(1+sqrt(1-4*s*s*pow(XX/no,2)*pow(YY/no,2)));
}

double Square::GetMax()
{
    return radius*radius;
}
