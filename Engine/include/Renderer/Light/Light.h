#pragma once

#include "Renderer/Shader/Shader.h"
#include "Renderer/Buffer/FrameBuffer.h"

#include "Renderer/Light/ShadowCamera.h"

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
    
    /// @brief Get the ambient strength of the light source.
    /// @return The ambient strength of the light source.
    float GetAmbientStrength() const { return m_AmbientStrength; }
    /// @brief Get the diffuse strength of the light source.
    /// @return The diffuse strength of the light source.
    float GetDiffuseStrength() const { return m_DiffuseStrength; }
    /// @brief Get the specular strength of the light source.
    /// @return The specular strength of the light source.
    float GetSpecularStrength() const { return m_SpecularStrength; }
    
    /// @brief Get the camera used for shadow mapping to generate depth maps for shadow calculations.
    /// @return The viewpoint of the light source.
    const std::shared_ptr<Camera>& GetShadowCamera() { return m_ShadowCamera; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define the general properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineGeneralProperties(const std::shared_ptr<Shader> &shader)
    {
        shader->SetVec3("u_Light.Color", m_Color);
        shader->SetVec4("u_Light.Vector", m_Vector);
    }
    /// @brief Define the strength properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineStrenghtProperties(const std::shared_ptr<Shader> &shader)
    {
        shader->SetFloat("u_Light.La", m_AmbientStrength);
        shader->SetFloat("u_Light.Ld", m_DiffuseStrength);
        shader->SetFloat("u_Light.Ls", m_SpecularStrength);
    }
    /// @brief Define the transformation properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineTranformProperties(const std::shared_ptr<Shader> &shader)
    {
        const static glm::mat4 textureMatrix = glm::mat4(
            0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f
        );
        
        shader->SetMat4("u_Transform.Light",
                        m_ShadowCamera->GetProjectionMatrix() *
                        m_ShadowCamera->GetViewMatrix());
        shader->SetMat4("u_Transform.Texture", textureMatrix);
    }
    
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader)
    {
        DefineGeneralProperties(shader);
        DefineStrenghtProperties(shader);
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a light source.
    /// @param color The color of the light source.
    Light(const glm::vec4 &vector,
          const glm::vec3 &color = glm::vec3(1.0f))
        : m_Vector(vector), m_Color(color)
    {};
    
protected:
    // Light variables
    // ----------------------------------------
    ///< The position of the light if .w is defined as 1.0f, or
    ///< the direction of the light if .w is defined as 0.0f.
    glm::vec4 m_Vector;
    
    ///< The light color.
    glm::vec3 m_Color;
    
    ///< The light intensities.
    float m_AmbientStrength = 0.2f;
    float m_DiffuseStrength = 0.6f;
    float m_SpecularStrength = 0.4f;
    
    ///< The light viewpoint (used for rendering shadows).
    std::shared_ptr<Camera> m_ShadowCamera;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Light(const Light&) = delete;
    Light(Light&&) = delete;

    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;
};
