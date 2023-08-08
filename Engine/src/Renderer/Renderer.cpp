#include "enginepch.h"
#include "Renderer/Renderer.h"

#include <GL/glew.h>

// Define the renderer variable(s)
bool Renderer::s_ColorBuffer = true;
bool Renderer::s_DepthBuffer = false;
std::unique_ptr<SceneData> Renderer::s_SceneData = std::make_unique<SceneData>();

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param camera Rendering camera.
 */
void Renderer::BeginScene()
{
    s_SceneData->viewPosition = glm::vec3(0.0);
    
    s_SceneData->viewMatrix = glm::mat4(1.0f);
    s_SceneData->projectionMatrix = glm::mat4(1.0f);
}

/**
 * Start the rendering of a scene by defining its general parameters.
 *
 * @param camera Rendering camera.
 */
void Renderer::BeginScene(const std::shared_ptr<Camera> &camera)
{
    s_SceneData->viewPosition = camera->GetPosition();
    
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
    if (s_ColorBuffer)
        glClear(GL_COLOR_BUFFER_BIT);
    
    if (s_DepthBuffer)
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
                glDrawArrays(utils::OpenGL::PrimitiveTypeToOpenGLType(primitive), 0, vbo->GetCount());
            // Draw segments of the buffer separately
            else
            {
                int point = 0;
                for(unsigned int s : segments)
                {
                    glDrawArrays(utils::OpenGL::PrimitiveTypeToOpenGLType(primitive), point, s + 1);
                    point += s + 1;
                }
            }
        }
    }
    // Draw using the information in the index buffer
    else
    {
        vao->GetIndexBuffer()->Bind();
        glDrawElements(utils::OpenGL::PrimitiveTypeToOpenGLType(primitive),
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
    
    material->GetShader()->SetMat4("u_Transform.Model", transform);
    material->GetShader()->SetMat4("u_Transform.View", s_SceneData->viewMatrix);
    material->GetShader()->SetMat4("u_Transform.Projection", s_SceneData->projectionMatrix);

    if (material->IsNormalMatrixDefined())
        material->GetShader()->SetMat3("u_Transform.Normal", glm::mat3(glm::transpose(glm::inverse(transform))));
    
    if (material->IsViewDirectionDefined())
        material->GetShader()->SetVec3("u_View.Position", s_SceneData->viewPosition);
    
    // Render the geometry
    Draw(vao, primitive, useIndexBuffer);
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
void Renderer::SetDepthBuffer(bool enabled)
{
    if (enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    s_DepthBuffer = enabled;
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
