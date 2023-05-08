#include "enginepch.h"
#include "Renderer/VertexArray.h"

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
 * Link an input vertex buffer to the vertex array.
 *
 * @param vbo Vertex buffer.
 */
void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
{
    // Check if the vertex buffer has a layout defined
    CORE_ASSERT(vbo->GetLayout().GetElements().size(),
                "Vertex buffer has no layout!");
    
    // Bind the vertex array and the buffer
    Bind();
    vbo->Bind();
    // Define the vertex attribute pointers
    const auto& layout = vbo->GetLayout();
    for (const auto& element : layout)
    {
        glVertexAttribPointer(m_Index, GetCompCountOfType(element.Type),
            DataTypeToOpenGLType(element.Type), element.Normalized,
            layout.GetStride(), (const void*)(size_t)element.Offset);
        glEnableVertexAttribArray(m_Index);
        m_Index++;
    }
    
    vbo->Unbind();
    Unbind();
    
    // Add to the list of vertex buffers linked
    m_VertexBuffers.push_back(vbo);
    
}

/**
 * Link an input index buffer to the vertex array.
 *
 * @param ibo Index buffer object.
 */
void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo)
{
    m_IndexBuffer = ibo;
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

/**
 * Get all the associated vertex buffers to this vertex array.
 *
 * @return Set of vertex buffers.
 */
const std::vector<std::shared_ptr<VertexBuffer>>& VertexArray::GetVertexBuffers() const
{
    return m_VertexBuffers;
}

/**
 * Get the index buffer associated to this vertex array.
 *
 * @return The index buffer.
 */
const std::shared_ptr<IndexBuffer>& VertexArray::GetIndexBuffer() const
{
    return m_IndexBuffer;
}
