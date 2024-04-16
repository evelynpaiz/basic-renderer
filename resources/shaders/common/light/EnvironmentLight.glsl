/**
 * Represents a environment light in the scene.
 */
struct Environment
{
    float La;                       ///< Ambient light intensity.
    
    samplerCube IrradianceMap;      ///< Irradiance map for (diffuse) indirect lighting.
    
    // TODO: to be added.
    //samplerCube PreFilterMap;     ///< Pre-filter map for (specular) indirect lighting.
};
