#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/NormalMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PTN.vs.glsl"

#shader fragment
#version 330 core

// Include material, view and light properties
#include "Resources/shaders/common/material/PhongTextureMaterial.glsl"
#include "Resources/shaders/common/view/SimpleView.glsl"
#include "Resources/shaders/common/light/SimpleLight.glsl"

// Include fragment inputs
#include "Resources/shaders/common/fragment/PTN.fs.glsl"

// Include additional functions
#include "Resources/shaders/common/utils/Saturate.glsl"
#include "Resources/shaders/common/shading/PhongSpecular.glsl"
#include "Resources/shaders/common/shading/Phong.glsl"

// Entry point of the fragment shader
void main()
{
    // Get the diffuse color (kd) from the DiffuseMap texture
    vec3 kd = vec3(texture(u_Material.DiffuseMap, v_TextureCoord));
    
    // Get the specular color (ks) from the SpecularMap texture
    vec3 ks = vec3(texture(u_Material.SpecularMap, v_TextureCoord));
    
    // Define fragment color using Phong shading
    // Parameters: Diffuse color (kd), Diffuse color (kd), Specular color (ks), Shadow factor (0.0f)
    vec3 result = calculateColor(kd, kd, ks, 0.0f);
    
    // Set the fragment color with the calculated result and material's alpha
    color = vec4(result, u_Material.Alpha);
}
