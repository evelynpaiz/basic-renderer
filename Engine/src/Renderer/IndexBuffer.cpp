#include "enginepch.h"
#include "Renderer/IndexBuffer.h"

#include <GL/glew.h>

/**
 * Generate an index buffer and link it to the input indices.
 *
 * @param indices Index information for the vertices.
 * @param count Number of indices.
 */
IndexBuffer::IndexBuffer(const unsigned int *indices, const unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(count * sizeof(unsigned int)),
        indices, GL_STATIC_DRAW);
}

/**
 * Delete the index buffer.
 */
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

/**
 * Bind the index buffer.
 */
void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

/**
 * Unbind the index buffer.
 */
void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 * Get the number of indices.
 *
 * @return The count of indices.
 */
unsigned int IndexBuffer::GetCount() const
{
    return m_Count;
}
