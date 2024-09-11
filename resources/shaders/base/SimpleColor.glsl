#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/shared/structure/matrix/SimpleMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/shared/chunk/vertex/Pos.vs.glsl"

#shader fragment
#version 330 core

// Include material properties
#include "Resources/shaders/shared/structure/material/ColorMaterial.glsl"

// Include fragment inputs
#include "Resources/shaders/shared/chunk/fragment/Base.fs.glsl"

// Entry point of the fragment shader
void main()
{
    // Set the output color of the fragment shader to the material color
    color = u_Material.Color;
}
