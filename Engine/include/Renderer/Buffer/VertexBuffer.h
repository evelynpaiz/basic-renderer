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
    VertexBuffer(const void *vertices, const unsigned int size,
                 const unsigned int count);
    ~VertexBuffer();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Getter(s)
    // ----------------------------------------
    /// Get the number of vertices.
    /// @return The amount of vertices defined.
    unsigned int GetCount() const { return m_Count; }
    /// @brief Retrieve the current layout of the buffer, specifying the arrangement and format
    /// of vertex attributes within the buffer.
    /// @return The layout of the buffer.
    const BufferLayout& GetLayout() const { return m_Layout; }
    /// @brief Get the segments defining the geometry groups.
    /// @return A constant reference to the vector representing the number of vertices in each segment.
    const std::vector<unsigned int> &GetSegments() const { return m_Segments; }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the layout of the buffer, specifying the arrangement and format
    /// of vertex attributes within the buffer.
    /// @param layout The buffer layout.
    void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
    /// @brief Set the segments for splitting the geometry into groups.
    /// @param segments A vector representing the number of vertices in each segment.
    void SetSegments(const std::vector<unsigned int> &segments) { m_Segments = segments; }
    
    // Vertex buffer variables
    // ----------------------------------------
private:
    ///< ID of the vertex buffer.
    unsigned int m_ID = 0;
    ///< Number of vertices (element count).
    unsigned int m_Count = 0;
    ///< Layout for the vertex attributes.
    BufferLayout m_Layout;
    ///< Number of vertices that represents a joined geometry. Each segment can be considered
    ///< a separate geometry group, and it helps in organizing the rendering of complex geometries
    ///< using different draw calls.
    std::vector<unsigned int> m_Segments;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&&) = delete;

    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&&) = delete;
};
