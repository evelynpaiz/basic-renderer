#include "enginepch.h"
#include "Renderer/Renderer.h"

#include <GL/glew.h>

/**
 * Clear the buffers to preset values.
 */
void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (m_DepthTest)
            glClear(GL_DEPTH_BUFFER_BIT);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 */
void Renderer::Clear(const glm::vec4& color) const
{
    glClearColor(color.r, color.g, color.b, color.a);
    Clear();
}

/**
 * Render primitives (triangles) from array data.
 *
 * @param vao Vertex array.
 * @param shader Shader program.
 */
void Renderer::Draw(const std::shared_ptr<VertexArray>& vao,
                    const std::shared_ptr<Shader>& shader) const
{
    shader->Bind();
    vao->Bind();
    vao->GetIndexBuffer()->Bind();
    
    glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(),
                   GL_UNSIGNED_INT, nullptr);
}

/**
 * @brief Define if the depth testing is enable in the renderer.
 *
 * @param enable Enable or not the depth testing.
 */
void Renderer::setDepthTest(bool enabled)
{
    if (enabled)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);

    m_DepthTest = enabled;
}
