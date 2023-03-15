#pragma once

#include <vector>

/**
 * A structure to represent a vertex attribute (element).
 */
struct BufferElement
{
    /// Data type
    unsigned int type;
    /// Number of components per attribute
    unsigned int count;
    /// Specifies if the data should be normalized
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type);
};

/**
 * Description of a vertex attribute.
 */
class BufferLayout
{
public:
    /// Constructors/Destructor
    BufferLayout() = default;
    ~BufferLayout() = default;
    /// Gets
    unsigned int GetStride() const;
    const std::vector<BufferElement> GetElements() const;
    /// Push new layouts
    template<typename T>
    void Push(unsigned int count);
    template<>
    void Push<float>(unsigned int count);

private:
    /// Vertex buffer elements
    std::vector<BufferElement> m_Elements;
    /// Space between consecutive vertex attributes
    unsigned int m_Stride = 0;
};
