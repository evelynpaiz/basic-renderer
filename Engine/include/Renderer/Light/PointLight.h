#pragma once

#include "Renderer/Light/Light.h"

class PointLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a point of light.
    /// @param color The color of the light source.
    PointLight(const glm::vec3 &color = glm::vec3(1.0f),
               const glm::vec3 &position = glm::vec3(0.0f))
        : Light(color), m_Position(position)
    {}
    /// @brief Destructor for the point of light.
    ~PointLight() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the light position (x, y, z).
    /// @param position The light center position.
    void SetPosition(const glm::vec3& position) { m_Position = position; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light position (x, y, z).
    /// @return The light position coordinates.
    const glm::vec3& GetPosition() const { return m_Position; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader) override
    {
        // Define basic light properties
        Light::DefineLightProperties(shader);
        // Define the point of light properties
        shader->SetVec3("u_Light.Position", m_Position);
    }
    
    // Light variables
    // ----------------------------------------
private:
    ///< The light color.
    glm::vec3 m_Position;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    PointLight(const PointLight&) = delete;
    PointLight(PointLight&&) = delete;

    PointLight& operator=(const PointLight&) = delete;
    PointLight& operator=(PointLight&&) = delete;
};
