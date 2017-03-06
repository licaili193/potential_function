cmake_minimum_required(VERSION 2.8.3)
project(potential_function)

set(mgl2_LIBRARIES /usr/local/lib/libmgl.so)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

find_package(OpenCV 3 REQUIRED)
find_package(wxWidgets COMPONENTS core base REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs
)

set(wxWidgets_CONFIGURATION mswu)
include(${wxWidgets_USE_FILE})

include_directories(
  ${catkin_INCLUDE_DIRS}
  include/${PROJECT_NAME}
  ${OpenCV_INCLUDE_DIRS}
  include/mathgl
)

add_executable(nf_tester src/main.cpp src/obstacle.cpp)

target_link_libraries(nf_tester
   ${catkin_LIBRARIES}
   ${mgl2_LIBRARIES}
)

add_executable(nf_visualization src/nf_visualization.cpp src/plot.cpp)

target_link_libraries(nf_visualization
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
   ${wxWidgets_LIBRARIES}
   ${mgl2_LIBRARIES}
)

