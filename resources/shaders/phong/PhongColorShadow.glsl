#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/CompleteMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PN-S.vs.glsl"

#shader fragment
#version 330 core

// Include material, view and light properties
#include "Resources/shaders/common/material/PhongColorMaterial.glsl"
#include "Resources/shaders/common/view/SimpleView.glsl"
#include "Resources/shaders/common/light/ShadowLight.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/PN.fs.glsl"
#include "Resources/shaders/common/fragment/L.fs.glsl"

// Include additional functions
#include "Resources/shaders/common/utils/Saturate.glsl"
#include "Resources/shaders/phong/chunks/PhongSpecular.glsl"
#include "Resources/shaders/phong/chunks/Phong.glsl"

#include "Resources/shaders/depth/chunks/PCF.glsl"
#include "Resources/shaders/depth/chunks/BiasAngle.glsl"
#include "Resources/shaders/depth/chunks/ShadowMap.glsl"

// Entry point of the fragment shader
void main()
{
    // Calculate the normalized surface normal
    vec3 normal = normalize(v_Normal);
    
    // Calculate the normalized light direction vector
    vec3 lightDirection;
    if (u_Light.Vector.w == 1.0f)
        lightDirection = normalize(u_Light.Vector.xyz - v_Position);
    else if (u_Light.Vector.w == 0.0f)
        lightDirection = normalize(-u_Light.Vector.xyz);
    
    // Calculate shadow factor
    float bias = calculateBias(normal, lightDirection, 0.005f, 0.01f);
    float shadow = calculateShadow(u_Light.ShadowMap, v_LightSpacePosition, bias, 3, 1.0f);
    
    // Calculate shading result using Phong shading model with shadows
    // Parameters: Ambient reflection (ka), Diffuse reflection (kd),
    // Specular reflection (ks), Shadow factor (calculated above)
    vec3 result = calculateColor(u_Material.Ka, u_Material.Kd, u_Material.Ks, shadow);
    
    // Set the fragment color with the calculated result and material's alpha
    color = vec4(result, u_Material.Alpha);
}
