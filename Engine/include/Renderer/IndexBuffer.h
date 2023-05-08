#pragma once

/**
 * Represents an index buffer for rendering.
 *
 * The `IndexBuffer` class manages index buffers used to store indices that define the order in
 * which vertices are rendered, allowing for efficient reuse of shared vertices. It provides functions
 * for creation, binding, and management of index buffers.
 *
 * Copying or moving `IndexBuffer` objects is disabled to ensure single ownership and prevent
 * unintended buffer duplication.
 */
class IndexBuffer
{
public:
    // Constructor(s)/Destructor
    IndexBuffer(const unsigned int *indices, const unsigned int count);
    ~IndexBuffer();
    // Usage
    void Bind() const;
    void Unbind() const;
    // Gets
    unsigned int GetCount() const;
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;
    // Operators
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;
    
private:
    ///< ID of the index buffer.
    unsigned int m_ID = 0;
    ///< Number of indices (element count).
    unsigned int m_Count = 0;
};
