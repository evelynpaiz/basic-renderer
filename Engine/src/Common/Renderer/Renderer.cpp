#include "enginepch.h"
#include "Common/Renderer/Renderer.h"

#include "Common/Renderer/RendererCommand.h"
#include "Common/Renderer/Material/LightedMaterial.h"

#include <GL/glew.h>

// Define the renderer variable(s)
std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

static Renderer::RenderingStatistics g_Stats;

static const glm::mat4 g_TextureMatrix = glm::mat4(
    0.5f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f
);

/**
 * Initialize the renderer.
 */
void Renderer::Init()
{
    RendererCommand::Init();
}

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param camera Rendering camera.
 */
void Renderer::BeginScene()
{
    s_SceneData->ViewPosition = glm::vec3(0.0);
    
    s_SceneData->ViewMatrix = glm::mat4(1.0f);
    s_SceneData->ProjectionMatrix = glm::mat4(1.0f);
}

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param camera Rendering camera.
 */
void Renderer::BeginScene(const std::shared_ptr<Camera> &camera)
{
    s_SceneData->ViewPosition = camera->GetPosition();
    
    s_SceneData->ViewMatrix = camera->GetViewMatrix();
    s_SceneData->ProjectionMatrix = camera->GetProjectionMatrix();
}

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param view The view matrix transformation.
 * @param projection The projection matrix transformation.
 * @param position The view position.
 */
void Renderer::BeginScene(const glm::mat4 &view, const glm::mat4 &projection,
                          const glm::vec3& position)
{
    s_SceneData->ViewPosition = position;
    
    s_SceneData->ViewMatrix = view;
    s_SceneData->ProjectionMatrix = projection;
}

/**
 * End the rendering of a scene.
 */
void Renderer::EndScene()
{
    g_Stats.renderPasses++;
}

/**
 * Clear the buffers to preset values.
 */
void Renderer::Clear(const BufferState& buffersActive)
{
    // Clear buffers
    glClear(utils::OpenGL::BufferStateToOpenGLMask(buffersActive));
    // Activate depth testing if the depth buffer is active
    SetDepthTesting(buffersActive.depthBufferActive);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 */
void Renderer::Clear(const glm::vec4& color, const BufferState& buffersActive)
{
    glClearColor(color.r, color.g, color.b, color.a);
    Clear(buffersActive);
}

/**
 * Render primitives from array data using the specified vertex array.
 *
 * @param vao The VertexArray containing the vertex and index buffers for rendering.
 * @param primitive The type of primitive to be drawn (e.g., Points, Lines, Triangles).
 * @param useIndexBuffer Whether to use the index buffer for rendering or not.
 */
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao, const PrimitiveType &primitive)
{
    vao->Bind();
    vao->GetIndexBuffer()->Bind();
    glDrawElements(utils::OpenGL::PrimitiveTypeToOpenGLType(primitive),
                   vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    
    g_Stats.drawCalls++;
}

/**
 * Render primitives from array data using the specified vertex array.
 *
 * @param vao The VertexArray containing the vertex and index buffers for rendering.
 * @param shader The shader program.
 * @param transform The transformation matrix of the geometry (model matrix).
 * @param primitive The type of primitive to be drawn (e.g., Points, Lines, Triangles).
 * @param useIndexBuffer Whether to use the index buffer for rendering or not.
 */

void Renderer::Draw(const std::shared_ptr<VertexArray>& vao, const std::shared_ptr<Material>& material,
                    const glm::mat4 &transform, const PrimitiveType &primitive)
{
    // Bind the material and set the corresponding information into
    // it for the shading
    material->Bind();
    
    // Set the model, view, and projection matrices in the shader
    material->GetShader()->SetMat4("u_Transform.Model", transform);
    material->GetShader()->SetMat4("u_Transform.View", s_SceneData->ViewMatrix);
    material->GetShader()->SetMat4("u_Transform.Projection", s_SceneData->ProjectionMatrix);

    // Check the flags for the material
    auto& flags = material->GetMaterialFlags();
    if (flags.ViewDirection)
        material->GetShader()->SetVec3("u_View.Position", s_SceneData->ViewPosition);
    if (flags.NormalMatrix)
        material->GetShader()->SetMat3("u_Transform.Normal", glm::mat3(glm::transpose(glm::inverse(transform))));
    
    auto lightedMaterial = std::dynamic_pointer_cast<LightedMaterial>(material);
    if (lightedMaterial)
    {
        // Check the flags for the lighted material
        auto& lightFlags = lightedMaterial->GetLightFlags();
        if (lightFlags.ShadowProperties)
            material->GetShader()->SetMat4("u_Transform.Texture", g_TextureMatrix);
    }
    
    // Render the geometry
    Draw(vao, primitive);
    
    // Unbind the material
    material->Unbind();
}

/**
 * Set the viewport for rendering.
 *
 * @param x The x-coordinate of the lower-left corner of the viewport.
 * @param y The y-coordinate of the lower-left corner of the viewport.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 */
void Renderer::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    glViewport(x, y, width, height);
}

/**
 * Set the depth buffer flag when rendering. If enabled, depth testing is enabled too.
 *
 * @param enable Enable or not the depth testing.
 */
void Renderer::SetDepthTesting(bool enabled)
{
    if (enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
}

/**
 * Set the depth function for rendering.
 *
 * The depth function determines how fragments (pixels) are compared to the depth buffer
 * to determine if they should be drawn or discarded.
 *
 * @param depth The depth function to be set.
 */
void Renderer::SetDepthFunction(const DepthFunction depth)
{
    glDepthFunc(utils::OpenGL::DepthToOpenGLType(depth));
}

/**
 * @brief Set the face culling mode for rendering.
 *
 * Face culling is a technique used to improve rendering performance by discarding
 * the rendering of faces that are not visible, such as the back faces of 3D objects.
 *
 * @param culling The face culling mode to be set.
 */
void Renderer::SetFaceCulling(const FaceCulling culling)
{
    glCullFace(utils::OpenGL::CullingToOpenGLType(culling));
}

/**
 * Enable or disable seamless cubemap sampling.
 *
 * This function allows you to enable or disable seamless cubemap sampling, which
 * can improve the visual quality when rendering cubemaps, especially when used as
 * skyboxes or for environment mapping.
 *
 * @param enabled Set to `true` to enable seamless cubemap sampling, or `false` to disable it.
 */
void Renderer::SetCubeMapSeamless(const bool enabled)
{
    if (enabled)
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    else
        glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

/**
 * Reset rendering statistics.
 *
 * This function resets the stored rendering statistics, including information about
 * the number of draw calls, vertices rendered, and other rendering-related data.
 * After calling this function, the statistics will be reset to zero values.
 */
void Renderer::ResetStats()
{
    memset(&g_Stats, 0, sizeof(RenderingStatistics));
}

/**
 * Get the current rendering statistics.
 *
 * @return The rendering statistics structure containing performance metrics.
 */
Renderer::RenderingStatistics Renderer::GetStats()
{
    return g_Stats;
}

