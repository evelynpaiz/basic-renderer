#pragma once

#include "Common/Core/Library.h"
#include "Common/Renderer/Shader/Shader.h"
#include "Common/Renderer/Texture/Texture.h"

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
 * @brief Flags representing properties of a material.
 */
struct MaterialFlags
{
    ///< Boolean flag indicating whether view direction is used in the shader.
    bool ViewDirection = false;
    
    ///< Boolean flag indicating whether the normal matrix is used in the shader.
    bool NormalMatrix = false;
};

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
        std::string name = filePath.stem().string();
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
    virtual void Unbind() 
    {
        m_Shader -> Unbind();
#ifdef __APPLE__
        m_Slot = 0;
#else
        m_Slot = 1;
#endif
    }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Return the shader associated with the material.
    /// @return shader program.
    std::shared_ptr<Shader> GetShader() { return m_Shader; }
    
    /// @brief Returns the active flags for the material.
    /// @return Shading flags.
    MaterialFlags& GetMaterialFlags() { return m_Flags; }
    
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties.
    virtual void SetMaterialProperties()
    {}
    
    // Material variables
    // ----------------------------------------
protected:
    ///< The shader used for shading the specific material.
    std::shared_ptr<Shader> m_Shader;
    
    ///< Texture unit index.
    // TODO: fix the issue related to starting slot number.
#ifdef __APPLE__
    unsigned int m_Slot = 0;
#else
    unsigned int m_Slot = 1;
#endif
    ///< Flags for shading.
    MaterialFlags m_Flags;
    
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
    // Constructor
    // ----------------------------------------
    /// @brief Create a new material library.
    MaterialLibrary() : Library("Material") {}
    
    // Create
    // ----------------------------------------
    /// @brief Loads a material and adds it to the library.
    /// @tparam Type The type of material to create.
    /// @tparam Args The types of arguments to forward to the material constructor.
    /// @param name The name to associate with the loaded material.
    /// @param args The arguments to forward to the material constructor.
    /// @return The material created.
    template<typename Type, typename... Args>
    std::shared_ptr<Type> Create(const std::string& name, Args&&... args)
    {
        auto material = std::make_shared<Type>(std::forward<Args>(args)...);
        
        std::string message = GetName() + " " + name + " is not of the specified type!";
        CORE_ASSERT(std::dynamic_pointer_cast<Material>(material), message);
        
        Add(name, material);
        return material;
    }
};
