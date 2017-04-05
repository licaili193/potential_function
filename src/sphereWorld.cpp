#include "sphereWorld.h"
#include "world.h"
#include <cmath>

using namespace std;

SphereWorld::SphereWorld():World()
{
    lemmda = 1;
}

SphereWorld::SphereWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o):World(xs,xe,ys,ye,st,o)
{
    lemmda = 1;
}

double SphereWorld::PotentialValue(double x, double y, double kappa)
{
    double ommitProduct, temp;
    temp = mainObs->Beta(x,y);
    if(temp>0) return -1;
    ommitProduct = -temp;
    int length = obsArray.size();
    for(int i=0;i<length;i++)
    {
        temp = obsArray[i]->Beta(x,y);
        if(temp<0) return -1;
        ommitProduct*=temp;
    }
    return (GoalFunction(x,y)/pow((pow(GoalFunction(x,y),kappa)+lemmda*ommitProduct),1/kappa));
}
