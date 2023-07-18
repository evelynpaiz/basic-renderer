#pragma once

#include "Renderer/Buffer/BufferLayout.h"

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
    // ----------------------------------------
    VertexBuffer(const void *vertices, const unsigned int size);
    ~VertexBuffer();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Buffer layout
    // ----------------------------------------
    /// @brief Retrieve the current layout of the buffer, specifying the arrangement and format
    /// of vertex attributes within the buffer.
    /// @return The layout of the buffer.
    const BufferLayout& GetLayout() const { return m_Layout; }
    /// @brief Set the layout of the buffer, specifying the arrangement and format
    /// of vertex attributes within the buffer.
    /// @param layout The buffer layout.
    void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
    
    // Vertex buffer variables
    // ----------------------------------------
private:
    ///< ID of the vertex buffer.
    unsigned int m_ID = 0;
    ///< Layout for the vertex attributes.
    BufferLayout m_Layout;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;
};
