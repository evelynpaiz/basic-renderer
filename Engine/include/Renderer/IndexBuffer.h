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
    // ----------------------------------------
    IndexBuffer(const unsigned int *indices, const unsigned int count);
    ~IndexBuffer();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void Unbind() const;
    
    // Getter(s)
    // ----------------------------------------
    /// Get the number of indices.
    /// @return The count of indices.
    unsigned int GetCount() const { return m_Count; }
    
    // Index buffer variables
    // ----------------------------------------
private:
    ///< ID of the index buffer.
    unsigned int m_ID = 0;
    ///< Number of indices (element count).
    unsigned int m_Count = 0;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&&) = delete;

    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&&) = delete;
};
