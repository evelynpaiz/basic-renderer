#pragma once

#include <glm/glm.hpp>

/**
 * Base class for light sources used in 3D rendering.
 *
 * The `Light` class serves as a base class for defining different types of light sources used in 3D
 * rendering. It provides common functionality for defining and retrieving the color of the light source.
 * Derived classes can override the `DefineLightProperties` method to set additional light
 * properties in the shader, such as position or direction.
 *
 * Copying or moving `Light` objects is disabled to ensure single ownership and prevent unintended
 * duplication of light resources.
 */
class Light
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Destructor for the light type.
    virtual ~Light() = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the color of the light source.
    /// @param color The color of the light source.
    void SetColor(const glm::vec3 &color) { m_Color = color; }
    
    /// @brief Set the strength of the ambient component of the light source.
    /// @param s The strength of the ambient component (a value between 0 and 1).
    void SetAmbientStrength(float s) { m_AmbientStrength = s; }
    /// @brief Set the strength of the diffuse component of the light source.
    /// @param s The strength of the diffuse component (a value between 0 and 1).
    void SetDiffuseStrength(float s) { m_DiffuseStrength = s; }
    /// @brief Set the strength of the specular component of the light source.
    /// @param s The strength of the specular component (a value between 0 and 1).
    void SetSpecularStrength(float s) { m_SpecularStrength = s; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the color of the light source.
    /// @return The color of the light source.
    glm::vec3 GetColor() const { return m_Color; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    virtual void DefineLightProperties(const std::shared_ptr<Shader> &shader)
    {
        shader->SetVec3("u_Light.Color", m_Color);
        
        shader->SetFloat("u_Light.La", m_AmbientStrength);
        shader->SetFloat("u_Light.Ld", m_DiffuseStrength);
        shader->SetFloat("u_Light.Ls", m_SpecularStrength);
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a light source.
    /// @param color The color of the light source.
    Light(const glm::vec3 &color = glm::vec3(1.0f))
    : m_Color(color)
    {}
    
    // Light variables
    // ----------------------------------------
protected:
    ///< The light color.
    glm::vec3 m_Color;
    
    ///< The intensity for the ambient component.
    float m_AmbientStrength = 0.4f;
    float m_DiffuseStrength = 0.6f;
    float m_SpecularStrength = 1.0f;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Light(const Light&) = delete;
    Light(Light&&) = delete;

    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;
};
