#pragma once

#include "Common/Renderer/RendererAPI.h"

/**
 * Concrete implementation of the RendererAPI interface for Metal.
 *
 * The `MetalRendererAPI` class implements the `RendererAPI` abstract methods
 * specifically for the Metal rendering API.
 */
class MetalRendererAPI : public RendererAPI
{
public:
    // Initialization
    // ----------------------------------------
    void Init() override;
    
    // Clear
    // ----------------------------------------
    void Clear(const BufferState& buffersActive = {}) override;
    void Clear(const glm::vec4& color, const BufferState& buffersActive = {}) override;
    
    // Draw
    // ----------------------------------------
    void Draw(const std::shared_ptr<Drawable>& drawable,
              const PrimitiveType &primitive = PrimitiveType::Triangles) override;
    
    // Setter(s)
    // ----------------------------------------
    void SetViewport(unsigned int x, unsigned int y,
                     unsigned int width, unsigned int height) override;
    
    void SetDepthTesting(const bool enabled) override;
};
