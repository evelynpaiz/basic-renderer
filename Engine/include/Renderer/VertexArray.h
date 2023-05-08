#pragma once

#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/BufferLayout.h"


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
    VertexArray();
    ~VertexArray();
    // Buffers
    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);
    // Usage
    void Bind() const;
    void Unbind() const;
    // Get(s)
    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const;
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const;
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&&) = delete;
    // Operators
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;
    
private:
    ///< ID of the vertex array.
    unsigned int m_ID = 0;
    ///< Vertex attribute index.
    unsigned int m_Index = 0;
    
    ///< Linked vertex buffers (possible to have more than one).
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    ///< Linked index buffer.
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};
