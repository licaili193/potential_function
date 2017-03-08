#include "ros/ros.h"
#include "std_msgs/String.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    bool isRun = true;
    ros::init(argc, argv, "nf_tester");
    ros::NodeHandle n;
    ROS_INFO("Hello World!");
    ros::Publisher nf_pub = n.advertise<std_msgs::String>("nf_cmd", 1000);
  
    while(isRun)
    {
        string cmd;
        cout<<"Please input the command: ";
        cin>>cmd;
        
        std_msgs::String msg;
        msg.data = cmd.c_str();

        nf_pub.publish(msg);
        ros::spinOnce();
        if(cmd=="exit") {isRun=false; break;}
    }
    return 0;
}




