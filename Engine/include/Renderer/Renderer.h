#pragma once

#include <glm/glm.hpp>

#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

/**
 * Responsible for rendering geometry using a specified shader program.
 *
 * The `Renderer` class serves as the central component for performing rendering operations. It
 * provides methods to clear the screen, set the clear color, and draw geometry using a `VertexArray`
 * object and a `Shader` program.
 */
class Renderer
{
public:
    // Constructor(s)/Destructor
    Renderer() = default;
    ~Renderer() = default;
    // Render
    void Clear() const;
    void Clear(const glm::vec4& color) const;
    void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Shader>& shader) const;
};
