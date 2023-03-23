# Basic Renderer
This is a lightweight rendering pipeline using OpenGL.

## Requirements
* [Git](https://git-scm.com): used as the version control system.
* [CMake](https://cmake.org): used to generate the project solution. 
* [OpenGL](https://www.opengl.org/): used as a low level rendering library.
    
## Getting started
<ins>**1. Downloading the repository:**</ins>
Start by cloning the project from the git repository:
```
git clone --recursive https://github.com/epaizreyes/basic-renderer.git
```
and access the directory of the cloned repository `basic-renderer/`.

To clone the necessary submodules, if the repository was cloned non-recursively, use:
```
git submodule update --init
```

<ins>**2. Build the project solution:**</ins>
The project solution can be generated using CMake:

* **For Visual Studio**:
	```
	cmake -B VisualStudio
	```
	The Visual Studio solution `basic-renderer.sln` can be found in the `VisualStudio/` directory.

* **For XCode**:
	```
	cmake -G Xcode -B XCode
	```
	The XCode project solution `basic-renderer.xcodeproj` can be found in `XCode/` directory.

## Third party libraries
The external libraries needed in this project have been added as git submodules. These can be found in the `3rdparty/` directory.
* [glfw](https://github.com/glfw/glfw): Creation of windows, contexts and surfaces. It also receives inputs and events.
* [glew](https://github.com/nigels-com/glew): Loading library for Modern OpenGL.
* [stb](https://github.com/nothings/stb): Utility library. Specifically, we use stb-image for handling images.

## References
The four main references for this rendering engine are:
* [OpenGL Tutorial](https://github.com/TheCherno/OpenGL) from Yan Chernokov.
* [Hazel Engine](https://github.com/TheCherno/Hazel) from Yan Chernokov.
* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL) from Joey de Vries.
* [OpenGL Tutorial](https://github.com/VictorGordan/opengl-tutorials) from Victor Gordan.