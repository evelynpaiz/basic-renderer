/**
 * Calculate the final color using Phong shading model with shadow consideration.
 *
 * @param ka Ambient reflection coefficient.
 * @param kd Diffuse reflection coefficient.
 * @param ks Specular reflection coefficient.
 * @param shadow Shadow factor (0.0 - 1.0), where 0.0 means fully lit and 1.0 means fully shadowed.
 *
 * @return Calculated color using Phong shading model with shadow.
 */
vec3 calculateColor(vec3 ka, vec3 kd, vec3 ks, float shadow)
{
    // Calculate the normalized surface normal
    vec3 normal = normalize(v_Normal);
        
    // Calculate the direction from the surface point to the light source
    vec3 lightDirection = normalize(u_Light.Position - v_Position);
    
    // Calculate the direction from the surface point to the viewer's eye
    vec3 viewDirection = normalize(u_View.Position - v_Position);
    
    // Calculate the reflection direction using the Phong reflection formula
    vec3 reflectionDirection = normalize(2.0 * dot(lightDirection, normal) * normal - lightDirection);
    
    // Calculate the distance from the light
    float lightDistance = length(u_Light.Position - v_Position);
    
    // Calculate the ambient reflection component by scaling the ambient color
    vec3 ambient = u_Light.La * ka;
    
    // Calculate the diffuse reflection component using the Lambertian cosine law
    float cosTheta = saturate(dot(normal, lightDirection));
    vec3 diffuse = u_Light.Ld * cosTheta * kd;
    
    // Calculate the specular reflection component using the Phong specular reflection formula
    vec3 specular = cosTheta > 0.0f ? calculateSpecular(viewDirection, reflectionDirection,
        ks, u_Material.Shininess) : vec3(0.0f);
    
    // Calculate the final color by combining ambient, diffuse, and specular components,
    // and modulating with the shadow factor
    vec3 result = ambient + (1.0 - shadow) * (diffuse + specular);
    
    // Calculate light attenuention
    float attenuation = 1.0 / (1.0f + 0.007f * lightDistance + 0.0002f * (lightDistance * lightDistance));
    result *= attenuation * u_Light.Color;
    
    return result;
}
