#include "worldManager.h"

#include <string>
#include <vector>
#include <map>
#include <utility>

#include "obstacle.h"
#include "world.h"
#include "sphereWorld.h"
#include "starWorld.h"
#include "purgedWorld.h"
#include "sphere.h"
#include "square.h"
#include "rectangle.h"

#include <cmath>
#include <cstddef>

using namespace std;

WorldManager::~WorldManager()
{
    ClearAll();
}

void WorldManager::ClearAll()
{
    while(!_worldVector.empty())
    {
        delete _worldVector[_worldVector.size()-1];
        _worldVector.pop_back();
    }

    map<string, Obstacle *>::iterator it = _obsMap.begin();
    while(it!=_obsMap.end()) {delete it->second; it++;}
    _obsMap.clear();
}

bool WorldManager::LoadXML(string address)
{
    //complete later
    ClearAll();
    return false;
}

World* WorldManager::GetWorld(int id)
{
    if(id<0||id>=_worldVector.size()) return NULL;
    return _worldVector[id];
}

Obstacle* WorldManager::FindObstacle(string key)
{
    return _obsMap.find(key)->second;
}

bool WorldManager::LoadSample()
{
    ClearAll();
    pair<string, Obstacle*>tempObs;
    World *tempWorld;

    //Obstacle: s1
    tempObs.first = "s1";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(0.26,0.565);
    static_cast<Sphere*>(tempObs.second)->SetRadius(1.622);
    _obsMap.insert(tempObs);
    //Obstacle: s2
    tempObs.first = "s2";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(-0.175,0.085);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.016);
    _obsMap.insert(tempObs);
    //Obstacle: s3
    tempObs.first = "s3";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(0.56,1.01);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.0165);
    _obsMap.insert(tempObs);

    //World: 0
    tempWorld = new SphereWorld;
    tempWorld->SetFrame(-1.562,2.082,-1.257,2.387,0.01);
    tempWorld->mainObs = FindObstacle("s1");
    tempWorld->obsArray.push_back(FindObstacle("s2"));
    tempWorld->obsArray.push_back(FindObstacle("s3"));
    tempWorld->destX = 1.2;
    tempWorld->destY = 1.2;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 5;
    tempWorld->lemmda = 10;
    _worldVector.push_back(tempWorld);

    //Obstacle: q1
    tempObs.first = "q1";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.26,0.565);
    static_cast<Square*>(tempObs.second)->SetRadius(1.131);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s1");
    _obsMap.insert(tempObs);
    //Obstacle: q2
    tempObs.first = "q2";
    tempObs.second = new Square;
    tempObs.second->SetCenter(-0.175,0.085);
    static_cast<Square*>(tempObs.second)->SetRadius(0.239);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s2");
    _obsMap.insert(tempObs);
    //Obstacle: q3
    tempObs.first = "q3";
    tempObs.second = new Rect;
    tempObs.second->SetCenter(0.51,1.01);
    static_cast<Rect*>(tempObs.second)->SetScale(0.45,0.245);
    tempObs.second->parentObs = FindObstacle("s3");
    _obsMap.insert(tempObs);

    //World: 1
    tempWorld = new StarWorld;
    tempWorld->SetFrame(-1.021,1.541,-0.716,1.846,0.01);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->destX = 1.2;
    tempWorld->destY = 1.2;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 50;
    tempWorld->SetParentWorld(GetWorld(0));
    _worldVector.push_back(tempWorld);

    //Obstacle: q4
    tempObs.first = "q4";
    tempObs.second = new Rect;
    tempObs.second->SetCenter(0.73,0.82);
    static_cast<Rect*>(tempObs.second)->SetScale(0.235,0.43);
    tempObs.second->parentObs = FindObstacle("q3");
    _obsMap.insert(tempObs);

    //Obstacle: v1
    tempObs.first = "v1";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.73,1.01);
    static_cast<Square*>(tempObs.second)->SetRadius(0.225);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    _obsMap.insert(tempObs);

    //World: 2
    tempWorld = new PurgedWorld;
    tempWorld->SetFrame(-1.021,1.541,-0.716,1.846,0.01);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->obsArray.push_back(FindObstacle("q4"));
    tempWorld->destX = 1.2;
    tempWorld->destY = 1.2;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 20;
    static_cast<PurgedWorld*>(tempWorld)->virtObs = FindObstacle("v1");
    static_cast<PurgedWorld*>(tempWorld)->newObs = FindObstacle("q4");
    tempWorld->SetParentWorld(GetWorld(1));
    _worldVector.push_back(tempWorld);
}

void WorldManager::SetGoal(double x, double y)
{
    for(int i=0;i<_worldVector.size();i++) {_worldVector[i]->destX=x;_worldVector[i]->destY=y;};
}

bool WorldManager::GetGrad(double x, double y, double acc, double &dx, double &dy, int world)
{
    if(world==-1) world = _worldVector.size()-1;
    double x1 = _worldVector[world]->PotentialValue(x-acc,y,_worldVector[world]->kappa);
    double x2 = _worldVector[world]->PotentialValue(x+acc,y,_worldVector[world]->kappa);
    double y1 = _worldVector[world]->PotentialValue(x,y-acc,_worldVector[world]->kappa);
    double y2 = _worldVector[world]->PotentialValue(x,y+acc,_worldVector[world]->kappa);
    if(x1==-1||x2==-1||y1==-1||y2==-1) return false;
    else
    {
        dx = x2-x1;
        dy = y2-y1;
        double norm = sqrt(dx*dx+dy*dy);
        if(norm==0) 
        {
            dx = 0; 
            dy = 0;
        }
        else 
        {
            dx /= norm;
            dy /= norm;
        }
        return true;
    }
}

double WorldManager::GetGamma(double x, double y, int world)
{
    if(world==-1) world = _worldVector.size()-1;
    return _worldVector[world]->GoalFunction(x, y);
}
