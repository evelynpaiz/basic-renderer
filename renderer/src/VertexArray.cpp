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
void VertexArray::AddVertexBuffer(const VertexBuffer& vbo, const BufferLayout& layout)
{
    // Bind the vertex array and the buffer
    Bind();
    vbo.Bind();
    // Define the vertex attribute pointers
    const std::vector<BufferElement> elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); ++i)
    {
        BufferElement element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized,
                              layout.GetStride(), (const void*)(size_t)offset);
        glEnableVertexAttribArray(i);
        offset += element.count * BufferElement::GetSizeOfType(element.type);
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
