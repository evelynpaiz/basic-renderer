/**
 * Calculate the shadow value for a fragment.
 *
 * @param position The position of the fragment in view space.
 * @param lightDistance The distance between the light source and the fragment.
 * @param maxDistance The maximum distance to the light source.
 *
 * @return The shadow value for the fragment.
 */
float calculateShadow(vec4 position, float lightDistance, float maxDistance)
{
    // Convert the fragment's position to normalized device coordinates
    vec3 projectionCoord = position.xyz / position.w;
    // Transform to [0, 1] range for texture sampling
    projectionCoord = projectionCoord * 0.5 + 0.5;
    
    // Keep the shadow at 1.0 when outside the far plane region of the light's frustum
    if (projectionCoord.z > 1.0)
        return 1.0f;

    // Define bias values based on light distance
    float nearBias = 0.005f;   // Bias when the light is close
    float farBias = 0.0f;      // Bias when the light is far
    // Normalize the light distance and calculate the bias using a mix
    float normalizedDistance = lightDistance / maxDistance;
    float bias = mix(nearBias, farBias, normalizedDistance);
    
    // Calculate the size of a texel in the shadow map
    vec2 texelSize = 1.0f / textureSize(u_Light.ShadowMap, 0);
    
    // Call the PCF function to calculate the shadow value
    // Using a kernel size of 15 and a Gaussian distribution with a sigma of 2.75
    return PCF(projectionCoord, bias, texelSize, 15, 2.75f);
}
