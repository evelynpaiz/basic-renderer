#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

/**
 * Shader program (executed on the GPU).
 */
struct ShaderProgramSource
{
    /// Vertex shader
    std::string VertexSource;
    /// Fragment shader
    std::string FragmentSource;
    
    /// Constructor
    ShaderProgramSource(const std::string& vs, const std::string& fs);
};

/**
 * A shader program (runned in the graphics pipeline).
 */
class Shader
{
public:
    /// Constructor/Destructor
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
    void SetFloat2(const std::string& name, float x, float y);
    void SetFloat3(const std::string& name, float x, float y, float z);
    void SetFloat4(const std::string& name, float x, float y, float z, float w);
    
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
