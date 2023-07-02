#include "enginepch.h"
#include "Renderer/Renderer.h"

#include <GL/glew.h>

// Define the renderer variable(s)
bool Renderer::s_DepthTest = false;
std::unique_ptr<SceneData> Renderer::s_SceneData = std::make_unique<SceneData>();

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param camera Rendering camera.
 */
void Renderer::BeginScene(const std::shared_ptr<Camera> &camera)
{
    s_SceneData->viewMatrix = camera->GetViewMatrix();
    s_SceneData->projectionMatrix = camera->GetProjectionMatrix();
}

/**
 * End the rendering of a scene.
 */
void Renderer::EndScene()
{}

/**
 * Clear the buffers to preset values.
 */
void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (s_DepthTest)
        glClear(GL_DEPTH_BUFFER_BIT);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 */
void Renderer::Clear(const glm::vec4& color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    Clear();
}

/**
 * Render primitives (triangles) from array data.
 *
 * @param vao Vertex array.
 */
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao)
{
    vao->Bind();
    vao->GetIndexBuffer()->Bind();
    glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);
}

/**
 * Render primitives (triangles) from array data.
 *
 * @param vao Vertex array.
 * @param shader Shader program.
 * @param transform Transformation matrix of the geometry (model matrix).
 */
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao,
                    const std::shared_ptr<Material>& material,
                    const glm::mat4& transform)
{
    // Bind the material and set the corresponding information into
    // it for the shading
    material->Bind();
    material->GetShader()->SetMat4("u_Transform", s_SceneData->projectionMatrix *
                                   s_SceneData->viewMatrix * transform);
    
    // Render the geometry
    Draw(vao);
}

/**
 * Define if the depth testing is enable in the renderer.
 *
 * @param enable Enable or not the depth testing.
 */
void Renderer::setDepthTest(bool enabled)
{
    if (enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    s_DepthTest = enabled;
}
