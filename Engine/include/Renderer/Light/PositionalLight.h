#pragma once

#include "Renderer/Light/Light.h"

#include "Renderer/Material/SimpleMaterial.h"

#include "Renderer/Mesh/MeshUtils.h"
#include "Renderer/Model/ModelUtils.h"

#include <glm/glm.hpp>

/**
 * Represents a positional light source in 3D rendering.
 *
 * The `PositionalLight` class extends the `Light` base class to define a positional light source.
 * It provides methods to set and retrieve the light's position, as well as additional properties
 * such as the shadow camera and 3D model representation.
 *
 * Copying or moving `PositionalLight` objects is disabled to ensure single ownership and prevent
 * unintended duplication of light resources.
 */
class PositionalLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a light source with a position in the world space.
    /// @param color The color of the light source.
    /// @param position The position of the light source.
    /// @param angle The angle of visibility of the light source.
    PositionalLight(const glm::vec3 &color = glm::vec3(1.0f),
                    const glm::vec3 &position = glm::vec3(0.0f),
                    float angle = 90.0f)
        : Light(color), m_Position(position)
    {
        // Set the shadow camera parameters
        auto shadowCamera = std::make_shared<PerspectiveShadow>();
        shadowCamera->SetPosition(position);
        shadowCamera->SetFieldOfView(angle);
        m_ShadowCamera = shadowCamera;
        
        // Define the 3D model for the positional light
        std::shared_ptr<SimpleColorMaterial> material = std::make_shared<SimpleColorMaterial>();
        material->SetColor(glm::vec4(color, 1.0f));
        
        m_Model = utils::Geometry::ModelSphere<GeoVertexData<glm::vec4>>(material);
        m_Model.SetScale(glm::vec3(0.25f));
        m_Model.SetPosition(position);
    }
    
    /// @brief Destructor for the positional light.
    ~PositionalLight() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the light position (x, y, z).
    /// @param position The light center position.
    void SetPosition(const glm::vec3& position) {
        m_Position = position;
        m_ShadowCamera->SetPosition(position);
        m_Model.SetPosition(position);
    }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light position (x, y, z).
    /// @return The light position coordinates.
    glm::vec3 GetPosition() const { return m_Position; }
    
    /// @brief Get the light 3D model representing a positional light.
    /// @return The light 3D model.
    Model<GeoVertexData<glm::vec4>>& GetModel() {return m_Model; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader) override
    {
        // Define basic light properties
        Light::DefineLightProperties(shader);
        // Define the positional light properties
        // (set .w coordiante as 1 to identify it as a position vector)
        shader->SetVec4("u_Light.Vector", glm::vec4(m_Position, 1.0f));
    }
    
    // Light variables
    // ----------------------------------------
private:
    ///< The light color.
    glm::vec3 m_Position;
    
    ///< Light 3D model.
    Model<GeoVertexData<glm::vec4>> m_Model;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    PositionalLight(const PositionalLight&) = delete;
    PositionalLight(PositionalLight&&) = delete;

    PositionalLight& operator=(const PositionalLight&) = delete;
    PositionalLight& operator=(PositionalLight&&) = delete;
};