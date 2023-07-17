#pragma once

#include "Engine.h"

/**
 * Derived class representing a basic material.
 *
 * The `BasicMaterial` class represents a simple material used for basic rendering.
 * It inherits from the `Material` base class and provides an implementation of the
 * `SetMaterialProperties()` method. The specific shader used by the material can be
 * optionally specified by providing a file path to the constructor.
 *
 * Copying or moving `BasicMaterial` objects is disabled to ensure single ownership and prevent
 * unintended duplication of material resources.
 */
class BasicMaterial : public Material
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a basic material object with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    BasicMaterial(const std::filesystem::path& filePath =
                  std::filesystem::path("resources/shaders/basic.glsl"))
        : Material(filePath)
    {}
    /// @brief Destructor for the basic material.
    ~BasicMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the albedo color of the material.
    /// @param color Albedo color in RGBA.
    void SetColor(const glm::vec4& color) { m_Color = color; }
    /// @brief Set the texture map for the geometry.
    /// @param texture Texture map.
    void SetTexture(const std::shared_ptr<Texture>& texture)
    {
        m_Texture = texture;
    }
    /// @brief Set the material properties.
    void SetMaterialProperties() override
    {
        m_Shader->SetVec4("u_Color", m_Color);
        if(m_Texture)
        {
            m_Texture->Bind(0);
            m_Shader->SetInt("u_Texture", 0);
        }
    }
    
    // Basic material variables
    // ----------------------------------------
private:
    ///< Material albedo color.
    glm::vec4 m_Color = glm::vec4(1.0f);
    ///< Material texture.
    std::shared_ptr<Texture> m_Texture;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    BasicMaterial(const BasicMaterial&) = delete;
    BasicMaterial(BasicMaterial&&) = delete;

    BasicMaterial& operator=(const BasicMaterial&) = delete;
    BasicMaterial& operator=(BasicMaterial&&) = delete;
};
