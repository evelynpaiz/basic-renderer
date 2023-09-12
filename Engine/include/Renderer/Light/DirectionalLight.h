#pragma once

#include "Renderer/Light/Light.h"

#include <glm/glm.hpp>

/**
 * Represents a directional light source in 3D rendering.
 *
 * The `DirectionalLight` class extends the `Light` base class to define a directional light source.
 * It provides methods to set and retrieve the light's direction, distance, and additional properties
 * such as the shadow camera.
 *
 * Copying or moving `DirectionalLight` objects is disabled to ensure single ownership and prevent
 * unintended duplication of light resources.
 */
class DirectionalLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a light source defined by a direction.
    /// @param width The width that the light source covers.
    /// @param height The height that the light source covers.
    /// @param color The color of the light source.
    /// @param direction The direction of the light source.
    /// @param distance The distance from the target position to the light source.
    /// @param orthoSize The orthographic size for shadow calculations.
    DirectionalLight(const unsigned int width, const unsigned int height,
                     const glm::vec3& color = glm::vec3(1.0f),
                     const glm::vec3& direction = glm::vec3(0.0f, -1.0f, 0.0f),
                     float distance = 15.0f, float orthoSize = 20.0f)
        : Light(color), m_Direction(direction), m_Distance(distance)
    {
        // Set the shadow camera parameters
        auto shadowCamera = std::make_shared<OrthographicShadow>();
        shadowCamera->SetOrthographicSize(orthoSize);
        m_ShadowCamera = shadowCamera;
        
        UpdateShadowCamera();
    }
    /// @brief Destructor for the directional light.
    ~DirectionalLight() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the light direction.
    /// @param direction The light direction.
    void SetDirection(const glm::vec3& direction)
    {
        m_Direction = direction;
        UpdateShadowCamera();
    }
    /// @brief Change the distance of the light.
    /// @param distance The light distance.
    void SetDistance(const float distance)
    {
        m_Distance = distance;
        UpdateShadowCamera();
    }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light direction.
    /// @return The light direction vector.
    glm::vec3 GetDirection() const { return m_Direction; }
    /// @brief Get the distance of the light source.
    /// @return The light distance.
    float GetDistance() const { return m_Distance; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader) override
    {
        // Define basic light properties
        Light::DefineLightProperties(shader);
        // Define the point of light properties
        shader->SetVec4("u_Light.Vector", glm::vec4(m_Direction, 0.0f));
    }
    
private:
    // Update(s)
    // ----------------------------------------
    /// @brief Update the shadow camera based on the properties of the light source.
    void UpdateShadowCamera()
    {
        m_ShadowCamera->SetPosition(m_ShadowCamera->GetTarget() - (glm::normalize(m_Direction) * m_Distance));
    }
    
    // Light variables
    // ----------------------------------------
private:
    ///< The direction of the light.
    glm::vec3 m_Direction;
    ///< The distance from the (shadow camera) target to the light source.
    float m_Distance;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    DirectionalLight(const DirectionalLight&) = delete;
    DirectionalLight(DirectionalLight&&) = delete;

    DirectionalLight& operator=(const DirectionalLight&) = delete;
    DirectionalLight& operator=(DirectionalLight&&) = delete;
};
