#include "enginepch.h"
#include "Common/Renderer/Buffer/VertexBuffer.h"

#include "Common/Renderer/Renderer.h"

#include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"
#include "Platform/Metal/Buffer/MetalVertexBuffer.h"

/**
 * Create a vertex buffer based on the active rendering API.
 *
 * @param vertices Vertices to be rendered.
 * @param size Size of vertices in bytes.
 * @param count Number of vertices.
 *
 * @return A shared pointer to the created vertex buffer, or nullptr if the API
 *         is not supported or an error occurs.
 */
std::shared_ptr<VertexBuffer> VertexBuffer::Create(const void* vertices, const uint32_t size,
                                                   const uint32_t count)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size, count);
             
    #ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalVertexBuffer>(vertices, size, count);
    #endif
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}
