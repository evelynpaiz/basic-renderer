#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/IndexBuffer.h"

#include "Renderer/Material/Material.h"

#include "Camera/Camera.h"

/**
 * Enumeration representing different types of primitives for rendering.
 */
enum class PrimitiveType
{
    Points,         ///< Points, each vertex represents a point.
    Lines,          ///< Lines, each pair of vertices forms a line segment.
    LineStrip,      ///< Line strip, consecutive vertices form connected lines.
    Triangles,      ///< Triangles, each group of three vertices forms a triangle.
    TriangleStrip   ///< Triangle strip, consecutive vertices form connected triangles.
};

/**
 * Convert a PrimitiveType value to the corresponding OpenGL primitive type.
 *
 * @param type The PrimitiveType value to be converted.
 * @return The corresponding OpenGL primitive type as a GLenum.
 */
inline GLenum PrimitiveTypeToOpenGLType(PrimitiveType type)
{
    switch (type)
    {
        case PrimitiveType::Points: return GL_POINTS;
        case PrimitiveType::Lines: return GL_LINES;
        case PrimitiveType::LineStrip: return GL_LINE_STRIP;
        case PrimitiveType::Triangles: return GL_TRIANGLES;
        case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
    }

    CORE_ASSERT(false, "Unknown primitive type!");
    return 0;
}

/**
 * Represents the current information of the rendered scene (useful for the shading process).
 */
struct SceneData
{
    ///< View (camera) position.
    glm::vec3 viewPosition = glm::vec3(0.0f);
    
    ///< View matrix.
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    ///< Projection matrix.
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
    static void BeginScene();
    static void BeginScene(const std::shared_ptr<Camera>& camera);
    static void EndScene();
    
    // Render
    // ----------------------------------------
    static void Clear();
    static void Clear(const glm::vec4& color);
    static void Draw(const std::shared_ptr<VertexArray>& vao,
                     const PrimitiveType &primitive = PrimitiveType::Triangles,
                     bool useIndexBuffer = true);
    static void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Material>& material,
              const glm::mat4 &transform = glm::mat4(1.0f),
              const PrimitiveType &primitive = PrimitiveType::Triangles,
              bool useIndexBuffer = true);
    
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
