#include "enginepch.h"
#include "Renderer/Buffer/VertexArray.h"

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
        glVertexAttribPointer(m_Index, utils::OpenGL::GetCompCountOfType(element.Type),
            utils::OpenGL::DataTypeToOpenGLType(element.Type), element.Normalized,
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
