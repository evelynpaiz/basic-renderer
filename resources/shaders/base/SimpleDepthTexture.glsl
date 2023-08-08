#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
};

uniform Transform u_Transform;

out vec2 v_TextureCoord;

void main()
{
    v_TextureCoord = a_TextureCoord;
    
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TextureCoord;

uniform sampler2D u_Texture;

float linearizeDepth(float depth, float near, float far)
{
    float z = depth * 2.0 - 1.0; // back to NDC coordinates
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    // Near and far plane
    // TODO: pass it as uniforms
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    float depthValue = texture(u_Texture, v_TextureCoord).r;
    
    // Display the depth map,
    // for orthographic use: color = vec4(vec3(depthValue), 1.0);
    // for pespective use: color = vec4(vec3(linearizeDepth(depthValue, nearPlane, farPlane) / farPlane), 1.0);
    color = vec4(vec3(linearizeDepth(depthValue, nearPlane, farPlane) / farPlane), 1.0);
}
