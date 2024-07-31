#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
};

uniform Transform u_Transform;

void main()
{
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

uniform vec3 u_Color;

void main()
{
    color = vec4(u_Color, 1.0f);
}
