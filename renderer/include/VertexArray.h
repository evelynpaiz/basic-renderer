#pragma once

#include "VertexBuffer.h"
#include "BufferLayout.h"

/**
 * A vertex array used to describe how the vertex attributes are stored (its layout) in a vertex buffer.
 */
class VertexArray
{
public:
    /// Constructors/Destructor
    VertexArray();
    ~VertexArray();
    /// Buffers
    void AddVertexBuffer(const VertexBuffer& vbo, const BufferLayout& layout);
    /// Usage
    void Bind() const;
    void Unbind() const;
    
private:
    /// ID of the vertex array
    unsigned int m_ID = 0;
};
