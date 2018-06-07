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
