#include "purgedWorld.h"
#include "starWorld.h"
#include <vector>
#include <cmath>

#include <iostream>

using namespace std;

PurgedWorld::PurgedWorld()
{
    virtObs = NULL;
    newObs = NULL;
    gap = 0.05;
}

PurgedWorld::PurgedWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o):World(xs,xe,ys,ye,st,o)
{
    virtObs = NULL;
    newObs = NULL;
    gap = 0.05;
}

void PurgedWorld::Ti(double x, double y, StarTiInfo &ti,  double &resX, double &resY)
{
    if(ti.x0==x&&ti.y0==y)
    {
        resX = x;
        resY = y;
        return;
    }

    double norm = sqrt((x-ti.x0)*(x-ti.x0)+(y-ti.y0)*(y-ti.y0));
    double v = (1+ti.betaSon)*ti.rhoParent/norm;

    resX = v*(x-ti.x0)+ti.x0;
    resY = v*(y-ti.y0)+ti.y0;
}

double PurgedWorld::PotentialValue(double x, double y, double kappa)
{
    vector<double>betas;
    double theBeta = mainObs->Beta(x,y);
    int length = obsArray.size();

    if(theBeta>0) return -1;
    betas.clear();

    double product = 1;
    for(int i=0;i<length;i++)
    {
        double temp = obsArray[i]->Beta(x,y);
        if(temp<0) return -1;
        betas.push_back(temp);
        product *= temp;
    }

    double theNewBeta = newObs->Beta(x,y);

    double theParentBeta = newObs->parentObs->Beta(x,y);
    product = product*theBeta/theParentBeta/theNewBeta;

    double gamma = GoalFunction(x,y);

    double betaP = theParentBeta+(2*gap-theNewBeta)+sqrt(theParentBeta*theParentBeta+(2*gap-theNewBeta)*(2*gap-theNewBeta));

    double tempB = -gamma*product*betaP;
    double s0 = tempB/(tempB+kappa*theNewBeta);

    double theS = 1-s0;

    double tempX, tempY;
    StarTiInfo T0 = {virtObs->centerX,virtObs->centerY,virtObs->Rho(x,y),theNewBeta};
    Ti(x,y,T0,tempX,tempY);

    double resX = theS*x+s0*tempX;
    double resY = theS*y+s0*tempY;

    return _parentWorld->PotentialValue(resX,resY,_parentWorld->kappa);
}
