#pragma once

#include <glm/glm.hpp>

#include "Renderer/VertexArray.h"
#include "Renderer/IndexBuffer.h"

#include "Material/Material.h"

#include "Camera/Camera.h"

/**
 * Represents the current information of the rendered scene (useful for the shading process).
 */
struct SceneData
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
};

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
    // Scene parametrization
    // ----------------------------------------
    static void BeginScene(const std::shared_ptr<Camera>& camera);
    static void EndScene();
    
    // Render
    // ----------------------------------------
    static void Clear();
    static void Clear(const glm::vec4& color);
    static void Draw(const std::shared_ptr<VertexArray>& vao);
    static void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Material>& material,
              const glm::mat4& transform = glm::mat4(1.0f));
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Check if depth testing is active.
    /// @return `true` if the renderer is doing depth testing.
    static bool IsDepthTestActive() { return s_DepthTest; }
    
    // Setter(s)
    // ----------------------------------------
    static void setDepthTest(bool enabled);
    
private:
    ///< Depth testing.
    static bool s_DepthTest;
    ///< Scene current general information.
    static std::unique_ptr<SceneData> s_SceneData;
};
