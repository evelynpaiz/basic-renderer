#include "enginepch.h"
#include "Platform/Metal/Shader/MetalShader.h"

#include "Platform/Metal/MetalContext.h"
#include "Platform/Metal/MetalRendererUtils.h"

#include <Metal/Metal.h>

/**
 * Internal representation of compiled Metal shader source.
 */
struct MetalShader::MetalShaderSource
{
    ///< Shading library
    id<MTLLibrary> Library;
    
    ///< Compiled Metal vertex function.
    id<MTLFunction> VertexFunction;
    ///< Compiled Metal fragment function.
    id<MTLFunction> FragmentFunction;
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
    : MetalShader(filePath.stem().string(), filePath)
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
{}

/**
 * Deactivate the shader.
 */
void MetalShader::Unbind() const
{}

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
    SetUniformData(name, value);
}

/**
 * Set the uniform with an integer value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void MetalShader::SetInt(const std::string& name, int value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a float value.
 *
 * @param name Uniform name.
 * @param value Uniform value.
 */
void MetalShader::SetFloat(const std::string& name, float value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a vector with 2 values (x, y).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec2(const std::string& name, const glm::vec2& value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a vector with 3 values (x, y, z).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec3(const std::string& name, const glm::vec3& value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a vector with 4 values (x, y, z, w).
 *
 * @param name Uniform name.
 * @param value Vector input value.
 */
void MetalShader::SetVec4(const std::string& name, const glm::vec4& value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a matrix with 2x2 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat2(const std::string& name, const glm::mat2& value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a matrix with 3x3 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat3(const std::string& name, const glm::mat3& value)
{
    SetUniformData(name, value);
}

/**
 * Set the uniform with a matrix with 4x4 values.
 *
 * @param name Uniform name.
 * @param value Matrix input value.
 */
void MetalShader::SetMat4(const std::string& name, const glm::mat4& value)
{
    SetUniformData(name, value);
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
    m_ShaderSource->Library = [device newLibraryWithSource:sourceCode options:nil error:&error];
    CORE_ASSERT(!error, "Failed to compiled shader!");
    
    // Define the shader functions
    m_ShaderSource->VertexFunction = [m_ShaderSource->Library newFunctionWithName:@"vertex_main"];
    m_ShaderSource->FragmentFunction = [m_ShaderSource->Library newFunctionWithName:@"fragment_main"];
}

/**
 * Processes a single shader argument (uniform) from Metal reflection data.
 *
 * @param arg  A `void*` pointer to the `MTLArgument` object.
 * @param type The shader type associated with the argument.
 */
void MetalShader::ProcessShaderArgument(void* arg, ShaderType type)
{
    // Get the Metal argument definition
    // TODO: use MTLBinding instead
    MTLArgument* argument = reinterpret_cast<MTLArgument*>(arg);
    
    // Ignore inactive arguments
    if (!argument.active)
        return;
    
    // Get the uniform group name (assuming the "u_" prefix convention)
    const char* group = [argument.name UTF8String];
    if (strncmp(group, "u_", 2) != 0)
        return;
    
    // Get the binding index for the uniform buffer
    int32_t index = static_cast<int32_t>(argument.index);
    
    // Verify if the uniform already exists
    // TODO: improve this verification to make it more robust
    if (m_Uniforms.Library<UniformLayout>::Exists(group))
    {
        auto& uniform = m_Uniforms.Library<UniformLayout>::Get(group);
        if (uniform.GetIndex() == index)
        {
            uniform.SetShaderType(type);
            return;
        }
    }
    
    // Extract uniform data from the argument
    if (argument.bufferDataType == MTLDataTypeStruct)
    {
        // Uniform is a struct, process each member
        for(MTLStructMember* uniform in argument.bufferStructType.members)
        {
            UniformElement element(utils::graphics::mtl::ToDataType(uniform.dataType));
            element.Offset = static_cast<uint32_t>(uniform.offset);
            
            const char* member = [uniform.name UTF8String];
            m_Uniforms.Add(group, member, element);
        }
    }
    else
    {
        // Uniform is a simple type, add it directly
        UniformElement element(utils::graphics::mtl::ToDataType(argument.bufferDataType));
        m_Uniforms.Add(group, "", element);
    }
    
    // Set the index and shader type for the uniform layout
    auto& uniform = m_Uniforms.Library<UniformLayout>::Get(group);
    uniform.SetIndex(index);
    uniform.SetShaderType(type);
}

/**
 * Extracts and stores information about active attributes and uniforms from the shader program.
 *
 * @param descriptor A pointer to the `MTLRenderPipelineDescriptor` object.
 *
 * @post  `m_Attributes` will contain information about the active attributes.
 * @post  `m_Uniforms` will contain information about the active uniforms.
 */
void MetalShader::ExtractShaderResources(void* descriptor)
{
    // Return early if the data has been already set
    if (!m_Attributes.IsEmpty() || !m_Uniforms.IsEmpty())
        return;
    
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    // Get the Metal device from the context
    id<MTLDevice> device = reinterpret_cast<id<MTLDevice>>(context->GetDevice());
    
    // Get the Metal pipeline descriptor
    MTLRenderPipelineDescriptor* pipelineDescriptor =
        reinterpret_cast<MTLRenderPipelineDescriptor*>(descriptor);
    
    // Obtain shader reflection information
    NSError *error = nil;
    MTLRenderPipelineReflection *reflection = nil;
    [device
        newRenderPipelineStateWithDescriptor:pipelineDescriptor
        options:MTLPipelineOptionArgumentInfo
        reflection:&reflection
        error:&error];
    CORE_ASSERT(!error, "Error creating a reflection of the shader program!");
    
    // TODO: extract this information of the vertex attributes
    
    // Process vertex and fragment uniforms
    for (MTLArgument *argument in reflection.vertexArguments)
        ProcessShaderArgument(reinterpret_cast<void*>(argument), ShaderType::VERTEX);
    for (MTLArgument *argument in reflection.fragmentArguments)
        ProcessShaderArgument(reinterpret_cast<void*>(argument), ShaderType::FRAGMENT);
}

/**
 * Updates and binds uniform buffers for the shader.
 *
 * @note  Assumes that `m_Uniforms` has been populated with valid `UniformLayout`
 *        objects and that the `DataElement` objects within the layouts have
 *        accurate data pointers (`Data`), sizes (`Size`), and offsets (`Offset`).
 */
void MetalShader::UpdateUniformBuffers()
{
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    
    // Get the Metal device and command encoder
    id<MTLDevice> device = reinterpret_cast<id<MTLDevice>>(context->GetDevice());
    id<MTLRenderCommandEncoder> encoder = 
        reinterpret_cast<id<MTLRenderCommandEncoder>>(context->GetEncoder());
    
    // Iterate through each uniform
    for (auto& [uniform, layout]: m_Uniforms)
    {
        uint32_t stride = layout.GetStride();   // Total size of the uniform data
        int32_t index = layout.GetIndex();      // Binding index for the uniform buffer
        
        // Get or create the Metal uniform buffer
        id<MTLBuffer> uniformBuffer;
        void* buffer = layout.GetBufferOfData();
        if (!buffer)
        {
            // Create a new uniform buffer if one doesn't exist
            uniformBuffer = [device
                                newBufferWithLength:stride
                                options:MTLResourceStorageModeShared];
            buffer = reinterpret_cast<void*>(uniformBuffer);
        }
        else
            // If the buffer already exists, retrieve the object
            uniformBuffer = reinterpret_cast<id<MTLBuffer>>(buffer);
        
        // Copy uniform data from individual members into the buffer
        char* content = reinterpret_cast<char*>(uniformBuffer.contents);
        for (auto& name: layout.GetBufferOrder())
        {
            auto& member = layout.Get(name);
            
            // Prevent buffer overflows
            CORE_ASSERT(member.Offset + member.Size <= stride, "Uniform data overflow!");

            // Copy member data into the correct location within the buffer
            memcpy(content + member.Offset, member.Data, member.Size);
        }
        
        // 3. Bind the Uniform Buffer to the Correct Shader Stage
        for (const auto& type : layout.GetShaderType())
        {
            switch (type)
            {
                case ShaderType::VERTEX:
                    [encoder setVertexBuffer:uniformBuffer offset:0 atIndex:index];
                    break;
                case ShaderType::FRAGMENT:
                    [encoder setFragmentBuffer:uniformBuffer offset:0 atIndex:index];
                    break;
                default:
                    CORE_WARN("Unsupported shader type for uniform: {}", uniform);
                    break;
            }
        }
    }
}
