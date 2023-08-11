/**
 * Represents a light source in the scene.
 */
struct Light {
    vec3 Position;   ///< Position of the light source in world space.
    
    vec3 Color;      ///< Color/intensity of the light.
    
    float La;        ///< Ambient light intensity.
    float Ld;        ///< Diffuse light intensity.
    float Ls;        ///< Specular light intensity.
    
    sampler2D ShadowMap;  ///< Shadow map texture for shadow calculations.
};
