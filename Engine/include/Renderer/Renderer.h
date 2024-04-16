#pragma once

#include "Renderer/RendererUtils.h"

#include "Renderer/Buffer/VertexArray.h"
#include "Renderer/Buffer/IndexBuffer.h"
#include "Renderer/Buffer/FrameBuffer.h"

#include "Renderer/Material/Material.h"

#include "Camera/Camera.h"

#include <glm/glm.hpp>

class LightLibrary;

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
    static void BeginScene(const glm::mat4& view, const glm::mat4& projection,
                           const glm::vec3& position = glm::vec3(0.0f));
    static void EndScene();
    
    // Render
    // ----------------------------------------
    static void Clear(const BufferState& buffersActive = {});
    static void Clear(const glm::vec4& color, const BufferState& buffersActive = {});
    static void Draw(const std::shared_ptr<VertexArray>& vao,
                     const PrimitiveType &primitive = PrimitiveType::Triangles);
    static void Draw(const std::shared_ptr<VertexArray>& vao,
              const std::shared_ptr<Material>& material,
              const glm::mat4 &transform = glm::mat4(1.0f),
              const PrimitiveType &primitive = PrimitiveType::Triangles);
    
    // Getters(s)
    // ----------------------------------------
    static MaterialLibrary& GetMaterialLibrary() { return s_MaterialLibrary; }

    // Setter(s)
    // ----------------------------------------
    static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
    
    static void SetDepthTesting(const bool enabled);
    static void SetDepthFunction(const DepthFunction depth);
    static void SetFaceCulling(const FaceCulling culling);
    static void SetCubeMapSeamless(const bool enabled);
    
    // Statistics
    // ----------------------------------------
    /**
     * Represents the information related to the statistics of the rendering.
     */
    struct RenderingStatistics
    {
        ///< Number or rendering passes.
        unsigned int renderPasses = 0;
        ///< Number of times the draw function is called.
        unsigned int drawCalls = 0;
    };
    
    static void ResetStats();
    static RenderingStatistics GetStats();
    
    // Renderer Structures
    // ----------------------------------------
private:
    /**
     * Represents the current information of the rendered scene (useful for the shading process).
     */
    struct SceneData
    {
        ///< View position.
        glm::vec3 ViewPosition = glm::vec3(0.0f);
        
        ///< View matrix.
        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        ///< Projection matrix.
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
    };
    
    // Renderer variables
    // ----------------------------------------
private:
    ///< Scene current general information.
    static std::unique_ptr<SceneData> s_SceneData;
    
    ///< Rendering libraries.
    static inline MaterialLibrary s_MaterialLibrary;
};
