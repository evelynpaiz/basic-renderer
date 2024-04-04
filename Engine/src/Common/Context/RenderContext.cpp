#include "enginepch.h"
#include "Context/RenderContext.h"

#include "Renderer/Material/SimpleMaterial.h"

/**
 * Define the context where a scene will be rendered.
 *
 * @param width Viewport width.
 * @param height Viewport height.
 * @param viewportShader The shader file path to be used for shading the viewport.
 */
RenderContext::RenderContext(int width, int height, 
                             const std::filesystem::path& viewportShader)
{
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(width, height);
    
    // Define the viewport
    m_Viewport = std::make_shared<Viewport>(width, height, viewportShader);
}

/**
 * @brief Get a material by its name.
 *
 * @param name The name of the material to retrieve.
 *
 * @return The material defined with the input name.
 */
std::shared_ptr<Material> RenderContext::GetMaterial(const std::string& name) const
{
    auto it = m_Materials.find(name);
    if (it != m_Materials.end())
        return it->second;
    
    // Handle error: material not found
    CORE_WARN("Material '{0}' not found!", name);
    return nullptr;
}

/**
 * @brief Get a framebuffer by its name.
 *
 * @param name The name of the framebuffer to retrieve.
 *
 * @return The framebuffer defined with the input name.
 */
std::shared_ptr<FrameBuffer> RenderContext::GetFramebuffer(const std::string& name) const
{
    auto it = m_Framebuffers.find(name);
    if (it != m_Framebuffers.end())
        return it->second;
    
    // Handle error: material not found
    CORE_WARN("Framebuffer '{0}' not found!", name);
    return nullptr;
}

/**
 * @brief Create and add a framebuffer to the framebuffer library.
 *
 * @param name The name of the framebuffer.
 * @param spec The specification of the framebuffer.
 *
 * @return The created framebuffer.
 */
std::shared_ptr<FrameBuffer> RenderContext::CreateFrameBuffer(const std::string& name,
                                                              const FrameBufferSpecification& spec)
{
    auto framebuffer = std::make_shared<FrameBuffer>(spec);
    m_Framebuffers[name] = framebuffer;
    return framebuffer;
}

/**
 * Perform a screen render pass (display into the viewport).
 */
void RenderContext::RenderToScreen()
{
    m_Viewport->Render();
}
