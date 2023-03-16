#pragma once

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
    
private:
    /// ID of the vertex buffer
    unsigned int m_ID = 0;
};
