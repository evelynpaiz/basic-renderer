#pragma once

#include "Common/Core/Library.h"

#include <glm/glm.hpp>

/**
 * Represents a shader program executed on the GPU.
 *
 * The `Shader` class provides functionality to load, compile, and use shader programs in
 * the graphics pipeline. Shaders can be loaded from file paths and bound for use in rendering
 * operations. The class also supports setting various types of uniform values in the shaders.
 *
 * Copying or moving `Shader` objects is disabled to ensure single ownership and prevent
 * unintended shader duplication.
 */
class Shader
{
public:
    // Constructor(s)
    // ----------------------------------------
    static std::shared_ptr<Shader> Create(const std::string& name, const std::filesystem::path& filePath);
    static std::shared_ptr<Shader> Create(const std::filesystem::path& filePath);
    // Destructor
    // ----------------------------------------
    /// @brief Delete the shader.
    virtual ~Shader() = default;
    
    // Usage
    // ----------------------------------------
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the name that identifies the shader.
    /// @return The shader's name.
    const std::string& GetName() const { return m_Name; }
    
    // Setter(s)
    // ----------------------------------------
    virtual void SetBool(const std::string &name, bool value) = 0;
    virtual void SetInt(const std::string &name, int value) = 0;
    virtual void SetFloat(const std::string &name, float value) = 0;
    
    virtual void SetVec2(const std::string& name, const glm::vec2& value) = 0;
    virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
    virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
    
    virtual void SetMat2(const std::string& name, const glm::mat2& value) = 0;
    virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
    
    // Parsing
    // ----------------------------------------
    std::string ReadFile(const std::filesystem::path& filePath);
    
protected:
    // Base constructor
    // ----------------------------------------
    /// @brief Define a general shader.
    /// @param name The name for the shader.
    /// @param filePath Path to the source file.
    Shader(const std::string& name, const std::filesystem::path& filePath)
        : m_Name(name), m_FilePath(filePath)
    {}
    
    // Shader variables
    // ----------------------------------------
protected:
    ///< Name of the shader.
    std::string m_Name;
    ///< File path of shader source program.
    std::filesystem::path m_FilePath;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;

    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) = delete;
};

/**
 * Represents a library of shader programs.
 *
 * The `ShaderLibrary` class manages a collection of shader programs. It provides
 * functionality to add, load, retrieve, and check for the existence of shaders within
 * the library.
 *
 * Shaders can be added to the library individually using the `Add` method or loaded
 * from file paths using the `Load` methods. Shaders in the library are associated with
 * unique names.
 *
 * Once added or loaded, shaders can be retrieved from the library using their names
 * with the `Get` method. The existence of a shader with a given name can be checked
 * using the `Exists` method.
 */
class ShaderLibrary : public Library<std::shared_ptr<Shader>>
{
public:
    // Constructor
    // ----------------------------------------
    /// @brief Create a new shader library.
    ShaderLibrary() : Library("Shader") {}
    
    // Add/Load
    // ----------------------------------------
    std::shared_ptr<Shader> Load(const std::filesystem::path& filePath);
    std::shared_ptr<Shader> Load(const std::string& name,
                                 const std::filesystem::path& filePath);
};
