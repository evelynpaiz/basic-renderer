#shader vertex
#version 330 core

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
    
    mat3 Normal;
};

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform Transform u_Transform;

out vec3 v_Position;
out vec3 v_Normal;

void main()
{
    // Transform to world space
    vec4 worldPosition = u_Transform.Model * a_Position;
    
    v_Position = worldPosition.xyz / worldPosition.w;
    v_Normal = u_Transform.Normal * a_Normal;
    
    // Define vertex position
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

struct Material {
    vec4 Color;
    
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
    
    float Shininess;
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
in vec3 v_Normal;

void main()
{
    // Calculate direction vectors
    vec3 normal = normalize(v_Normal);
    
    vec3 lightDirection = normalize(u_Light.Position - v_Position);
    vec3 viewDirection = normalize(u_View.Position - v_Position);
    
    vec3 reflectionDirection = normalize(2.0 * dot(lightDirection, normal) * normal - lightDirection);
    
    // Ambient component
    vec3 ambient = u_Light.Color * u_Material.Ka * u_Light.La;
    
    // Diffuse component
    float cosineTheta = max(0.0, dot(normal, lightDirection));
    vec3 diffuse = u_Light.Color * cosineTheta * u_Material.Kd * u_Light.Ld;
    
    // Specular component
    float specularStrength = 0.5;
    
    float cosinePhi = max(0.0, dot(viewDirection, reflectionDirection));
    vec3 specular = u_Light.Color * pow(cosinePhi, u_Material.Shininess) * u_Material.Ks * u_Light.Ls;
    
    // Define fragment color using Phong shading
    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, u_Material.Color.a);
}
