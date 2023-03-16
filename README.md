# Basic Renderer
This is a lightweight rendering pipeline using OpenGL.

## Requirements

* [Premake](https://premake.github.io/download): used to generate the project solution. 
* [OpenGL](https://www.opengl.org/): used as a low level rendering library.
* 3rd Party Libraries: external libraries needed in this project.
    * [glfw](https://github.com/glfw/glfw): Creation of windows, contexts and surfaces. It also receives inputs and events.
    * [glew](https://github.com/nigels-com/glew): Loading library for Modern OpenGL.
    * [stb](https://github.com/nothings/stb): Utility library. Specifically, we use stb-image for handling images.
    
## Generate the project solution

Create the project solution in the main folder `basic-renderer\` by calling [premake](https://premake.github.io/docs/Using-Premake):
```
premake5 [action]
```
where `action` represents what type of project files to be generated.

For example, generate a Visual Studio 2022 project solution using the command:
```
premake5 vs2022
```
or generate a Xcode project solution using the command:
```
premake5 xcode4
```

## References
The three main references for this rendering engine are:
* [OpenGL Tutorial](https://github.com/TheCherno/OpenGL) from Yan Chernokov.
* [Hazel Engine](https://github.com/TheCherno/Hazel) from Yan Chernokov.
* [Learn OpenGL](https://github.com/JoeyDeVries/LearnOpenGL) from Joey de Vries.
* [OpenGL Tutorial](https://github.com/VictorGordan/opengl-tutorials) from Victor Gordan.