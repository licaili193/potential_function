#include "ros/ros.h"
#include "std_msgs/String.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "nf_visualization");
  ros::NodeHandle n;
  ROS_INFO("This node will create a window for visualization.");

  Mat image;
  image = imread("sample.png", CV_LOAD_IMAGE_COLOR);   // Read the file

  if(! image.data )                              // Check for invalid input
  {
      ROS_INFO("Cannot show image.");
      return -1;
  }

  namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Display window", image );                   // Show our image inside it.
  waitKey(0);     

  ros::spin();
  return 0;
}




