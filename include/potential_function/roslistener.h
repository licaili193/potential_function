#ifndef __ROSLISTENER
#define __ROSLISTENER

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <pthread.h>

class ROSListener
{
    pthread_t thread;
public:
    ~ROSListener();

    void Start();
    static void *Run(void *threadid);
    static void cmdCallback(const std_msgs::String::ConstPtr& msg);
};

#endif
