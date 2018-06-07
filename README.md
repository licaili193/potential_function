# potential_function
Robot Navigation with Potential Functions Toolkit

MathGL

```
sudo apt-get install libmgl-dev
```

wxWidgets

See http://codelite.org/LiteEditor/WxWidgets31Binaries#toc2

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

## Navigation Functions Construction

### World

The navigation function is constructed with different layers of the worlds. At each layer, when a valid navigation function is built, a diffeomorphic transformation can be constructed to transform the current layer of the world to the next layer. Finally, the navigation function will be in the shape that we want. The typical layout setting for a navigation function is: __sphere world -> star world -> purged world 1 -> ... purged world n (final navigation function)__ 

![World 0](https://github.com/licaili193/potential_function/raw/master/screenshots/world0.png "The Zeroth World")
![World 1](https://github.com/licaili193/potential_function/raw/master/screenshots/world1.png "The First World")
![World 2](https://github.com/licaili193/potential_function/raw/master/screenshots/world2.png "The Second World")
![World 3](https://github.com/licaili193/potential_function/raw/master/screenshots/world3.png "The Thrid World")
