#include "Renderer.h"

#include <GL/glew.h>

/**
 * Clear the buffers to preset values.
 */
void Renderer::Clear() const
{
    glClearColor(0.93f, 0.93f, 0.93f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * Render primitives (triangles) from array data.
 *
 * @param vao Vertex array.
 * @param ibo Index buffer.
 * @param shader Shader program.
 */
void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo,
                    const Shader& shader) const
{
    shader.Bind();
    vao.Bind();
    ibo.Bind();
    
    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}
