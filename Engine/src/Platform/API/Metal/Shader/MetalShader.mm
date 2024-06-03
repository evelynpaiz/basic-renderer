#include "enginepch.h"
#include "Platform/Metal/Shader/MetalShader.h"

#include "Platform/Metal/MetalContext.h"

#include <Metal/Metal.h>

/**
 * Internal representation of compiled Metal shader source.
 */
struct MetalShader::MetalShaderSource
{
    ///< Compiled Metal vertex function.
    id<MTLFunction> VertexFunction;
    ///< Compiled Metal fragment function.
    id<MTLFunction> FragmentFunction;
    
    ///< Uniform buffer.
    id<MTLBuffer> UniformBuffer;
};

/**
 * Generate a shader program.
 *
 * @param name The name for the shader.
 * @param filePath Path to the source file.
 */
MetalShader::MetalShader(const std::string& name, const std::filesystem::path& filePath)
    : Shader(name, filePath)
{
    // Initialize
    m_ShaderSource = std::make_shared<MetalShaderSource>();
    // Compile the source file and define the shader functions
    CompileShader(filePath);
}

/**
 * Generate a shader program.
 *
 * @param filePath Path to the source file.
 */
MetalShader::MetalShader(const std::filesystem::path& filePath)
    : MetalShader(filePath.stem(), filePath)
{}

/**
 * Delete the shader program.
 */
MetalShader::~MetalShader()
{}

/**
 * Activate the shader.
 */
void MetalShader::Bind() const
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Deactivate the shader.
 */
void MetalShader::Unbind() const
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Gets the compiled Metal vertex function.
 *
 * @return A pointer to the compiled Metal vertex function as a void pointer,
 * or nullptr if the function was not compiled or found.
 */
void* MetalShader::GetVertexFunction() const
{
    return reinterpret_cast<void*>(m_ShaderSource->VertexFunction);
}

/**
 * Gets the compiled Metal fragment function.
 *
 * @return A pointer to the compiled Metal vertex function as a void pointer,
 * or nullptr if the function was not compiled or found.
 */
void* MetalShader::GetFragmentFunction() const
{
    return reinterpret_cast<void*>(m_ShaderSource->FragmentFunction);
}

/**
 * Set the uniform with a bool value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void MetalShader::SetBool(const std::string& name, bool value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with an integer value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void MetalShader::SetInt(const std::string& name, int value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a float value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void MetalShader::SetFloat(const std::string& name, float value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a vector with 2 values (x, y).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec2(const std::string& name, const glm::vec2& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a vector with 3 values (x, y, z).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec3(const std::string& name, const glm::vec3& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a vector with 4 values (x, y, z, w).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec4(const std::string& name, const glm::vec4& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a matrix with 2x2 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat2(const std::string& name, const glm::mat2& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a matrix with 3x3 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat3(const std::string& name, const glm::mat3& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Set the uniform with a matrix with 4x4 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat4(const std::string& name, const glm::mat4& value)
{
    CORE_WARN("Shader::Method not yet defined!");
}

/**
 * Compiles the shader source code for Metal.
 *
 * @param filePath Path to the source file.
 */
void MetalShader::CompileShader(const std::filesystem::path& filePath)
{
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    // Get the Metal device from the context
    id<MTLDevice> device = reinterpret_cast<id<MTLDevice>>(context->GetDevice());
    
    // Load the shader source program
    std::string sourceFromFile = ReadFile(filePath);
    NSString* sourceCode = [NSString stringWithUTF8String:sourceFromFile.c_str()];
    
    // Compile the shader source code into a Metal library
    NSError* error = nil;
    id<MTLLibrary> library = [device newLibraryWithSource:sourceCode options:nil error:&error];
    CORE_ASSERT(!error, "Failed to compiled shader!");
    
    // Define the shader functions
    m_ShaderSource->VertexFunction = [library newFunctionWithName:@"vertex_main"];
    m_ShaderSource->FragmentFunction = [library newFunctionWithName:@"fragment_main"];
}
