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
vec3 calculateColor(vec3 ka, vec3 kd, vec3 ks, float shadow,
                    float lightLinear, float lightQuadratic, float maxAttenuation)
{
    // Calculate the surface vector(s)
    vec3 normal = normalize(v_Normal);
    
    // Calculate the direction vectors
    vec3 lightDirection = u_Light.Vector.w == 1.0f ?
                            normalize(u_Light.Vector.xyz - v_Position)      // positional light (.w = 1)
                            : normalize(-u_Light.Vector.xyz);               // directional light (.w = 0)
    vec3 viewDirection = normalize(u_View.Position - v_Position);
    vec3 reflectionDirection = normalize(2.0 * dot(lightDirection, normal) * normal - lightDirection);
    
    // Calculate the light radiance
    vec3 radiance = u_Light.Color * calculateAttenuation(v_Position, u_Light.Vector, lightLinear, lightQuadratic, maxAttenuation);
    
    // Calculate the ambient reflection component by scaling the ambient color
    vec3 ambient = u_Light.La * ka;
    
    // Calculate the diffuse reflection component using the Lambertian cosine law
    float cosTheta = saturate(dot(normal, lightDirection));
    vec3 diffuse = u_Light.Ld * cosTheta * kd;
    
    // Calculate the specular reflection component using the Phong specular reflection formula
    vec3 specular = cosTheta > 0.0f ? calculateSpecular(viewDirection, reflectionDirection,
        ks, u_Material.Shininess) : vec3(0.0f);
    specular *= u_Light.Ls;
    
    // Calculate the final color by combining ambient, diffuse, and specular components,
    // and modulating with the shadow factor
    vec3 result = ambient + radiance * (1.0 - shadow) * (diffuse + specular);
    
    return result;
}
