/**
 * Calculate the shadow value for a fragment.
 *
 * @param N The normalized surface normal at the fragment.
 * @param L The normalized light direction vector.
 * @param position The position of the fragment in view space.
 *
 * @return The shadow value for the fragment.
 */
float calculateShadow(vec3 N, vec3 L, vec4 position)
{
    // Perform perspective divide to transform the fragment's position to normalized device coordinates
    vec3 projectionCoord = position.xyz / position.w;
    // Transform to [0, 1] range for texture sampling
    projectionCoord = projectionCoord * 0.5 + 0.5;
    
    // Keep the shadow at 0.0 when outside the far plane region of the light's frustum
    if (projectionCoord.z > 1.0)
        return 0.0f;

    // Define a bias to remove shadow acne
    // The bias is calculated based on the dot product of the normal and light direction
    float bias = max(0.01 * (1.0 - dot(N, L)), 0.005);

    // Calculate the size of a texel in the shadow map
    vec2 texelSize = 1.0f / textureSize(u_Light.ShadowMap, 0);
    
    // Call the PCF function to calculate the shadow value using a kernel size of 9
    return PCF(projectionCoord, bias, texelSize, 9);
}
