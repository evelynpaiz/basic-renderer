#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 v_TextureCoord;

uniform mat4 u_Transform;

void main()
{
    v_TextureCoord = a_TextureCoord;
    gl_Position = u_Transform * a_Position;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TextureCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 inputColor = u_Color;
    vec4 textureColor = texture(u_Texture, v_TextureCoord);
    
    color = mix(inputColor, textureColor, 0.6f);
}
