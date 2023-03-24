#pragma once

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/BufferLayout.h"

#include <vector>

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
    void AddVertexBuffer(const VertexBuffer& vbo);
    void SetIndexBuffer(const IndexBuffer& ibo);
    /// Usage
    void Bind() const;
    void Unbind() const;
    /// Gets
    const std::vector<VertexBuffer>& GetVertexBuffers() const;
    const IndexBuffer& GetIndexBuffer() const;
    
private:
    /// ID of the vertex array
    unsigned int m_ID = 0;
    /// Vertex attribute index
    unsigned int m_Index = 0;
    
    /// Linked vertex buffers (possible to have more than one)
    std::vector<VertexBuffer> m_VertexBuffers;
    /// Linked index buffer
    IndexBuffer m_IndexBuffer;
};
