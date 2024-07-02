#include "enginepch.h"
#include "Common/Renderer/Buffer/IndexBuffer.h"

#include "Common/Renderer/Renderer.h"

#include "Platform/OpenGL/Buffer/OpenGLIndexBuffer.h"
#include "Platform/Metal/Buffer/MetalIndexBuffer.h"

/**
 * Create a vertex buffer based on the active rendering API.
 *
 * @param indices Index information for the vertices.
 * @param count Number of indices.
 *
 * @return A shared pointer to the created index buffer, or nullptr if the API
 *         is not supported or an error occurs.
 */
std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t *indices,
                                                 const uint32_t count)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, count);
             
    #ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalIndexBuffer>(indices, count);
    #endif
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}
