#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

/**
 * Representation of a shader program (vertex & fragment sources).
 */
struct ShaderProgramSource
{
    /// Vertex shader
    std::string vertexSource;
    /// Fragment shader
    std::string fragmentSource;
    
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
    Shader(const std::filesystem::path& filepath);
    ~Shader();
    /// Usage
    void Bind() const;
    void Unbind() const;
    /// Gets
    int GetUniformLocation(const std::string& name);
    /// Sets
    void SetVec4(const std::string& name, float x, float y, float z, float w);
    
private:
    /// Compilation
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader);
    ShaderProgramSource ParseShader(const std::filesystem::path& filepath);
    
private:
    /// File path of shader source program
    std::filesystem::path m_FilePath;
    /// ID of the shader program
    unsigned int m_ID;
    /// Cache of uniform locations
    std::unordered_map<std::string, int> m_UniformLocationCache;
};
