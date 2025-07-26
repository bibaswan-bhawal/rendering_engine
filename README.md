# Rendering Engine Experiment

### introduction

This is an experiment in creating a rendering engine to learn about openGL and graphics rendering.

### Building

For now this project is designed to run on MacOS, it can easily be modified to run on other platforms and in the future it may be adjusted to run on other platforms.

#### MacOS

The following commands will build the project for MacOS

```zsh
mkdir build && cd build
cmake ..
make
```

This should output a executable binary called `./rendering_app` in the `build` folder.

#### Other platforms

This project uses [glfw](https://www.glfw.org/) to create a window and work with OpenGL. The binaries for MacOS have been bundled in with this project under `third_part/glfw-3.4`. If you would like to run this project on other platforms you can replace these binaries with the binaries for your platform and update the `CMakeLists.txt` file to build the project with the new binaries.
