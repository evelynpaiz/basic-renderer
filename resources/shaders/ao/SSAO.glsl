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
};

// Specify the output color of the fragment shader
layout (location = 0) out float occlusion;

// Uniform buffer blocks
uniform mat4 u_ViewProjection;      // Projection matrix
uniform mat4 u_InvViewProjection;
uniform Material u_Material;        // Material properties
uniform vec3 u_Kernel[64];          // Kernel samples

// Input variables from the vertex shader
in vec2 v_TextureCoord;             // Texture coordinates

// parameters (you'd probably want to use them as uniforms to more easily tweak the effect)
int kernelSize = 64;
float radius = 0.5f;
float bias = 0.0002f;

// Tile noise texture over screen based on screen dimensions divided by noise size
const vec2 noiseScale = vec2(800.0/4.0, 600.0/4.0);

/**
 * Calculate the view space position of a point in a depth map.
 *
 * This function takes a depth map, 2D coordinates, and a transformation matrix
 * to calculate the view space position of a point in the depth map.
 *
 * @param depthMap The depth map texture.
 * @param coords The 2D coordinates of the point in the depth map.
 * @param transform The transformation matrix to convert coordinates to view space.
 * @return The view space position of the point.
 */
vec3 calculateViewPosition(sampler2D depthMap, vec2 coords, mat4 transform) {
    // Get the depth value
    float fragmentDepth = texture(depthMap, coords).r;
    // Convert to normalized position coordinates
    vec4 ndc = vec4(vec3(coords, fragmentDepth) * 2.0f - 1.0f, 1.0f);
    // Transform to view space using the inverse camera projection matrix
    vec4 position = transform * ndc;
    // Perform perspective divide
    return position.xyz / position.w;
}


// Entry point of the fragment shader
void main()
{
    // Get the fragment positions in view space
    //vec3 position = texture(u_Material.PositionMap, v_TextureCoord).xyz;
    vec3 position = calculateViewPosition(u_Material.DepthMap, v_TextureCoord, u_InvViewProjection);
    // The dFdy and dFdX are glsl functions used to calculate two vectors in view space
    // that lie on the plane of the surface being drawn
    vec3 normal = cross(dFdy(position), dFdx(position));
    normal = normalize(normal * -1.0);
    // Calculate a random offset using the noise texture sample
    vec3 randomVec = normalize(texture(u_Material.NoiseMap, v_TextureCoord * noiseScale).xyz);
    // Create TBN change-of-basis matrix: from tangent-space to view-space
    vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
    //vec3 tangent = texture(u_Material.TangentMap, v_TextureCoord).xyz;
    vec3 bitangent = cross(normal, tangent);
    mat3 TBN = mat3(tangent, bitangent, normal);
    
    // Iterate over the sample kernel and calculate occlusion factor
    occlusion = 1.0f;
    for(int i = 0; i < kernelSize; ++i)
    {
        // Get sample position (from tangent to view-space)
        vec3 samplePosition = TBN * u_Kernel[i];
        samplePosition = position + samplePosition * radius;
        
        // Project sample position (to sample texture) (to get position on screen/texture)
        vec4 offset = vec4(samplePosition, 1.0f);
        offset = u_ViewProjection * offset;     // from view to clip-space
        offset.xyz /= offset.w;                 // perspective divide
        offset.xyz = offset.xyz * 0.5f + 0.5f;  // transform to range 0.0 - 1.0
        
        // Get sample depth
        float sampleDepth = calculateViewPosition(u_Material.DepthMap, offset.xy, u_InvViewProjection).z;
        
        // Range check & accumulate
        float rangeCheck = smoothstep(0.0f, 1.0f, radius / abs(position.z - sampleDepth));
        occlusion += (sampleDepth >= samplePosition.z + bias ? 1.0 : 0.0) * rangeCheck;
    }
    occlusion = occlusion / kernelSize;
}
