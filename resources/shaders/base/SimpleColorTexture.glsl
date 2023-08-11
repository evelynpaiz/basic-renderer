#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/SimpleMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PT.vs.glsl"

#shader fragment
#version 330 core

// Include material properties
#include "Resources/shaders/common/material/ColorTextureMaterial.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/T.fs.glsl"

// Entry point of the fragment shader
void main()
{
    // Sample the color from the texture using the provided texture coordinates
    vec4 textureColor = texture(u_Material.TextureMap, v_TextureCoord);

    // Combine the sampled texture color with the material color
    color = textureColor * u_Material.Color;
}
