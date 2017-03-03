#include "ros/ros.h"
#include "std_msgs/String.h"

#include "obstacle.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nf_tester");
  ros::NodeHandle n;
  ROS_INFO("Hello World!");

  Obstacle O(0,0);
  ROS_INFO("Object created!");

  ros::spin();
  return 0;
}

