#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

/**
 * Rendering engine.
 */
class Renderer
{
public:
    /// Constructor(s)/ Destructor
    Renderer() = default;
    ~Renderer() = default;
    /// Render
    void Clear() const;
    void Clear(float r, float g, float b, float a = 1.0f) const;
    void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Shader>& shader) const;
};
