#pragma once

#include "Common/Renderer/Shader/Shader.h"

/**
 * Concrete implementation of the Shader class for the Metal API.
 *
 * The `MetalShader` class specializes the `Shader` base class for Metal, handling the
 * compilation of Metal Shading Language (MSL) code, management of Metal functions,
 * and interaction with Metal buffers for uniform data.
 *
 * Copying or moving `MetalShader` objects is disabled to ensure single ownership and
 * prevent unintended shader duplication.
 */
class MetalShader : public Shader
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    MetalShader(const std::string& name, const std::filesystem::path& filePath);
    MetalShader(const std::filesystem::path& filePath);
    ~MetalShader() override;
    
    // Usage
    // ----------------------------------------
    void Bind() const override;
    void Unbind() const override;
    
    // Getter(s)
    // ----------------------------------------
    void* GetVertexFunction() const;
    void* GetFragmentFunction() const;
    
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
    // Compilation
    // ----------------------------------------
    void CompileShader(const std::filesystem::path& filePath);
    
    // Shader variables
    // ----------------------------------------
private:
    ///< Shader program source.
    struct MetalShaderSource;
    std::shared_ptr<MetalShaderSource> m_ShaderSource;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    MetalShader(const MetalShader&) = delete;
    MetalShader(MetalShader&&) = delete;

    MetalShader& operator=(const MetalShader&) = delete;
    MetalShader& operator=(MetalShader&&) = delete;
};
