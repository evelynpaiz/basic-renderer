#include "VertexArray.h"

#include <GL/glew.h>

/**
 * Generate a vertex array.
 */
VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

/**
 * Delete the vertex array.
 */
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}


/**
 * Link a vertex buffer to the vertex array.
 *
 * @param vbo Vertex buffer.
 * @param layout Layout of the attributes of the vertex buffer.
 */
void VertexArray::AddVertexBuffer(const VertexBuffer& vbo)
{
    // Bind the vertex array and the buffer
    Bind();
    vbo.Bind();
    // Define the vertex attribute pointers
    unsigned int index = 0;
    const auto& layout = vbo.GetLayout();
    for (const auto& element : layout)
    {
        glVertexAttribPointer(index, element.GetComponentCount(),
            DataTypeToOpenGLType(element.Type), element.Normalized,
            layout.GetStride(), (const void*)(size_t)element.Offset);
        glEnableVertexAttribArray(index);
        index++;
    }
    Unbind();
}

/**
 * Bind the vertex array.
 */
void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

/**
 * Unbind the vertex array.
 */
void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
