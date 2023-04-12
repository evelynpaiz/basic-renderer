#pragma once

#include <glm/glm.hpp>

/**
 * Shader program (executed on the GPU).
 */
struct ShaderProgramSource
{
    /// Vertex shader
    std::string VertexSource;
    /// Fragment shader
    std::string FragmentSource;
    
    /// Constructor(s)/ Destructor
    ShaderProgramSource(const std::string& vs, const std::string& fs);
    ~ShaderProgramSource() = default;
};

/**
 * A shader program (runned in the graphics pipeline).
 */
class Shader
{
public:
    /// Constructor(s)/ Destructor
    Shader(const std::filesystem::path& filePath);
    ~Shader();
    /// Usage
    void Bind() const;
    void Unbind() const;
    /// Gets
    int GetUniformLocation(const std::string& name);
    /// Sets
    void SetBool(const std::string &name, bool value);
    void SetInt(const std::string &name, int value);
    void SetFloat(const std::string &name, float value);
    
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    
    void SetMat2(const std::string& name, const glm::mat2& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetMat4(const std::string& name, const glm::mat4& value);
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Shader(const Shader&) = delete;
    Shader(Shader&&) = delete;
    /// Operators
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&&) = delete;
    
private:
    /// Compilation
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader);
    /// Parsing
    ShaderProgramSource ParseShader(const std::filesystem::path& filepath);
    
private:
    /// File path of shader source program
    std::filesystem::path m_FilePath;
    /// ID of the shader program
    unsigned int m_ID = 0;
    /// Cache of uniform locations
    std::unordered_map<std::string, int> m_UniformLocationCache;
};
