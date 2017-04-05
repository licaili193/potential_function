#include "starWorld.h"
#include <vector>
#include <cmath>

#include <iostream>

using namespace std;

StarWorld::StarWorld()
{

}

StarWorld::StarWorld(double xs, double xe, double ys, double ye, double st, Obstacle* o):World(xs,xe,ys,ye,st,o)
{

}

void StarWorld::Ti(double x, double y, StarTiInfo &ti,  double &resX, double &resY, bool isMain, double maxMain)
{
    if(ti.x0==x&&ti.y0==y)
    {
        resX = x;
        resY = y;
        return;
    }

    double norm = sqrt((x-ti.x0)*(x-ti.x0)+(y-ti.y0)*(y-ti.y0));
    double v;
    if(isMain) v = (1-pow(ti.betaSon/maxMain,4))*ti.rhoParent/norm;
    else v = (1+ti.betaSon)*ti.rhoParent/norm;

    resX = v*(x-ti.x0)+ti.x0;
    resY = v*(y-ti.y0)+ti.y0;
}

double StarWorld::PotentialValue(double x, double y, double kappa)
{
    vector<double>betas;
    vector<double>s;
    double theBeta = mainObs->Beta(x,y);
    int length = obsArray.size();

    if(theBeta>0) return -1;
    betas.clear();
    s.clear();

    double product = 1;
    for(int i=0;i<length;i++)
    {
        double temp = obsArray[i]->Beta(x,y);
        if(temp<0) return -1;
        betas.push_back(temp);
        product *= temp;
    }

    double gamma = GoalFunction(x,y);
    double s0 = gamma*product/(gamma*product-kappa*theBeta);

    double theS = 1-s0;

    for(int i=0;i<length;i++)
    {
        double ommitProduct = -product*theBeta/betas[i];
        s.push_back(gamma*ommitProduct/(gamma*ommitProduct+kappa*betas[i]));
        theS-=s[i];
    }

    double tempX, tempY;
    StarTiInfo T0 = {mainObs->centerX,mainObs->centerY,mainObs->parentObs->Rho(x,y),-theBeta};
    Ti(x,y,T0,tempX,tempY,true,mainObs->GetMax());

    double resX = theS*x+s0*tempX;
    double resY = theS*y+s0*tempY;

    for(int i=0;i<length;i++)
    {
        StarTiInfo T = {obsArray[i]->centerX,obsArray[i]->centerY,obsArray[i]->parentObs->Rho(x,y),betas[i]};
        Ti(x,y,T,tempX,tempY);
        resX+=s[i]*tempX;
        resY+=s[i]*tempY;
    }

    return _parentWorld->PotentialValue(resX,resY,_parentWorld->kappa);
}
