#include "enginepch.h"
#include "Renderer/Renderer.h"

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
 * Render primitives from array data using the specified vertex array.
 *
 * @param vao The VertexArray containing the vertex and index buffers for rendering.
 * @param primitive The type of primitive to be drawn (e.g., Points, Lines, Triangles).
 * @param useIndexBuffer Whether to use the index buffer for rendering or not.
 */
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao,
                    const PrimitiveType &primitive, bool useIndexBuffer)
{
    vao->Bind();
    // Draw using the information in the vertex buffers (without index buffer)
    if (!useIndexBuffer)
    {
        for (const std::shared_ptr<VertexBuffer>& vbo : vao->GetVertexBuffers())
        {
            // Check if geometries should be drawn separately (using segments)
            std::vector<unsigned int> segments = vbo->GetSegments();
            // If no segments, draw the whole buffer
            if (segments.empty())
                glDrawArrays(PrimitiveTypeToOpenGLType(primitive), 0, vbo->GetCount());
            // Draw segments of the buffer separately
            else
            {
                int point = 0;
                for(unsigned int s : segments)
                {
                    glDrawArrays(PrimitiveTypeToOpenGLType(primitive), point, s + 1);
                    point += s + 1;
                }
            }
        }
    }
    // Draw using the information in the index buffer
    else
    {
        vao->GetIndexBuffer()->Bind();
        glDrawElements(PrimitiveTypeToOpenGLType(primitive),
                       vao->GetIndexBuffer()->GetCount(),
                       GL_UNSIGNED_INT, nullptr);
    }
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
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao,
                    const std::shared_ptr<Material>& material, const glm::mat4 &transform,
                    const PrimitiveType &primitive, bool useIndexBuffer)
{
    // Bind the material and set the corresponding information into
    // it for the shading
    material->Bind();
    
    material->GetShader()->SetMat4("u_Transform", s_SceneData->projectionMatrix *
                                   s_SceneData->viewMatrix * transform);
    
    // Render the geometry
    Draw(vao, primitive, useIndexBuffer);
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
