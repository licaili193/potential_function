#include "ros/ros.h"
#include "std_msgs/String.h"
#include <mgl2/mgl.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "obstacle.h"

using namespace cv;

int sample(mglGraph *gr)
{
  gr->Rotate(60,40);
  gr->Box();
  return 0;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nf_tester");
  ros::NodeHandle n;
  ROS_INFO("Hello World!");

  Obstacle O(0,0);

  mglData dat(30,40);	// data to for plotting
  for(long i=0;i<30;i++)   for(long j=0;j<40;j++)
    dat.a[i+30*j] = 1/(1+(i-15)*(i-15)/225.+(j-20)*(j-20)/400.);

  mglGraph gr;		// class for plot drawing
  gr.Rotate(50,60);	// rotate axis
  gr.Light(true);	// enable lighting
  gr.Surf(dat);		// plot surface
  gr.Cont(dat,"y");	// plot yellow contour lines
  gr.Axis();		// draw axis
  gr.WriteFrame("sample.png");	// save it
                                         // Wait for a keystroke in the window
  ROS_INFO("Object created!");

  ros::spin();
  return 0;
}




