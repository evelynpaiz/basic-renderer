#pragma once

#include "Renderer/Light/Light.h"

#include "Renderer/Material/SimpleMaterial.h"

#include "Renderer/Mesh/MeshUtils.h"
#include "Renderer/Model/ModelUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Represents a point light source in 3D space.
 *
 * The `PointLight` class is a type of `Light` that represents a point light source with color,
 * position, and associated properties. It also includes a 3D model to visualize the point of light.
 * Derived from `Light`, it provides methods to set and retrieve position and interact with shaders.
 *
 * Copying or moving `PointLight` objects is disabled to ensure single ownership
 * and prevent unintended duplication of light resources.
 */
class PointLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a point of light.
    /// @param color The color of the light source.
    /// @param position The position of the light source.
    /// @param orthoSize The orthographic size for shadow calculations (for directional shadows).
    PointLight(const glm::vec3 &color = glm::vec3(1.0f),
               const glm::vec3 &position = glm::vec3(0.0f),
               const float& orthoSize = 10.0f)
        : Light(color), m_Position(position)
    {
        // Set the viewpoint
        m_ShadowCamera = std::make_shared<OrthographicShadow>();
        m_ShadowCamera->SetPosition(position);
        
        // Check if m_ShadowCamera is actually of type OrthographicShadow before casting
        OrthographicShadow* orthoShadowCamera = dynamic_cast<OrthographicShadow*>(m_ShadowCamera.get());
        if (orthoShadowCamera) {
            orthoShadowCamera->SetOrthographicSize(orthoSize);
        }
        
        // Set the light 3D model
        std::shared_ptr<SimpleColorMaterial> material = std::make_shared<SimpleColorMaterial>();
        material->SetColor(glm::vec4(color, 1.0f));
        
        m_Model = utils::Geometry::ModelCube<GeoVertexData<glm::vec4>>(material);
        m_Model.SetPosition(position);
    }
    /// @brief Destructor for the point of light.
    ~PointLight() override = default;
    
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
    
    /// @brief Get the light 3D model representing a point of light.
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
        // Define the point of light properties
        shader->SetVec3("u_Light.Position", m_Position);
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
    PointLight(const PointLight&) = delete;
    PointLight(PointLight&&) = delete;

    PointLight& operator=(const PointLight&) = delete;
    PointLight& operator=(PointLight&&) = delete;
};
