#include "enginepch.h"
#include "Platform/OpenGL/Buffer/OpenGLVertexArray.h"

#include "Platform/OpenGL/OpenGLRendererUtils.h"

#include <GL/glew.h>

/**
 * Generate a vertex array.
 */
OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_ID);
}

/**
 * Delete the vertex array.
 */
OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

/**
 * Bind the vertex array.
 */
void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

/**
 * Unbind the vertex array.
 */
void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

/**
 * Link an input vertex buffer to the vertex array.
 *
 * @param vbo Vertex buffer.
 * @param index Attribute index.
 */
void OpenGLVertexArray::SetVertexAttributes(const std::shared_ptr<VertexBuffer>& vbo,
                                            unsigned int& index)
{
    // Check if the vertex buffer has a layout defined
    CORE_ASSERT(!vbo->GetLayout().IsEmpty(), "Vertex buffer has no layout!");
    
    // Bind the vertex array and the vertex buffer
    Bind();
    vbo->Bind();
    // Define the vertex attribute pointers
    const auto& layout = vbo->GetLayout();
    for (const auto& name : layout.GetBufferOrder())
    {
        // Define the vertex attribute
        auto& element = layout.Get(name);
        glVertexAttribPointer(index,
                              utils::data::GetComponentCount(element.Type),
                              utils::graphics::gl::ToOpenGLType(element.Type),
                              element.Normalized,
                              layout.GetStride(),
                              (const void*)(size_t)element.Offset);
        glEnableVertexAttribArray(index);
        index++;
    }
    
    // Unbind the vertex array and the vertex buffer
    vbo->Unbind();
    Unbind();
}
