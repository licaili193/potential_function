cmake_minimum_required(VERSION 2.8.3)
project(potential_function)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include/${PROJECT_NAME}
)

add_executable(nf_tester src/main.cpp src/obstacle.cpp)

target_link_libraries(nf_tester
   ${catkin_LIBRARIES}
)

