#include "enginepch.h"
#include "Common/Renderer/Drawable/Drawable.h"

#include "Common/Renderer/Renderer.h"

#include "Platform/OpenGL/Drawable/OpenGLDrawable.h"
#include "Platform/Metal/Drawable/MetalDrawable.h"

/**
 * Create a drawable object based on the active rendering API.
 *
 * @return A shared pointer to the created drawable, or `nullptr` if the API
 *         is not supported or an error occurs.
 */
std::shared_ptr<Drawable> Drawable::Create()
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
            
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLDrawable>();
        
    #ifdef __APPLE__
        case RendererAPI::API::Metal:
             return std::make_shared<MetalDrawable>();
    #endif
    }
    
    CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}
