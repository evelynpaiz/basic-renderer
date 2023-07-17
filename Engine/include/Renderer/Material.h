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
