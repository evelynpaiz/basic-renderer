/**
 * @brief Calculates a shadow value for a fragment using Percentage Closer Filtering (PCF).
 *
 * This function calculates a shadow value for a given fragment using Percentage Closer Filtering (PCF).
 * PCF is used to reduce aliasing and improve the quality of shadow rendering by considering multiple
 * samples from the shadow map and applying a filter to their results.
 *
 *  * @param shadowMap The sampler2D texture of the shadow map.
 * @param position The world-space position of the fragment to be shadowed.
 * @param bias The bias value used to prevent shadow acne and peter panning artifacts.
 * @param kernelSize The size of the PCF kernel (number of samples to take).
 * @param weight The weight value, which can be used as a sigma for Gaussian filtering or an opacity value.
 *
 * @return The calculated shadow value for the fragment.
 */
float calculateShadow(sampler2D shadowMap, vec4 position, float bias, int kernelSize, float weight)
{
    // Perform perspective divide to transform the fragment's position to normalized device coordinates
    vec3 projectionCoord = position.xyz / position.w;
    // Transform to [0, 1] range for texture sampling
    projectionCoord = projectionCoord * 0.5 + 0.5;

    // Calculate the size of a texel in the shadow map
    vec2 texelSize = 1.0f / textureSize(shadowMap, 0);
    
    // Call the PCF function to calculate the shadow value
    return PCF(shadowMap, projectionCoord, bias, texelSize, kernelSize, weight);
}
