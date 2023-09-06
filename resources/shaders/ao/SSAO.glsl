#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/SimpleMatrix.glsl"

// Include vertex shader
#include "Resources/shaders/common/vertex/PT.vs.glsl"

#shader fragment
#version 330 core

/**
 * Represents the material properties of an object.
 */
struct Material {
    sampler2D DepthMap;
    sampler2D NoiseMap;
    
    int SampleCount;
    
    float Radius;
    float Bias;
};

// Specify the output color of the fragment shader
layout (location = 0) out float occlusion;

const int MAX_KERNEL = 128;

// Uniform buffer blocks
uniform mat4 u_ViewProjection;          // Projection matrix
uniform mat4 u_InvViewProjection;       // Inverse projection matrix
uniform Material u_Material;            // Material properties
uniform vec3 u_Kernel[MAX_KERNEL];      // Kernel samples

// Input variables from the vertex shader
in vec2 v_TextureCoord;                 // Texture coordinates

// Include additional functions
#include "Resources/shaders/ao/chunks/PositionFromDepth.glsl"

// Entry point of the fragment shader
void main()
{
    // Get the fragment positions in view space
    vec3 position = calculateViewPosition(u_Material.DepthMap, v_TextureCoord, u_InvViewProjection);
    // The dFdy and dFdX are glsl functions used to calculate two vectors in view space
    // that lie on the plane of the surface being drawn
    vec3 normal = cross(dFdy(position), dFdx(position));
    normal = normalize(normal * -1.0f);
    // Calculate a random offset using the noise texture sample
    vec2 noiseScale = vec2(textureSize(u_Material.DepthMap, 0)) * 0.25f;
    vec3 randomVector = normalize(texture(u_Material.NoiseMap, v_TextureCoord * noiseScale).xyz);
    // Create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVector - normal * dot(randomVector, normal));
    //vec3 tangent = texture(u_Material.TangentMap, v_TextureCoord).xyz;
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    
    // Iterate over the sample kernel and calculate occlusion factor
    occlusion = 0.0f;
    for(int i = 0; i < u_Material.SampleCount; ++i)
    {
        // Get sample position (from tangent to view-space)
        vec3 samplePosition = TBN * u_Kernel[i];
        samplePosition = position + samplePosition * u_Material.Radius;
        
        // Project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(samplePosition, 1.0f);
        offset = u_ViewProjection * offset;     // from view to clip-space
        offset.xyz /= offset.w;                 // perspective divide
        offset.xyz = offset.xyz * 0.5f + 0.5f;  // transform to range 0.0 - 1.0
        
        // Get sample depth
        float sampleDepth = calculateViewPosition(u_Material.DepthMap, offset.xy, u_InvViewProjection).z;
        
        // Range check & accumulate
        float rangeCheck = smoothstep(0.0f, 1.0f, u_Material.Radius / abs(position.z - sampleDepth));
        occlusion += (sampleDepth >= samplePosition.z + u_Material.Bias ? 1.0f : 0.0f) * rangeCheck;
    }
    occlusion = occlusion / u_Material.SampleCount;
}
