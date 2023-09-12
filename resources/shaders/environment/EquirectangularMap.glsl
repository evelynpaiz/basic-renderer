#shader vertex
#version 330 core

// Include transformation matrices
#include "Resources/shaders/common/matrix/SimpleMatrix.glsl"

// Input vertex attributes
layout (location = 0) in vec4 a_Position;   // Vertex position in object space

// Uniform buffer block containing transformation matrices
uniform Transform u_Transform;

// Outputs to fragment shader
out vec3 v_Position;                        // Vertex position in object space

// Entry point of the vertex shader
void main()
{
    // Pass the object space coordinates
    v_Position = a_Position.xyz;

    // Calculate the final position of the vertex in clip space
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

// Include material properties
#include "Resources/shaders/common/material/TextureMaterial.glsl"

// Specify the output color of the fragment shader
layout (location = 0) out vec4 color;

// Uniform buffer blocks
uniform Material u_Material;        // Material properties

// Input variables from the vertex shader
in vec3 v_Position;                 // Vertex position in object space

// Define constant variables
const vec2 invAtan = vec2(0.1591, 0.3183);

/**
 * Inverse tangent and spherical mapping function.
 *
 * This function calculates 2D texture coordinates (UV) for spherical mapping
 * based on a 3D vector 'v', which typically represents a normalized direction
 * vector from the origin to a point on a sphere. The resulting UV coordinates
 * are used for texture sampling on a spherical texture map.
 *
 * @param v The 3D vector representing a point on a unit sphere.
 *
 * @return The 2D texture coordinates (UV) mapped to the spherical map.
 */
vec2 sampleSphericalMap(vec3 v)
{
    // Calculate the azimuth (horizontal angle) and inclination (vertical angle)
    // of the input 3D vector and map them to UV coordinates.
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    
    // Scale the UV coordinates using the provided inverse tangent values.
    uv *= invAtan;
    
    // Offset the UV coordinates to ensure they are in the [0, 1] range.
    uv += 0.5f;
    
    return uv;
}

// Entry point of the fragment shader
void main()
{
    // Sample the color from the texture using the provided texture coordinates
    vec4 textureColor = texture(u_Material.TextureMap, sampleSphericalMap(normalize(v_Position)));
    // Set the output color of the fragment shader to the color from the texture
    color = textureColor;
}
