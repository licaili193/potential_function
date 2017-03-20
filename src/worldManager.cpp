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
    tempObs.second->SetCenter(0.417,1.859);
    static_cast<Sphere*>(tempObs.second)->SetRadius(1.622);
    _obsMap.insert(tempObs);
    //Obstacle: s2
    tempObs.first = "s2";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(-0.004,1.361);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.239);
    _obsMap.insert(tempObs);
    //Obstacle: s3
    tempObs.first = "s3";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(0.927,2.272);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.245);
    _obsMap.insert(tempObs);

    //World: 0
    tempWorld = new SphereWorld;
    tempWorld->SetFrame(-1.405,2.239,0.037,3.681,0.01);
    tempWorld->mainObs = FindObstacle("s1");
    tempWorld->obsArray.push_back(FindObstacle("s2"));
    tempWorld->obsArray.push_back(FindObstacle("s3"));
    tempWorld->destX = 0.417;
    tempWorld->destY = 1.859;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 1.9;
    _worldVector.push_back(tempWorld);

    //Obstacle: q1
    tempObs.first = "q1";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.417,1.859);
    static_cast<Square*>(tempObs.second)->SetRadius(1.081);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s1");
    _obsMap.insert(tempObs);
    //Obstacle: q2
    tempObs.first = "q2";
    tempObs.second = new Square;
    tempObs.second->SetCenter(-0.004,1.361);
    static_cast<Square*>(tempObs.second)->SetRadius(0.239);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s2");
    _obsMap.insert(tempObs);
    //Obstacle: q3
    tempObs.first = "q3";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.927,2.272);
    static_cast<Square*>(tempObs.second)->SetRadius(0.245);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s3");
    _obsMap.insert(tempObs);

    //World: 1
    tempWorld = new StarWorld;
    tempWorld->SetFrame(-0.864,1.698,0.578,3.14,0.01);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->destX = 0.417;
    tempWorld->destY = 1.859;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 40;
    tempWorld->SetParentWorld(GetWorld(0));
    _worldVector.push_back(tempWorld);

    //Obstacle: q4
    tempObs.first = "q4";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.763,2.272);
    static_cast<Square*>(tempObs.second)->SetRadius(0.235);
    static_cast<Square*>(tempObs.second)->SetScale(2,1);
    tempObs.second->parentObs = FindObstacle("q2");
    _obsMap.insert(tempObs);

    //World: 2
    tempWorld = new PurgedWorld;
    tempWorld->SetFrame(-0.864,1.698,0.578,3.14,0.01);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->obsArray.push_back(FindObstacle("q4"));
    tempWorld->destX = 0.417;
    tempWorld->destY = 1.859;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 150;
    static_cast<PurgedWorld*>(tempWorld)->virtObs = FindObstacle("q2");
    static_cast<PurgedWorld*>(tempWorld)->newObs = FindObstacle("q4");
    tempWorld->SetParentWorld(GetWorld(1));
    _worldVector.push_back(tempWorld);

    //Obstacle: q5
    tempObs.first = "q5";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0.927,2.12);
    static_cast<Square*>(tempObs.second)->SetRadius(0.235);
    static_cast<Square*>(tempObs.second)->SetScale(1,2);
    tempObs.second->parentObs = FindObstacle("q2");
    _obsMap.insert(tempObs);

    //World: 3
    tempWorld = new PurgedWorld;
    tempWorld->SetFrame(-0.864,1.698,0.578,3.14,0.01);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->obsArray.push_back(FindObstacle("q4"));
    tempWorld->obsArray.push_back(FindObstacle("q5"));
    tempWorld->destX = 0.417;
    tempWorld->destY = 1.859;
    tempWorld->rBubble = 0.05;
    tempWorld->kappa = 150;
    static_cast<PurgedWorld*>(tempWorld)->virtObs = FindObstacle("q2");
    static_cast<PurgedWorld*>(tempWorld)->newObs = FindObstacle("q5");
    tempWorld->SetParentWorld(GetWorld(2));
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
