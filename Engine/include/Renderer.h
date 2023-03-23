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
    void Clear(float r, float g, float b, float a = 1.0f) const;
    void Draw(const VertexArray& vao, const Shader& shader) const;
};
