#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/CompleteMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PTN-S.vs.glsl"

#shader fragment
#version 330 core

// Include material, view and light properties
#include "Resources/shaders/common/material/PhongTextureMaterial.glsl"
#include "Resources/shaders/common/view/SimpleView.glsl"
#include "Resources/shaders/common/light/ShadowLight.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/PTN.fs.glsl"
#include "Resources/shaders/common/fragment/L.fs.glsl"

// Include additional functions
#include "Resources/shaders/common/utils/Saturate.glsl"
#include "Resources/shaders/common/utils/Attenuation.glsl"

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
    vec3 lightDirection = u_Light.Vector.w == 1.0f ?
                            normalize(u_Light.Vector.xyz - v_Position)      // positional light (.w = 1)
                            : normalize(-u_Light.Vector.xyz);               // directional light (.w = 0)
    
    // Get the diffuse color (kd) from the DiffuseMap texture
    vec3 kd = vec3(texture(u_Material.DiffuseMap, v_TextureCoord));
    
    // Get the specular color (ks) from the SpecularMap texture
    vec3 ks = vec3(texture(u_Material.SpecularMap, v_TextureCoord));
    
    // Calculate shadow factor
    float bias = calculateBias(normal, lightDirection, 0.005f, 0.01f);
    float shadow = calculateShadow(u_Light.ShadowMap, v_LightSpacePosition, bias, 3, 1.0f);
    
    // Define fragment color using Phong shading
    // Parameters: Diffuse color (kd), Diffuse color (kd), Specular color (ks), Shadow factor
    vec3 result = calculateColor(kd, kd, ks, shadow, 0.045f, 0.0075f, 0.7f);
    
    // Set the fragment color with the calculated result and material's alpha
    color = vec4(result, u_Material.Alpha);
}
