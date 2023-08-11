#pragma once

#include <glm/glm.hpp>

/**
 * Represents the source code for a shader program.
 */
struct ShaderProgramSource
{
    // Shader program source variables
    // ----------------------------------------
    ///< Vertex shader source code
    std::string VertexSource;
    ///< Fragment shader source code
    std::string FragmentSource;
    
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Define the shader program source.
    /// @param vs Vertex shader source.
    /// @param fs Fragment shader source.
    ShaderProgramSource(const std::string& vs, const std::string& fs)
        : VertexSource(vs), FragmentSource(fs)
    {}
    /// @brief Delete the shader program source.
    ~ShaderProgramSource() = default;
};

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
    // Constructor(s)/Destructor
    // ----------------------------------------
    Shader(const std::filesystem::path& filePath);
    ~Shader();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Getter(s)
    // ----------------------------------------
    int GetUniformLocation(const std::string& name);
    
    // Setter(s)
    // ----------------------------------------
    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    
    void SetMat2(const std::string& name, const glm::mat2& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    
private:
    // Compilation
    // ----------------------------------------
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader);
    // Parsing
    // ----------------------------------------
    ShaderProgramSource ParseShader(const std::filesystem::path& filepath);
    std::string ReadFile(const std::filesystem::path& filePath);
    
    // Shader variables
    // ----------------------------------------
private:
    ///< File path of shader source program.
    std::filesystem::path m_FilePath;
    ///< ID of the shader program.
    unsigned int m_ID = 0;
    ///< Cache of uniform locations.
    std::unordered_map<std::string, int> m_UniformLocationCache;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;

    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) = delete;
};
