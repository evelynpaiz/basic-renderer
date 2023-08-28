#pragma once

#include "Renderer/Material/Material.h"
#include "Renderer/Light/Light.h"
#include "Renderer/Buffer/FrameBuffer.h"

/**
 * A base class for materials that are affected by lighting.
 *
 * The `LightedMaterial` class extends the base `Material` class to provide additional
 * functionality for handling lighting and shadow properties. It allows setting a light
 * source and a framebuffer for shadow mapping, as well as defining shadow properties
 * in the shader program. Derived classes must implement the `SetMaterialProperties()`
 * method to specify the material's specific properties.
 *
 * Copying or moving `LightedMaterial` objects is disabled to ensure single ownership and
 * prevent unintended duplication of material resources.
 */
class LightedMaterial : public Material
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    /// @brief Generate a (lighted) material with the specified shader file path.
    /// @param light The light source to be used for shading.
    /// @param filePath The file path to the shader used by the material.
    LightedMaterial(const std::shared_ptr<Light>& light,
                    const std::filesystem::path& filePath)
        : Material(filePath), m_Light(light)
    {}
    /// @brief Destructor for the (lighted) material.
    virtual ~LightedMaterial() = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the light source used for shading.
    /// @param texture The light source.
    void SetLight(const std::shared_ptr<Light>& light) { m_Light = light; }
    
    /// @brief Set the shadow map.
    /// @param texture The texture representing the shadow map.
    void SetShadowMap(const std::shared_ptr<Texture>& texture) { m_ShadowMap = texture; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light source used for shading.
    /// @return The light source.
    const std::shared_ptr<Light>& GetLight() { return m_Light; }
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Define the shadow properties (from the light) into the uniforms of the shader program.
    /// @param slot Next texture slot available.
    void DefineShadowProperties()
    {
        utils::Texturing::SetTextureMap(m_Shader, "u_Light.ShadowMap", m_ShadowMap, m_Slot++);
    }
    /// @brief Set the material properties.
    void SetMaterialProperties() override
    {
        Material::SetMaterialProperties();
        m_Light->DefineLightProperties(m_Shader);
        DefineShadowProperties();
    }
    
    // Lighted color variables
    // ----------------------------------------
protected:
    ///< Light source.
    std::shared_ptr<Light> m_Light;
    
    ///< The light map.
    std::shared_ptr<Texture> m_ShadowMap;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    LightedMaterial(const LightedMaterial&) = delete;
    LightedMaterial(LightedMaterial&&) = delete;

    LightedMaterial& operator=(const LightedMaterial&) = delete;
    LightedMaterial& operator=(LightedMaterial&&) = delete;
};
