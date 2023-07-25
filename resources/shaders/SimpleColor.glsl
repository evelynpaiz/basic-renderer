#shader vertex
#version 330 core

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
};

layout (location = 0) in vec4 a_Position;

uniform Transform u_Transform;

void main()
{
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

struct Material {
    vec4 Color;
};

layout (location = 0) out vec4 color;

uniform Material u_Material;

void main()
{
    color = u_Material.Color;
}
