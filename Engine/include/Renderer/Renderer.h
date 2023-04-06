#pragma once

#include <glm/glm.hpp>

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
    void Clear(const glm::vec4& color) const;
    void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Shader>& shader) const;
};
