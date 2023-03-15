#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

/**
 * Rendering engine.
 */
class Renderer
{
public:
    /// Constructor/Destructor
    Renderer() = default;
    ~Renderer() = default;
    /// Render
    void Clear() const;
    void Draw(const VertexArray& vao, const IndexBuffer& ibo,
              const Shader& shader) const;
};
