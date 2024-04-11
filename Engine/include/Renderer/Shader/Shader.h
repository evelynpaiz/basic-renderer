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
    ///< Geometry shader source code
    std::string GeometrySource;
    
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Define the shader program source.
    /// @param vs Vertex shader source.
    /// @param fs Fragment shader source.
    ShaderProgramSource(const std::string& vs, const std::string& fs, 
        const std::string& gs = "")
        : VertexSource(vs), FragmentSource(fs), GeometrySource(gs)
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
    Shader(const std::string& name, const std::filesystem::path& filePath);
    Shader(const std::filesystem::path& filePath);
    ~Shader();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the name that identifies the shader.
    /// @return The shader's name.
    const std::string& GetName() const { return m_Name; }
    
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
                              const std::string& fragmentShader,
                              const std::string& gemetryShader = "");
    // Parsing
    // ----------------------------------------
    ShaderProgramSource ParseShader(const std::filesystem::path& filepath);
    std::string ReadFile(const std::filesystem::path& filePath);
    
    // Shader variables
    // ----------------------------------------
private:
    ///< Name of the shader.
    std::string m_Name;
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

/**
 * @brief Represents a library of shader programs.
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
class ShaderLibrary
{
public:
    // Constructor/Destructor
    // ----------------------------------------
    /// @brief Create a new shader library.
    ShaderLibrary() = default;
    /// @brief Delete the shader library.
    ~ShaderLibrary() = default;
    
    // Add/Load
    // ----------------------------------------
    void Add(const std::shared_ptr<Shader>& shader);
    std::shared_ptr<Shader> Load(const std::filesystem::path& filePath);
    std::shared_ptr<Shader> Load(const std::string& name,
                                 const std::filesystem::path& filePath);
    
    // Getter(s)
    // ----------------------------------------
    std::shared_ptr<Shader> Get(const std::string& name);
    bool Exists(const std::string& name) const;
    
    // Shader library
    // ----------------------------------------
private:
    ///< A map of shader names to their corresponding shader program.
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};
