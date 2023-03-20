#shader vertex
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 v_TextureCoord;

void main()
{
    v_TextureCoord = uv;
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
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
    vec4 inputColor = u_Color;
    
    color = textureColor;
}