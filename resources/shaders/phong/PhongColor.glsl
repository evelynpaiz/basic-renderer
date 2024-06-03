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
#include "Resources/shaders/common/light/EnvironmentLight.glsl"

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
    // Define the initial reflectance
    vec3 reflectance = vec3(0.0f);
    
    // Shade based on each light source in the scene
    for(int i = 0; i < u_Environment.LightsNumber; i++)
    {
        // Calculate the shading result using Phong shading model
        reflectance += calculateColor(v_Position, v_Normal, u_View.Position, u_Light[i].Vector, u_Light[i].Color,
                                      u_Material.Kd * u_Light[i].Ld, u_Material.Ks * u_Light[i].Ls,
                                      u_Material.Shininess, 0.0f, 0.045f, 0.0075f, 0.7f);
    }
    
    // Calculate the irradiance value
    vec3 irradiance = texture(u_Environment.IrradianceMap, v_Normal).rgb;
    // Calculate the ambient light
    vec3 ambient = u_Material.Ka * u_Environment.La * irradiance;
    
    // Set the fragment color with the calculated result and material's alpha
    vec3 result = reflectance + ambient;
    color = vec4(result, u_Material.Alpha);
}
