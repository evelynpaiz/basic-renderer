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
    // ----------------------------------------
    /// @brief Generate a renderer.
    Renderer() = default;
    /// @brief Delete the renderer.
    ~Renderer() = default;
    
    // Render
    // ----------------------------------------
    void Clear() const;
    void Clear(const glm::vec4& color) const;
    void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Shader>& shader) const;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Check if depth testing is active.
    /// @return `true` if the renderer is doing depth testing.
    bool IsDepthTestActive() const { return m_DepthTest; }
    
    // Setter(s)
    // ----------------------------------------
    void setDepthTest(bool enabled);
    
private:
    ///< Depth testing.
    bool m_DepthTest = false;
};
