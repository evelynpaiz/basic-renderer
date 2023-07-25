#pragma once

#include "Renderer/Material/Material.h"

/**
 * A material class for simple color-based shading.
 *
 * The `SimpleColorMaterial` class is a subclass of `Material` and provides a basic
 * material definition for shading 3D models with a simple color. It uses a shader specified by the
 * given file path to apply the color to the model. The albedo color can be set using the
 * `SetColor` method, and the material properties are then applied to the shader program
 * using the `SetMaterialProperties` method.
 *
 * Copying or moving `SimpleColorMaterial` objects is disabled to ensure single ownership
 * and prevent unintended duplication of material resources.
 */
class SimpleColorMaterial : public Material
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a material for hair with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    SimpleColorMaterial(const std::filesystem::path& filePath =
                        std::filesystem::path("Resources/shaders/SimpleColor.glsl"))
        : Material(filePath)
    {}
    /// @brief Destructor for the hair shading material.
    ~SimpleColorMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the albedo color.
    /// @param color Albedo color in RGBA.
    virtual void SetColor(const glm::vec4& color) { m_Color = color; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the albedo color.
    /// @return The albedo color in RGBA.
    glm::vec4 GetColor() const { return m_Color; }
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties into the uniforms of the shader program.
    void SetMaterialProperties() override
    {
        m_Shader->SetVec4("u_Material.Color", m_Color);
    }
    
    // Basic material variables
    // ----------------------------------------
protected:
    ///< Material albedo color.
    glm::vec4 m_Color = glm::vec4(1.0f);
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    SimpleColorMaterial(const SimpleColorMaterial&) = delete;
    SimpleColorMaterial(SimpleColorMaterial&&) = delete;

    SimpleColorMaterial& operator=(const SimpleColorMaterial&) = delete;
    SimpleColorMaterial& operator=(SimpleColorMaterial&&) = delete;
};

/**
 * A material class for simple texture-based shading.
 *
 * The `SimpleTextureMaterial` class is a subclass of `Material` and provides a basic
 * material definition for shading 3D models with a simple texture map. It uses a shader specified by the
 * given file path to apply the texture to the model. The texture map can be set using the
 * `SetTexture` method, and the material properties are then applied to the shader program
 * using the `SetMaterialProperties` method.
 *
 * Copying or moving `SimpleTextureMaterial` objects is disabled to ensure single ownership
 * and prevent unintended duplication of material resources.
 */
class SimpleTextureMaterial : public Material
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a basic material object with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    SimpleTextureMaterial(const std::filesystem::path& filePath =
                  std::filesystem::path("Resources/shaders/SimpleTexture.glsl"))
        : Material(filePath)
    {}
    /// @brief Destructor for the basic material.
    ~SimpleTextureMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the texture map for the geometry.
    /// @param texture Texture map.
    void SetTexture(const std::shared_ptr<Texture>& texture)
    {
        m_Texture = texture;
    }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the texture map for the geometry.
    /// @return The texture map.
    std::shared_ptr<Texture> GetTexture() const { return m_Texture; }
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties into the uniforms of the shader program.
    void SetMaterialProperties() override
    {
        if(!m_Texture)
            return;
        
        m_Texture->Bind(0);
        m_Shader->SetInt("u_Texture", 0);
    }
    
    // Basic material variables
    // ----------------------------------------
private:
    ///< Material texture.
    std::shared_ptr<Texture> m_Texture;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    SimpleTextureMaterial(const SimpleTextureMaterial&) = delete;
    SimpleTextureMaterial(SimpleTextureMaterial&&) = delete;

    SimpleTextureMaterial& operator=(const SimpleTextureMaterial&) = delete;
    SimpleTextureMaterial& operator=(SimpleTextureMaterial&&) = delete;
};
