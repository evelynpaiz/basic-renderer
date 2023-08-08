#shader vertex
#version 330 core

struct Transform {
    mat4 Model;
    mat4 View;
    mat4 Projection;
    
    mat3 Normal;
    mat4 Light;
};

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;
layout (location = 2) in vec3 a_Normal;

uniform Transform u_Transform;

out vec4 v_LightSpacePosition;

out vec3 v_WorldPosition;
out vec2 v_TextureCoord;
out vec3 v_Normal;

void main()
{
    vec4 worldPosition = u_Transform.Model * a_Position;
    vec4 lightSpacePosition = u_Transform.Light * worldPosition;
    
    v_LightSpacePosition = lightSpacePosition;              // Store vertex position in light space
    
    v_WorldPosition = worldPosition.xyz / worldPosition.w;  // Perspective divide to get world space position
    v_TextureCoord = a_TextureCoord;                        // Pass through texture coordinate
    v_Normal = u_Transform.Normal * a_Normal;               // Transform normal to world space
    
    // Calculate final vertex position in clip space
    gl_Position = u_Transform.Projection * u_Transform.View * u_Transform.Model * a_Position;
}

#shader fragment
#version 330 core

struct Material {
    sampler2D DiffuseMap;
    sampler2D SpecularMap;
    
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
    
    sampler2D ShadowMap;
};

layout (location = 0) out vec4 color;

uniform View u_View;
uniform Light u_Light;

uniform Material u_Material;

in vec4 v_LightSpacePosition;

in vec3 v_WorldPosition;
in vec2 v_TextureCoord;
in vec3 v_Normal;

float saturate(float x) {
    return clamp(x, 0.0f, 1.0f);
}

vec3 calculateSpecular(vec3 V, vec3 R, vec3 ks, float shininess)
{
    float cosPhi = saturate(dot(V, R));
    return pow(cosPhi, shininess) * ks;
}

float calculateShadow(vec3 N, vec3 L, vec4 position)
{
    vec3 projectionCoord = position.xyz / position.w;   // Perform perspective divide
    projectionCoord = projectionCoord * 0.5 + 0.5;      // Transform to [0,1] range
    
    // Keep the shadow at 0.0 when outside the far plane region of the light's frustum
    if(projectionCoord.z > 1.0)
        return 0.0f;
        
    // Get closest depth value from light's perspective
    float closestDepth = texture(u_Light.ShadowMap, projectionCoord.xy).r;
    // Get depth of current fragment from light's perspective
    float currentDepth = projectionCoord.z;
    // Define a bias to remove shadow acne (generally needs to be fine tuned)
    // use for orthographic projection: float bias = max(0.05 * (1.0 - dot(N, L)), 0.03);
    // user for perspective projection: float bias = max(0.01 * (1.0 - dot(N, L)), 0.005);
    float bias = max(0.01 * (1.0 - dot(N, L)), 0.005);
    // Check whether current fragment pos is in shadow (currently using PCF to filter)
    float shadow = 0.0f;
    vec2 texelSize = 1.0f / textureSize(u_Light.ShadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
       for(int y = -1; y <= 1; ++y)
       {
           float pcfDepth = texture(u_Light.ShadowMap, projectionCoord.xy + vec2(x, y) * texelSize).r;
           shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
       }
    }
    shadow /= 9.0f;
    
    return shadow;
}

void main()
{
    // Calculate direction vectors
    vec3 normal = normalize(v_Normal);
    
    vec3 lightDirection = normalize(u_Light.Position - v_WorldPosition);
    vec3 viewDirection = normalize(u_View.Position - v_WorldPosition);
    
    vec3 reflectionDirection = normalize(2.0 * dot(lightDirection, normal) * normal - lightDirection);
    
    // Get the texture map information
    vec3 kd = vec3(texture(u_Material.DiffuseMap, v_TextureCoord));
    vec3 ks = vec3(texture(u_Material.SpecularMap, v_TextureCoord));
    
    // Ambient component
    vec3 ambient = u_Light.La * kd;
    
    // Diffuse component
    
    float cosTheta = saturate(dot(normal, lightDirection));
    vec3 diffuse = u_Light.Ld * cosTheta * kd;
    
    // Specular component
    vec3 specular = cosTheta > 0.0f ? calculateSpecular(viewDirection, reflectionDirection,
        ks, u_Material.Shininess) : vec3(0.0f);
    
    // Shadows
    float shadow = calculateShadow(normal, lightDirection, v_LightSpacePosition);
    
    // Define fragment color using Phong shading
    vec3 result = u_Light.Color * (ambient + (1.0 - shadow) * (diffuse + specular));
    color = vec4(result, u_Material.Alpha);
}
