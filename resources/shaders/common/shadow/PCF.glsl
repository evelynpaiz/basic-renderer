/**
 * Percentage Closer Filtering (PCF) for shadow mapping.
 *
 * @param projectionCoord The normalized device coordinates of the fragment.
 * @param bias The bias to adjust shadow comparisons.
 * @param texelSize The size of a texel in the shadow map.
 * @param kernelSize The size of the PCF kernel.
 *
 * @return The shadow value for the fragment.
 */
float PCF(vec3 projectionCoord, float bias, vec2 texelSize, int kernelSize)
{
    // Get depth of current fragment from light's perspective
    float currentDepth = projectionCoord.z;
    // Initialize shadow value
    float shadow = 0.0f;
    
    // Calculate half of the kernel size
    int halfKernel = kernelSize / 2;
    
    // Loop over the PCF kernel
    for(int x = -halfKernel; x <= halfKernel; ++x)
    {
       for(int y = -halfKernel; y <= halfKernel; ++y)
       {
           // Compute an offset based on the current kernel sample
           vec2 sampleOffset = vec2(x, y) * texelSize;
           
           // Sample the shadow map at the offset position
           float pcfDepth = texture(u_Light.ShadowMap, projectionCoord.xy + sampleOffset).r;
           
           // Update the shadow value using the sampled depth and bias
           shadow += currentDepth - bias > pcfDepth ? 1.0f : 0.0f;
       }
    }
    
    // Normalize the shadow value by the number of samples
    shadow /= float(kernelSize * kernelSize);
    
    return shadow;
}
