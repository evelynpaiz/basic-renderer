#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/SimpleMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/P.vs.glsl"

#shader fragment
#version 330 core

// Include material properties
#include "Resources/shaders/common/material/ColorMaterial.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/P.fs.glsl"

// Entry point of the fragment shader
void main()
{
    // Set the output color of the fragment shader to the material color
    color = u_Material.Color;
}
