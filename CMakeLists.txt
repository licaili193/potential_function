cmake_minimum_required(VERSION 2.8.3)
project(potential_function)

set(mgl2_LIBRARIES /usr/local/lib/libmgl.so)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
)

find_package(wxWidgets COMPONENTS core base REQUIRED)

find_package( PkgConfig REQUIRED)
pkg_check_modules( gsl REQUIRED gsl )

add_service_files(FILES GetPotentialGrad.srv)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy std_msgs
)

set(wxWidgets_CONFIGURATION mswu)
include(${wxWidgets_USE_FILE})

include_directories(
  ${catkin_INCLUDE_DIRS}
  include/${PROJECT_NAME}
  include/mathgl
)

add_executable(nf_tester src/main.cpp)

target_link_libraries(nf_tester
   ${catkin_LIBRARIES}
)

add_executable(nf_visualization 
src/nf_visualization.cpp 
src/roslistener.cpp 
src/visualizer.cpp 
src/world.cpp 
src/obstacle.cpp 
src/sphere.cpp 
src/square.cpp
src/rectangle.cpp
src/sphereWorld.cpp
src/starWorld.cpp
src/purgedWorld.cpp
src/worldManager.cpp)

target_link_libraries(nf_visualization
   ${catkin_LIBRARIES}
   ${wxWidgets_LIBRARIES}
   ${mgl2_LIBRARIES}
)

add_executable(nf_server 
src/gradServer.cpp
src/world.cpp 
src/obstacle.cpp 
src/sphere.cpp 
src/square.cpp
src/rectangle.cpp
src/sphereWorld.cpp
src/starWorld.cpp
src/purgedWorld.cpp
src/worldManager.cpp)

target_link_libraries(nf_server ${catkin_LIBRARIES} ${mgl2_LIBRARIES})
add_dependencies(nf_server ${PROJECT_NAME}_generate_messages_cpp)
