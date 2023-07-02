#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

/**
 * Base class representing a material used for rendering.
 *
 * The `Material` class provides a base interface for defining materials used in rendering.
 * It encapsulates functionality for binding and unbinding the material, as well as setting
 * material-specific properties. Derived classes are responsible for implementing the
 * `SetMaterialProperties()` method to define the material's specific properties.
 *
 * Copying or moving `Material` objects is disabled to ensure single ownership and prevent
 * unintended duplication of material resources.
 */
class Material
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Destructor for the material.
    virtual ~Material() = default;
    
    // Usage
    // ----------------------------------------
    /// @brief Bind the material's associated shader and sets material properties.
    virtual void Bind()
    {
        m_Shader->Bind();
        SetMaterialProperties();
    }
    /// @brief Unbinds the material's associated shader.
    virtual void Unbind() { m_Shader -> Unbind(); }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the material properties.
    virtual void SetMaterialProperties() = 0;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Return the shader associated with the material.
    std::shared_ptr<Shader>& GetShader() { return m_Shader; }
    
protected:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a material with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    Material(const std::filesystem::path& filePath)
        : m_Shader(std::make_shared<Shader>(filePath))
    {}
    
    // Material variables
    // ----------------------------------------
protected:
    ///< The shader used for shading the specific material.
    std::shared_ptr<Shader> m_Shader;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Material(const Material&) = delete;
    Material(Material&&) = delete;

    Material& operator=(const Material&) = delete;
    Material& operator=(Material&&) = delete;
};

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
