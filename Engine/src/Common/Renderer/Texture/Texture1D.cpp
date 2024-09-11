#include "enginepch.h"
#include "Common/Renderer/Texture/Texture1D.h"

#include "Common/Renderer/Renderer.h"

#include "Platform/OpenGL/Texture/OpenGLTexture1D.h"

/**
 * Create a 1D texture based on the active rendering API.
 *
 * @return A shared pointer to the created texture, or nullptr if the API is not supported or an error occurs.
 */
std::shared_ptr<Texture1D> Texture1D::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture1D>();
        
/*
#ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalTexture1D>();
#endif
*/
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

/**
 * Create a 1D texture based on the active rendering API.
 *
 * @param spec The texture specifications.
 *
 * @return A shared pointer to the created texture, or nullptr if the API is not supported or an error occurs.
 */
std::shared_ptr<Texture1D> Texture1D::Create(const TextureSpecification& spec)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture1D>(spec);
        
/*
#ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalTexture1D>(spec);
#endif
*/
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

/**
 * Create a 1D texture based on the active rendering API.
 *
 * @param data The data for the 1D texture.
 *
 * @return A shared pointer to the created texture, or nullptr if the API is not supported or an error occurs.
 */
std::shared_ptr<Texture1D> Texture1D::CreateFromData(const void *data)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture1D>(data);
        
/*
#ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalTexture1D>(data);
#endif
*/
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

/**
 * Create a 1D texture based on the active rendering API.
 *
 * @param data The data for the 1D texture.
 * @param spec The texture specifications.
 *
 * @return A shared pointer to the created texture, or nullptr if the API is not supported or an error occurs.
 */
std::shared_ptr<Texture1D> Texture1D::CreateFromData(const void *data,
                                                     const TextureSpecification& spec)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture1D>(data, spec);
        
/*
#ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalTexture1D>(dataspec);
#endif
*/
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}
