#include "Renderer/BufferLayout.h"

// --------------------------------------------
// Buffer element
// --------------------------------------------

/**
 * Generate an attribute (element) for a buffer.
 *
 * @param name Name of the element.
 * @param type Data type of the element.
 * @param normalized Normalize the data.
 */
BufferElement::BufferElement(const std::string& name,
    DataType type, bool normalized)
    : Name(name), Type(type), Size(GetSizeOfType(type)),
    Offset(0), Normalized(normalized)
{}

// --------------------------------------------
// Buffer layout
// --------------------------------------------

/**
 * Generate a layout for the buffer.
 *
 * @param elements List of buffer elements to be set.
 */
BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
    : m_Elements(elements)
{
    // Calculate the offset and stride of the input attributes
    CalculateOffsetAndStride();
}

/**
 * Get the space between consecutive vertex attributes.
 *
 * @returns The stride value.
 */
unsigned int BufferLayout::GetStride() const
{
    return m_Stride;
}

/**
 * Get all the elements inside the vertex buffer layout.
 *
 * @returns Buffer elements.
 */
const std::vector<BufferElement> BufferLayout::GetElements() const
{
    return m_Elements;
}

/**
 * Get the first element  of the buffer.
 *
 * @returns Iterator pointing to the first buffer element.
 */
std::vector<BufferElement>::iterator BufferLayout::begin()
{
    return m_Elements.begin();
}

/**
 * Get the last element of the buffer.
 *
 * @returns Iterator pointing to the last buffer element.
 */
std::vector<BufferElement>::iterator BufferLayout::end()
{
    return m_Elements.end();
}

/**
 * Get the first element of the buffer (constant value).
 *
 * @returns Iterator pointing to the first buffer element.
 */
std::vector<BufferElement>::const_iterator BufferLayout::begin() const
{
    return m_Elements.begin();
}

/**
 * Get the last element of the buffer (constant value).
 *
 * @returns Iterator pointing to the last buffer element.
 */
std::vector<BufferElement>::const_iterator BufferLayout::end() const
{
    return m_Elements.end();
}

/**
 * Calculate the offset (where the data beggins in the buffer) and the stride
 * (space between consecutives vertex attributes) for the defined vertex attributes.
 */
void BufferLayout::CalculateOffsetAndStride()
{
    unsigned int offset = 0;
    m_Stride = 0;
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}
