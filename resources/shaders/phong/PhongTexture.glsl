#shader vertex
#version 330 core

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
    
    mat3 Normal;
};

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
layout (location = 2) in vec3 a_Normal;

uniform Transform u_Transform;

out vec3 v_Position;
out vec2 v_TextureCoord;
out vec3 v_Normal;

void main()
{
    // Transform to world space
    vec4 worldPosition = u_Transform.Model * a_Position;
    
    v_Position = worldPosition.xyz / worldPosition.w;
    v_TextureCoord = a_TextureCoord;
    v_Normal = u_Transform.Normal * a_Normal;
    
    // Define vertex position
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

struct Material {
    sampler2D Td;
    sampler2D Ts;
    
    float Shininess;
    float Alpha;
};

struct View {
    vec3 Position;
};

struct Light {
    vec3 Position;
    
    vec3 Color;
    
    float La;
    float Ld;
    float Ls;
};

layout (location = 0) out vec4 color;

uniform View u_View;
uniform Light u_Light;

uniform Material u_Material;

in vec3 v_Position;
in vec2 v_TextureCoord;
in vec3 v_Normal;

void main()
{
    // Calculate direction vectors
    vec3 normal = normalize(v_Normal);
    
    vec3 lightDirection = normalize(u_Light.Position - v_Position);
    vec3 viewDirection = normalize(u_View.Position - v_Position);
    
    vec3 reflectionDirection = normalize(2.0 * dot(lightDirection, normal) * normal - lightDirection);
    
    // Get the texture map information
    vec4 kd = texture(u_Material.Td, v_TextureCoord);
    vec4 ks = texture(u_Material.Ts, v_TextureCoord);
    
    // Ambient component
    vec3 ambient = u_Light.Color * u_Light.La * vec3(kd);
    
    // Diffuse component
    float cosineTheta = max(0.0, dot(normal, lightDirection));
    vec3 diffuse = u_Light.Color * u_Light.Ld * vec3(kd) * cosineTheta;
    
    // Specular component
    float specularStrength = 0.5;
    
    float cosinePhi = max(0.0, dot(viewDirection, reflectionDirection));
    vec3 specular = u_Light.Color * u_Light.Ls * vec3(ks) * pow(cosinePhi, u_Material.Shininess);
    
    // Define fragment color using Phong shading
    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, u_Material.Alpha);
}
