#include "Renderer/Renderer.h"

#include <GL/glew.h>

/**
 * Clear the buffers to preset values.
 */
void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * Clear the buffers to preset values.
 *
 * @param r Background color (red value)
 * @param g Background color (green value)
 * @param b Background color (blue value)
 * @param a Background color (alpha value)
 */
void Renderer::Clear(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
    Clear();
}

/**
 * Render primitives (triangles) from array data.
 *
 * @param vao Vertex array.
 * @param ibo Index buffer.
 * @param shader Shader program.
 */
void Renderer::Draw(const VertexArray& vao, const Shader& shader) const
{
    shader.Bind();
    vao.Bind();
    vao.GetIndexBuffer().Bind();
    
    glDrawElements(GL_TRIANGLES, vao.GetIndexBuffer().GetCount(),
                   GL_UNSIGNED_INT, nullptr);
}
