# Potential Function

Robot Navigation with Potential Functions Toolkit. This ROS toolkit is written by Caili Li (caili@udel.edu) for the master thesis of the MSME program at the University of Delaware. 

Advisor: Herbert G. Tanner (btanner@udel.edu)

## Dependences

This toolkit is tested under Ubuntu 16.04 LTS and ROS Kinetic Kame

__MathGL__

To install: 

```
sudo apt-get install libmgl-dev
```

__wxWidgets__

To install:

See http://codelite.org/LiteEditor/WxWidgets31Binaries#toc2

## How To Run

* Step 1: Install ROS, set up `catkin` workspace, clone this package and compile

* Step 2: Run ROS core
  ```
  $ roscore
  ```

* Step 3: In another terminal under the `catkin` workspace, run
  ```
  $ source devel/setup.bash
  $ rosrun potential_function nf_visualization
  ```
  
* Step 4: In another terminal under the `catkin` workspace, run
  ```
  $ rostopic pub -1 /nf_cmd std_msgs/String "goal -0.3 1"
  $ rostopic pub -1 /nf_cmd std_msgs/String "world 3"
  ```
  You will see a window popup with a sample navigation function visualized.

## Executables

### `nf_visualization`

Visualize contour plots of each layers of the navigation function worlds. There is a simple command line interface implemented in the visualizer. For each command, one or more parameters could be added and whitespace should be used to separate them. The available commands are: 

* `exit` Exit the visualization window

  - __Available parameters__: none

  - __Example__: `exit` This command will close the visualization window

* `goal` Set the goal position of the navigation function

  - __Available parameters__: 

    `x`

    *Type*: `double`

    *Description*: specify the *x* coordinate of the destination

    `y`

    *Type*: `double`

    *Description*: specify the *y* coordinate of the destination

  - __Example__: `goal 1.2 -0.4` This command above will set the destination of the navigation function to point (*1.2, -0.4*)

* `world` Plot a specific layer of the navigation function

  - __Available parameters__: 

    `world_number`
    
    *Type*: `int`
    
    *Description*: specify which layer of the world that should be plotted (the definition of the world layer is listed below)

  - __Example__: `world 0` The command above will plot the sphere world of the navigation function

### `nf_server`

The `nf_server` will load a navigation function construction and set up a ROS server. Giving a interested point in the workspace, the service will return the negative gradient direction of the potential field indicating the desired moving direction for the robot. The service is defined as:

```
# Inputs:
float64 x   # robot position x coordinate
float64 y   # robot position y coordinate
float64 gx  # goal position x coordinate
float64 gy  # goal position y coordinate
---
# Outputs:
int32 res   # success indicator and error codes
float64 dx  # normalized negative gradient x component
float64 dy  # normalized negative gradient y component
float64 g   # potential value
```

## Navigation Functions Construction

### World

The navigation function is constructed with different layers of the worlds. At each layer, when a valid navigation function is built, a diffeomorphic transformation can be constructed to transform the current layer of the world to the next layer. Finally, the navigation function will be in the shape that we want. The typical layout setting for a navigation function is: __sphere world -> star world -> purged world 1 -> ... purged world n (final navigation function)__ 

---

![World 0](https://github.com/licaili193/potential_function/raw/master/screenshots/world0.png "The Zeroth World")

__Sphere world__: all the obstacles are spheres 

---

![World 1](https://github.com/licaili193/potential_function/raw/master/screenshots/world1.png "The First World")

__Star world__: obstacles can be star-shapes (rectangles)

---

![World 2](https://github.com/licaili193/potential_function/raw/master/screenshots/world2.png "The Second World")

__Purged world 1__: introduced one new obstacle with purging transformation (we can introduce one or more new obstacles within one purging transformation, however, the current implementation of this package can only support one obstacle to be purged at each purged world layer)

---

![World 3](https://github.com/licaili193/potential_function/raw/master/screenshots/world3.png "The Thrid World")

__Purged world 2__: the final navigation function we want

---

The `class WorldManager` is used to construct the worlds. The user should design the hierarchical layers of the navigation functions (worlds), and this class provided a way to describe the hierarchy relationship with input parameters. The construction of the navigation function is now hard coded in the function

```
bool WorldManager::LoadSample();
```

__*TODO: finish the function `bool WorldManager::LoadXML(string address);` to support designing and loading navigation function construction from a XML file*__ 

Different kinds of worlds are described by the `class SphereWorld`, the `class StarWorld`, and the `class PurgedWorld`, which are derived from the base `class World`. For each layer of the worlds, there is a certain set of parameters to describe the weight factors in the transformation. Now, those factors can be set with the constructor of each kinds of the world.

__*TODO: support loading and adjusting navigation function construction parameters on the fly*__

When finished constructing the navigation function, call the member function

```
void WorldManager::SetGoal(double x, double y);
```

to set the goal position, and call the member function

```
bool WorldManager::GetGrad(double x, double y, double acc, double &dx, double &dy, int world=-1);
```

to get the gradient of the navigation function at a given position, and call the member function

```
double WorldManager::GetGamma(double x, double y, int world=-1);
```

to get the actual potential field value at a given position.

### Obstacles

There are two kinds of obstacles: spheres and squares. They are discribed by the `class Sphere` and the `class Square`, which are derived from the base `class Obstacle`. For a sphere, the user can set the center position and the radius of it. For a square, the user can set the center position, dimensions, and how rounded the corner is. Now, the user can make a square into a rounded rectangle by setting it scaling dimensions. 

__*TODO: support rotation of the rectangular obstacles*__

For each obstacle, the function

```
double Obstacle::Beta(double x, double y);
```

will return the contour value of its implicit representation at a given position, and the function

```
double Obstacle::Rho(double x, double y);
```

will return the "radius" length from the center to its boundary at a given position.
