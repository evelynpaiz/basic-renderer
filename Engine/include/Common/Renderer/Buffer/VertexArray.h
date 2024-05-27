#pragma once

#include "Common/Renderer/Buffer/VertexBuffer.h"
#include "Common/Renderer/Buffer/IndexBuffer.h"
#include "Common/Renderer/Buffer/BufferLayout.h"

/**
 * Represents a vertex array that describes how vertex attributes are stored in vertex buffer(s).
 *
 * The `VertexArray` class manages the overall state and bindings related to vertex attributes.
 * It allows for adding multiple vertex buffers and setting an index buffer. Use this class to define
 * the complete layout of vertex data for rendering a `Mesh`.
 *
 * Copying or moving `VertexArray` objects is disabled to ensure single ownership and prevent
 * unintended duplication.
 */
class VertexArray
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    VertexArray();
    ~VertexArray();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get all the associated vertex buffers to this vertex array.
    /// @return Set of vertex buffers.
    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const
    {
        return m_VertexBuffers;
    }
    /// @brief Get the index buffer associated to this vertex array.
    /// @return The index buffer.
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const
    {
        return m_IndexBuffer;
    }
    
    // Setter(s)
    // ----------------------------------------
    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
    /// @brief Link an input index buffer to the vertex array.
    /// @param ibo Index buffer object.
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo)
    {
        m_IndexBuffer = ibo;
    }
    
    // Vertex array variables
    // ----------------------------------------
private:
    ///< ID of the vertex array.
    unsigned int m_ID = 0;
    ///< Vertex attribute index.
    unsigned int m_Index = 0;
    
    ///< Linked vertex buffers (possible to have more than one).
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    ///< Linked index buffer.
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&&) = delete;

    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;
};
