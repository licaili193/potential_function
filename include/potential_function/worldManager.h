#ifndef __WORLDMANAGER
#define __WORLDMANAGER

#include <string>
#include <vector>
#include <map>

#include "obstacle.h"
#include "world.h"

using namespace std;

class WorldManager
{
    vector<World *>_worldVector;
    map<string, Obstacle *>_obsMap;

    Obstacle* FindObstacle(string key);
public:
    ~WorldManager();

    bool LoadXML(string address);
    bool LoadSample();
    World* GetWorld(int id);
    void ClearAll();
    void SetGoal(double x, double y);
    bool GetGrad(double x, double y, double acc, double &dx, double &dy, int world=-1);
    double GetGamma(double x, double y, int world=-1);
};

#endif
