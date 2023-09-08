#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/NormalMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PN.vs.glsl"

#shader fragment
#version 330 core

// Include material, view and light properties
#include "Resources/shaders/common/material/PhongColorMaterial.glsl"
#include "Resources/shaders/common/view/SimpleView.glsl"
#include "Resources/shaders/common/light/SimpleLight.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/PN.fs.glsl"

// Include additional functions
#include "Resources/shaders/common/utils/Saturate.glsl"
#include "Resources/shaders/common/utils/Attenuation.glsl"

#include "Resources/shaders/phong/chunks/PhongSpecular.glsl"
#include "Resources/shaders/phong/chunks/Phong.glsl"

// Entry point of the fragment shader
void main()
{
    // Calculate the shading result using Phong shading model
    // Parameters: Ambient reflection (ka), Diffuse reflection (kd),
    // Specular reflection (ks), Shadow factor (0.0f for no shadow)
    vec3 result = calculateColor(u_Material.Ka, u_Material.Kd, u_Material.Ks, 0.0f, 0.045f, 0.0075f, 0.7f);

    // Set the fragment color with the calculated result and material's alpha
    color = vec4(result, u_Material.Alpha);
}
