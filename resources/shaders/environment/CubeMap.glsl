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
    
    // Remove translation from the view matrix
    mat4 view = mat4(mat3(u_Transform.View));
    // Calculate the final position of the vertex in clip space
    vec4 clipPosition = u_Transform.Projection * view * u_Transform.Model * a_Position;
    gl_Position = clipPosition.xyww;
}

#shader fragment
#version 330 core

/**
 * Represents the material properties of an object.
 */
struct Material {
    samplerCube TextureMap;             ///< Texture map applied to the material.
};

// Specify the output color of the fragment shader
layout (location = 0) out vec4 color;

// Uniform buffer blocks
uniform Material u_Material;        // Material properties

// Input variables from the vertex shader
in vec3 v_Position;                     ///< Vertex position in object space

// Entry point of the fragment shader
void main()
{
    // Sample the color from the texture using the provided texture coordinates
    vec4 textureColor = texture(u_Material.TextureMap, normalize(v_Position));
    // Set the output color of the fragment shader to the color from the texture
    color = textureColor;
}
