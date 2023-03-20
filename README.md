# Basic Renderer
This is a lightweight rendering pipeline using OpenGL.

## Requirements

* [CMake](https://cmake.org): used to generate the project solution. 
* [OpenGL](https://www.opengl.org/): used as a low level rendering library.
* 3rd Party Libraries: external libraries needed in this project.
    * [glfw](https://github.com/glfw/glfw): Creation of windows, contexts and surfaces. It also receives inputs and events.
    * [glew](https://github.com/nigels-com/glew): Loading library for Modern OpenGL.
    * [stb](https://github.com/nothings/stb): Utility library. Specifically, we use stb-image for handling images.
    
# Build the project solution

Clone the project from the git repository:
```
git clone git@github.com:epaizreyes/basic-renderer
cd basic-renderer
```

The project solution can be generated using CMake:
1. For Visual Studio:
```
cmake -B VisualStudio
```
The VisualStudio solution `basic-renderer.sln` can be found in the `VisualStudio` directory.
2. For XCode:

```
cmake -G Xcode -B XCode
```
The XCode project solution `basic-renderer.xcodeproj` can be found in `XCode` directory.

## References
The three main references for this rendering engine are:
* [OpenGL Tutorial](https://github.com/TheCherno/OpenGL) from Yan Chernokov.
* [Hazel Engine](https://github.com/TheCherno/Hazel) from Yan Chernokov.
* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL) from Joey de Vries.
* [OpenGL Tutorial](https://github.com/VictorGordan/opengl-tutorials) from Victor Gordan.