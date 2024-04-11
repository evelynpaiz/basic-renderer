#pragma once

#include "Core/Library.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"

namespace utils { namespace Texturing {

/**
 * Set a texture map in the shader program.
 * 
 * @param shader The shader program to set the properties for.
 * @param texture The texture map.
 * @param name The uniform name.
 * @param slot The texture slot.
 */
inline void SetTextureMap(const std::shared_ptr<Shader>& shader, const std::string& name,
                          const std::shared_ptr<Texture>& texture, unsigned int slot)
{
    if(!texture)
        return;

    texture->BindToTextureUnit(slot);
    shader->SetInt(name, slot);
}

} // namespace Texturing
} // namespace utils

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
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a material with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    Material(const std::filesystem::path& filePath)
    {
        // Define the shader for the material
        std::string name = filePath.stem();
        auto shader = s_ShaderLibrary->Exists(name) ?
            s_ShaderLibrary->Get(name) : s_ShaderLibrary->Load(name, filePath);
        m_Shader = shader;
    }
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
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Return the shader associated with the material.
    /// @return shader program.
    std::shared_ptr<Shader> GetShader() { return m_Shader; }
    /// @brief Defines if the viewing direction should be defined in the shader.
    /// @return `true` if the view direction should be defined.
    bool IsViewDirectionDefined() const { return m_ViewDirection; }
    /// @brief Defines if the normal matrix should be defined in the shader.
    /// @return `true` if the normal matrix should be defined.
    bool IsNormalMatrixDefined() const { return m_NormalMatrix; }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Defines if the viewing direction should be defined in the shader.
    /// @param v The view direction is defined or not in the shader.
    void SetViewDirection(bool v) { m_ViewDirection = v; }
    /// @brief Defines if the normal matrix should be defined in the shader.
    /// @param n The normal matrix is defined or not in the shader.
    void SetNormalMatrix(bool n) { m_NormalMatrix = n; }
    
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties.
    virtual void SetMaterialProperties()
    {
        m_Slot = 0;
    }
    
    // Material variables
    // ----------------------------------------
protected:
    ///< The shader used for shading the specific material.
    std::shared_ptr<Shader> m_Shader;
    
    ///< Texture unit index.
    unsigned int m_Slot = 0;
    ///< Normal matrix should be defined in the shader.
    bool m_NormalMatrix = false;
    ///< View direction should be defined in the shader.
    bool m_ViewDirection = false;
    
    ///< Library containing all shader that have been loaded.
    static inline std::unique_ptr<ShaderLibrary> s_ShaderLibrary = std::make_unique<ShaderLibrary>();
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Material(const Material&) = delete;
    Material(Material&&) = delete;

    Material& operator=(const Material&) = delete;
    Material& operator=(Material&&) = delete;
};

/**
 * A library for managing materials used in rendering.
 *
 * The `MaterialLibrary` class provides functionality to add, load, retrieve, and check
 * for the existence of materials within the library. Each material is associated with
 * a unique name.
 */
class MaterialLibrary : public Library<std::shared_ptr<Material>>
{
public:
    /// @brief Loads a material and adds it to the library.
    /// @tparam Type The type of object to load.
    /// @tparam Args The types of arguments to forward to the object constructor.
    /// @param name The name to associate with the loaded object.
    /// @param args The arguments to forward to the object constructor.
    /// @return The material created.
    template<typename Type, typename... Args>
    std::shared_ptr<Type> Create(const std::string& name, Args&&... args)
    {
        auto material = std::make_shared<Type>(std::forward<Args>(args)...);
        CORE_ASSERT(std::dynamic_pointer_cast<Material>(material),
                    "Object '{0}' is not of the specified type!", name);
        Add(name, material);
        return material;
    }
};
