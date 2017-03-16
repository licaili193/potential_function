#include "ros/ros.h"
#include "std_msgs/String.h"
#include <pthread.h>

#include <iostream>

#include "roslistener.h"

params Msg;

void ROSListener::Start()
{
    int rc;
    Msg.mutex = PTHREAD_MUTEX_INITIALIZER;
    //Msg.done = PTHREAD_COND_INITIALIZER;
    rc = pthread_create(&thread, NULL, Run, (void *)&Msg);
}

int ROSListener::Kill()
{
    system("rosnode kill nf_visualization"); 
    //pthread_exit(NULL);
    return 0;
}

ROSListener::~ROSListener()
{
    pthread_mutex_destroy(&Msg.mutex);
}

void ROSListener::cmdCallback(const std_msgs::String::ConstPtr& msg)
{
    std::cout<<"I heard: "<<msg->data.c_str()<<std::endl;
    pthread_mutex_lock(&Msg.mutex);
    Msg.cmd = msg->data.c_str();
    pthread_mutex_unlock(&Msg.mutex);

    if(msg->data=="exit") 
    {
        system("rosnode kill nf_visualization"); 
        //pthread_exit(NULL);
    }
}

void * ROSListener::Run(void *msg)
{   
    int argc = 0;
    char **argv = NULL;
    ros::init(argc, argv, "nf_visualization");
    ros::NodeHandle n;
    ROS_INFO("This node will create a window for visualization.");
    ros::Subscriber sub = n.subscribe("nf_cmd", 1000, cmdCallback);
    ros::spin();
    pthread_exit(NULL);
}
