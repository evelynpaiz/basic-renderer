#pragma once

#include "Context/Viewport.h"

template<typename Type>
using Library = std::unordered_map<std::string, std::shared_ptr<Type>>;

/**
 * Manages the rendering context including viewport, materials, and framebuffers.
 *
 * The `RenderContext` class encapsulates various aspects of the rendering process,
 * such as the rendering camera, viewport settings, materials library, and framebuffers library.
 */
class RenderContext
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    RenderContext(int width, int height,
                  const std::filesystem::path& viewportShader = "");
    /// @brief Deletes the render context.
    ~RenderContext() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the camera used currently to render the scene.
    /// @return The active camera.
    const std::shared_ptr<Camera>& GetCamera() const { return m_Camera; }
    
    /// @brief Get the viewport where the scene is being rendered.
    /// @return The viewport.
    const std::shared_ptr<Viewport>& GetViewport() const { return m_Viewport; }
    
    std::shared_ptr<Material> GetMaterial(const std::string& name) const;
    std::shared_ptr<FrameBuffer> GetFramebuffer(const std::string& name) const;
    
    /// @brief Get the materials library.
    /// @return The defined materials.
    const Library<Material>& GetMaterials() const { return m_Materials; }
    /// @brief Get the framebuffers library.
    /// @return The defined framebuffers.
    const Library<FrameBuffer>& GetFramebuffers() const { return m_Framebuffers; }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Create and add a material to the materials library.
    /// @tparam MaterialType The type of material to create.
    /// @tparam Args The types of arguments to pass to the material constructor.
    /// @param name The name of the material.
    /// @param args The arguments to pass to the material constructor.
    /// @return The created material.
    template<typename MaterialType, typename... Args>
    std::shared_ptr<MaterialType> CreateMaterial(const std::string& name, Args&&... args)
    {
        auto material = std::make_shared<MaterialType>(std::forward<Args>(args)...);
        m_Materials[name] = material;
        return material;
    }
    
    std::shared_ptr<FrameBuffer> CreateFrameBuffer(const std::string& name,
                                                   const FrameBufferSpecification& spec);
    
    // Render
    // ----------------------------------------
    void RenderToScreen();
    
    // Scene variables
    // ----------------------------------------
private:
    ///< Rendering camera.
    std::shared_ptr<Camera> m_Camera;
    ///< Viewport (displays the rendered image).
    std::shared_ptr<Viewport> m_Viewport;
    
    ///< Material(s) library.
    Library<Material> m_Materials;
    ///< Framebufer(s) library.
    Library<FrameBuffer> m_Framebuffers;
};
