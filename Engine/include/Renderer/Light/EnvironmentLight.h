#pragma once

#include "Renderer/Texture/Texture3D.h"

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
class EnvironmentLight
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    EnvironmentLight(const unsigned int width, const unsigned int height);
    
    /// @brief Destructor for the environment light.
    ~EnvironmentLight() = default;
    
    // Setter(s)
    // ----------------------------------------
    void SetEnvironmentMap(const std::shared_ptr<Texture>& texture);
    
    void SetLightSource(const std::shared_ptr<Light>& light) { m_Light = light; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light 3D model representing the environment.
    /// @return The 3D model.
    Model<GeoVertexData<glm::vec4>>& GetModel() { return m_Model; }
    /// @brief Get the environment map.
    /// @return The texture describing the environment.
    const std::shared_ptr<Texture>& GetEnvironmentMap() { return m_EnvironmentMap; }
    
    /// @brief Get the light source.
    /// @return The light source.
    std::shared_ptr<Light>& GetLightSource() { return m_Light; }
    
    // Properties
    // ----------------------------------------
    void DefineIrradianceMap(const std::shared_ptr<Shader> &shader,
                             const unsigned int slot);
    void DefinePreFilterMap(const std::shared_ptr<Shader> &shader,
                            const unsigned int slot);
    
private:
    // Initialization
    // ----------------------------------------
    void InitEnvironmentFramebuffers(const unsigned int cubeSize);
    void InitEnvironmentMaterials();
    
    // Update
    // ----------------------------------------
    void UpdateEnvironment();
    void UpdateLight();
    
    // Render
    // ----------------------------------------
    void RenderCubeMap(const std::array<glm::mat4, 6> &views, const glm::mat4 &projection,
                       const std::shared_ptr<SimpleTextureMaterial> &material,
                       const std::shared_ptr<FrameBuffer> &framebuffer,
                       const unsigned int& viewportWidth = 0, const unsigned int& viewportHeight = 0,
                       const unsigned int &level = 0, const bool& genMipMaps = true);
    
    // Environment variables
    // ----------------------------------------
private:
    ///< The environment map.
    std::shared_ptr<Texture> m_EnvironmentMap;
    ///< The lights in the environment.
    std::shared_ptr<Light> m_Light;
    
    ///< 3D model representing the surrounding environment in the scene.
    Model<GeoVertexData<glm::vec4>> m_Model;
    
    ///< Framebuffer(s) for pre-processing.
    std::unordered_map<std::string, std::shared_ptr<FrameBuffer>> m_Framebuffers;
    ///< Material(s) for pre-processing.
    std::unordered_map<std::string, std::shared_ptr<SimpleTextureMaterial>> m_Materials;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    EnvironmentLight(const EnvironmentLight&) = delete;
    EnvironmentLight(EnvironmentLight&&) = delete;

    EnvironmentLight& operator=(const EnvironmentLight&) = delete;
    EnvironmentLight& operator=(EnvironmentLight&&) = delete;
};
