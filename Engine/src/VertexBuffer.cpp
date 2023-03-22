#include "VertexBuffer.h"

#include <GL/glew.h>

/**
 * Generate a vertex buffer and link it to the input vertex data.
 *
 * @param vertices Vertices to be rendered.
 * @param size Size of vertices in bytes.
 */
VertexBuffer::VertexBuffer(const void *vertices, const unsigned int size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

/**
 * Delete the vertex buffer.
 */
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

/**
 * Bind the vertex buffer.
 */
void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

/**
 * Unbind the vertex buffer.
 */
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * Set the layout for the vertex attributes in the buffer.
 *
 * @param layout Buffer layout.
 */
void VertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_Layout = layout;
}

/**
 * Get the layout for the vertex attributes in the buffer.
 *
 * @returns Buffer layout.
 */
const BufferLayout& VertexBuffer::GetLayout() const
{
    return m_Layout;
}
