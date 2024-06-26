#pragma once

#include "Common/Renderer/Shader/Shader.h"

/**
 * Concrete implementation of the `Shader` class for the OpenGL API.
 *
 * The `OpenGLShader` class extends the base `Shader` class to provide OpenGL-specific
 * functionality for compiling, linking, binding, and setting uniform values in OpenGL shader programs.
 *
 * Copying or moving `OpenGLShader` objects is disabled to ensure single ownership and prevent
 * unintended shader duplication.
 */
class OpenGLShader : public Shader
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    OpenGLShader(const std::string& name, const std::filesystem::path& filePath);
    OpenGLShader(const std::filesystem::path& filePath);
    ~OpenGLShader() override;
    
    // Usage
    // ----------------------------------------
    void Bind() const override;
    void Unbind() const override;
    
    // Getter(s)
    // ----------------------------------------
    int GetUniformLocation(const std::string& name);
    
    // Setter(s)
    // ----------------------------------------
    void SetBool(const std::string &name, bool value) override;
    void SetInt(const std::string &name, int value) override;
    void SetFloat(const std::string &name, float value) override;
    
    void SetVec2(const std::string& name, const glm::vec2& value) override;
    void SetVec3(const std::string& name, const glm::vec3& value) override;
    void SetVec4(const std::string& name, const glm::vec4& value) override;
    
    void SetMat2(const std::string& name, const glm::mat2& value) override;
    void SetMat3(const std::string& name, const glm::mat3& value) override;
    void SetMat4(const std::string& name, const glm::mat4& value) override;
    
private:
    /**
     * Represents the source code for an OpenGL shader program.
     */
    struct OpenGLShaderSource
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
        OpenGLShaderSource(const std::string& vs, const std::string& fs,
            const std::string& gs = "")
            : VertexSource(vs), FragmentSource(fs), GeometrySource(gs)
        {}
        /// @brief Delete the shader program source.
        ~OpenGLShaderSource() = default;
    };
    
private:
    // Compilation
    // ----------------------------------------
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader,
                              const std::string& gemetryShader = "");
    // Parsing
    // ----------------------------------------
    OpenGLShaderSource ParseShader(const std::filesystem::path& filepath);
    
    // Shader variables
    // ----------------------------------------
private:
    ///< ID of the shader program.
    unsigned int m_ID = 0;
    ///< Cache of uniform locations.
    std::unordered_map<std::string, int> m_UniformBuffer;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    OpenGLShader(const OpenGLShader&) = delete;
    OpenGLShader(OpenGLShader&&) = delete;

    OpenGLShader& operator=(const OpenGLShader&) = delete;
    OpenGLShader& operator=(OpenGLShader&&) = delete;
};
