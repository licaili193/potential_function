#include "ros/ros.h"
#include "potential_function/GetPotentialGrad.h"

#include "worldManager.h"

WorldManager wm;

bool add(potential_function::GetPotentialGrad::Request  &req,
         potential_function::GetPotentialGrad::Response &res)
{
  ROS_INFO("request: x=%lf, y=%lf", (double)req.x, (double)req.y);

  wm.SetGoal(req.gx,req.gy);
  double dx,dy;
  if(wm.GetGrad(req.x,req.y,0.0000001,dx,dy))
  {
    res.res = 0;
    res.dx = dx;
    res.dy = dy;
    res.g = wm.GetGamma(req.x, req.y);
    ROS_INFO("sending back response: [%lf, %lf]", res.dx, res.dy);
  }
  else
  {
    res.res = 1;
    ROS_INFO("out of free space.");
  }
  
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nf_server");
  ros::NodeHandle n;

  wm.LoadSample();

  ros::ServiceServer service = n.advertiseService("nf_grad", add);
  ROS_INFO("Ready to calculate gradients.");
  ros::spin();

  return 0;
}
