#pragma once

#include "Renderer/Texture/TextureCube.h"

#include "Renderer/Light/Light.h"

#include "Renderer/Material/SimpleMaterial.h"

#include "Renderer/Mesh/MeshUtils.h"
#include "Renderer/Model/ModelUtils.h"

#include <glm/glm.hpp>

/**
 * Represents an environment light source in 3D rendering.
 *
 * The `EnvironmentLight` class extends the `Light` base class to define an environment light source.
 * It provides methods to set and retrieve the light's position, environment map, and additional properties
 * such as the shadow camera and 3D model representation.
 *
 * Copying or moving `EnvironmentLight` objects is disabled to ensure single ownership and prevent
 * unintended duplication of light resources.
 */
class EnvironmentLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    EnvironmentLight(const unsigned int width, const unsigned int height,
                     const glm::vec3 &color = glm::vec3(1.0f),
                     const glm::vec3 &position = glm::vec3(0.0f));
    
    /// @brief Destructor for the environment light.
    ~EnvironmentLight() override = default;
    
    // Setter(s)
    // ----------------------------------------
    void SetEnvironmentMap(const std::shared_ptr<Texture>& texture);
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light 3D model representing a positional light.
    /// @return The light 3D model.
    Model<GeoVertexData<glm::vec4>>& GetModel() {return m_Model; }
    
    // Properties
    // ----------------------------------------
    void DefineIrradianceMap(const std::shared_ptr<Shader> &shader,
                             const unsigned int slot);
    void DefinePreFilterMap(const std::shared_ptr<Shader> &shader,
                            const unsigned int slot);
    
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
    
protected:
    // Initialization
    // ----------------------------------------
    void InitEnvironmentFramebuffers(const unsigned int cubeSize);
    void InitEnvironmentMaterials();
    
    // Render
    // ----------------------------------------
    void RenderCubeMap(const std::array<glm::mat4, 6> &views, const glm::mat4 &projection,
                       const std::shared_ptr<SimpleTextureMaterial> &material,
                       const std::shared_ptr<FrameBuffer> &framebuffer,
                       const unsigned int& viewportWidth = 0, const unsigned int& viewportHeight = 0,
                       const unsigned int &level = 0, const bool& genMipMaps = true);
    
    // Light variables
    // ----------------------------------------
private:
    ///< The position of the environment light.
    glm::vec3 m_Position;
    
    ///< Environment light's 3D model.
    Model<GeoVertexData<glm::vec4>> m_Model;
    
    ///< Environment light's framebuffer(s).
    std::unordered_map<std::string, std::shared_ptr<FrameBuffer>> m_EnvFramebuffers;
    
    ///< Environment light's material(s).
    std::unordered_map<std::string, std::shared_ptr<SimpleTextureMaterial>> m_EnvMaterials;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    EnvironmentLight(const EnvironmentLight&) = delete;
    EnvironmentLight(EnvironmentLight&&) = delete;

    EnvironmentLight& operator=(const EnvironmentLight&) = delete;
    EnvironmentLight& operator=(EnvironmentLight&&) = delete;
};
