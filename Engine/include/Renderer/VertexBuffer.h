#pragma once

#include "Renderer/BufferLayout.h"

/**
 * Stores the vertices information in the GPU's memory.
 */
class VertexBuffer
{
public:
    /// Constructors/Destructor
    VertexBuffer(const void *vertices, const unsigned int size);
    ~VertexBuffer();
    /// Usage
    void Bind() const;
    void Unbind() const;
    /// Buffer layout
    void SetLayout(const BufferLayout& layout);
    const BufferLayout& GetLayout() const;
    
private:
    /// ID of the vertex buffer
    unsigned int m_ID = 0;
    /// Layout for the vertex attributes
    BufferLayout m_Layout;
};
