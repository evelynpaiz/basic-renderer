#pragma once

#include "Renderer/BufferLayout.h"

/**
 * Represents a vertex buffer for storing vertex data.
 * 
 * The `VertexBuffer` class manages vertex buffers used to store vertex attribute data (such as
 * position, color, texture coordinates, etc.). This data is used by the graphics pipeline during rendering.
 * It provides functions for creation, binding, and management of vertex buffers.
 *
 * Copying or moving `VertexBuffer` objects is disabled to ensure single ownership and prevent
 * unintended buffer duplication.
 */
class VertexBuffer
{
public:
    // Constructor(s)/Destructor
    VertexBuffer(const void *vertices, const unsigned int size);
    ~VertexBuffer();
    // Usage
    void Bind() const;
    void Unbind() const;
    // Buffer layout
    void SetLayout(const BufferLayout& layout);
    const BufferLayout& GetLayout() const;
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;
    // Operators
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;
    
private:
    ///< ID of the vertex buffer.
    unsigned int m_ID = 0;
    ///< Layout for the vertex attributes.
    BufferLayout m_Layout;
};
