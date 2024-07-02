#pragma once

#include "Common/Renderer/RendererAPI.h"

#include <glm/glm.hpp>

/**
 * A static class that provides an interface to the rendering API.
 *
 * The `RendererCommand` class provides a set of static methods that can be used
 * to interact with the rendering API. It uses a singleton pattern to ensure that only one
 * instance of the Renderer API is created.
 */
class RendererCommand
{
public:
    // Initialization
    // ----------------------------------------
    static void Init();
    
    // Clear
    // ----------------------------------------
    static void Clear(const BufferState& buffersActive = {});
    static void Clear(const glm::vec4& color, const BufferState& buffersActive = {});
    
    // Render
    // ----------------------------------------
    static void Draw(const std::shared_ptr<Drawable>& drawable,
                     const PrimitiveType &primitive = PrimitiveType::Triangles);
    
    // Setter(s)
    // ----------------------------------------
    static void SetViewport(unsigned int x, unsigned int y, 
                            unsigned int width, unsigned int height);
    
    static void SetDepthTesting(const bool enabled);
    
    // Renderer variables
    // ----------------------------------------
private:
    ///< Rendering API.
    static std::unique_ptr<RendererAPI> s_API;
};
