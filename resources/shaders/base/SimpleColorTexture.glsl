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

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 textureColor = texture(u_Texture, v_TextureCoord);
    
    color = textureColor * u_Color;
}
