#pragma once

#include "Renderer/Light/Light.h"

/**
 * A base class for materials that are affected by lighting.
 */
class SimpleLighted
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Destructor for the phong base.
    virtual ~SimpleLighted() = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the light source used for shading.
    /// @param texture The light source.
    void SetLight(const std::shared_ptr<Light>& light) { m_Light = light; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light source used for shading.
    /// @return The light source.
    std::shared_ptr<Light> GetLight() const { return m_Light; }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a phong base.
    SimpleLighted() = default;
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties into the uniforms of the shader program.
    /// @param shader The shader program to set the properties for.
    void SetProperties(const std::shared_ptr<Shader>& shader,
                       unsigned int slot = 0)
    {
        // Set the light properties
        m_Light->DefineLightProperties(shader, slot);
    }
    
    // Lighted color variables
    // ----------------------------------------
protected:
    ///< Light source.
    std::shared_ptr<Light> m_Light;
};
