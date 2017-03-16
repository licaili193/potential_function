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
    tempObs.second->SetCenter(0,0);
    static_cast<Sphere*>(tempObs.second)->SetRadius(6);
    _obsMap.insert(tempObs);
    //Obstacle: s2
    tempObs.first = "s2";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(2,2);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.5);
    _obsMap.insert(tempObs);
    //Obstacle: s3
    tempObs.first = "s3";
    tempObs.second = new Sphere;
    tempObs.second->SetCenter(-2,-2);
    static_cast<Sphere*>(tempObs.second)->SetRadius(0.5);
    _obsMap.insert(tempObs);

    //World: 0
    tempWorld = new SphereWorld;
    tempWorld->SetFrame(-6.2,6.2,-6.2,6.2,0.02);
    tempWorld->mainObs = FindObstacle("s1");
    tempWorld->obsArray.push_back(FindObstacle("s2"));
    tempWorld->obsArray.push_back(FindObstacle("s3"));
    tempWorld->destX = -3.2;
    tempWorld->destY = 3.2;
    tempWorld->rBubble = 0.2;
    tempWorld->kappa = 1.9;
    _worldVector.push_back(tempWorld);

    //Obstacle: q1
    tempObs.first = "q1";
    tempObs.second = new Square;
    tempObs.second->SetCenter(0,0);
    static_cast<Square*>(tempObs.second)->SetRadius(4);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s1");
    _obsMap.insert(tempObs);
    //Obstacle: q2
    tempObs.first = "q2";
    tempObs.second = new Square;
    tempObs.second->SetCenter(2,2);
    static_cast<Square*>(tempObs.second)->SetRadius(0.6);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s2");
    _obsMap.insert(tempObs);
    //Obstacle: q3
    tempObs.first = "q3";
    tempObs.second = new Square;
    tempObs.second->SetCenter(-2,-2);
    static_cast<Square*>(tempObs.second)->SetRadius(0.6);
    static_cast<Square*>(tempObs.second)->SetScale(1,1);
    tempObs.second->parentObs = FindObstacle("s3");
    _obsMap.insert(tempObs);

    //World: 1
    tempWorld = new StarWorld;
    tempWorld->SetFrame(-4.2,4.2,-4.2,4.2,0.02);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->destX = -3.2;
    tempWorld->destY = 3.2;
    tempWorld->rBubble = 0.2;
    tempWorld->kappa = 5000;
    tempWorld->SetParentWorld(GetWorld(0));
    _worldVector.push_back(tempWorld);

    //Obstacle: q4
    tempObs.first = "q4";
    tempObs.second = new Square;
    tempObs.second->SetCenter(2,1.4);
    static_cast<Square*>(tempObs.second)->SetRadius(0.6);
    static_cast<Square*>(tempObs.second)->SetScale(1,2);
    tempObs.second->parentObs = FindObstacle("q2");
    _obsMap.insert(tempObs);

    //World: 2
    tempWorld = new PurgedWorld;
    tempWorld->SetFrame(-4.2,4.2,-4.2,4.2,0.02);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->obsArray.push_back(FindObstacle("q4"));
    tempWorld->destX = -3.2;
    tempWorld->destY = 3.2;
    tempWorld->rBubble = 0.2;
    tempWorld->kappa = 100000;
    static_cast<PurgedWorld*>(tempWorld)->virtObs = FindObstacle("q2");
    static_cast<PurgedWorld*>(tempWorld)->newObs = FindObstacle("q4");
    tempWorld->SetParentWorld(GetWorld(1));
    _worldVector.push_back(tempWorld);

    //Obstacle: q5
    tempObs.first = "q5";
    tempObs.second = new Square;
    tempObs.second->SetCenter(1.4,2);
    static_cast<Square*>(tempObs.second)->SetRadius(0.6);
    static_cast<Square*>(tempObs.second)->SetScale(2,1);
    tempObs.second->parentObs = FindObstacle("q2");
    _obsMap.insert(tempObs);

    //World: 3
    tempWorld = new PurgedWorld;
    tempWorld->SetFrame(-4.2,4.2,-4.2,4.2,0.02);
    tempWorld->mainObs = FindObstacle("q1");
    tempWorld->obsArray.push_back(FindObstacle("q2"));
    tempWorld->obsArray.push_back(FindObstacle("q3"));
    tempWorld->obsArray.push_back(FindObstacle("q4"));
    tempWorld->obsArray.push_back(FindObstacle("q5"));
    tempWorld->destX = -3.2;
    tempWorld->destY = 3.2;
    tempWorld->rBubble = 0.2;
    tempWorld->kappa = 3000000;
    static_cast<PurgedWorld*>(tempWorld)->virtObs = FindObstacle("q2");
    static_cast<PurgedWorld*>(tempWorld)->newObs = FindObstacle("q5");
    tempWorld->SetParentWorld(GetWorld(2));
    _worldVector.push_back(tempWorld);
}

void WorldManager::SetGoal(double x, double y)
{
    for(int i=0;i<_worldVector.size();i++) {_worldVector[i]->destX=x;_worldVector[i]->destY=y;};
}
