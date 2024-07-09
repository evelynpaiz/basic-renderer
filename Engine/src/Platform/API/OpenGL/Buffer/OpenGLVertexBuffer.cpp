#include "enginepch.h"
#include "Platform/OpenGL/Buffer/OpenGLVertexBuffer.h"

#include <GL/glew.h>

/**
 * Generate a vertex buffer and link it to the input vertex data.
 *
 * @param vertices Vertices to be rendered.
 * @param size Size of vertices in bytes.
 * @param count Number of vertices.
 */
OpenGLVertexBuffer::OpenGLVertexBuffer(const void *vertices, const uint32_t size,
                                       const uint32_t count)
    : VertexBuffer(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

/**
 * Delete the vertex buffer.
 */
OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

/**
 * Bind the vertex buffer.
 */
void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

/**
 * Unbind the vertex buffer.
 */
void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}