#include "ros/ros.h"
#include "std_msgs/String.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nf_tester");
  ros::NodeHandle n;
  ROS_INFO("Hello World!");
  ros::spin();
  return 0;
}

