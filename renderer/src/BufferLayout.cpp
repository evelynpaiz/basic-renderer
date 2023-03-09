#include "BufferLayout.h"

#include <iostream>

#include <GL/glew.h>

// --------------------------------------------
// Buffer element
// --------------------------------------------

/**
 * Get the size (in bytes) of the data depending on its type.
 *
 * @returns The stride value.
 */
unsigned int BufferElement::GetSizeOfType(unsigned int type)
{
    switch (type) {
        case GL_FLOAT: return 4;
    }
    
    std::cout << "Unknown vertex data type!" << std::endl;
    return 0;
}

// --------------------------------------------
// Buffer layout
// --------------------------------------------

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
 * Push and define a vertex attribute.
 *
 * @tparam T Data type to be pushed.
 */
template<typename T>
void BufferLayout::Push(unsigned int count)
{
    static_assert(Push<T>, "this function has to be implemented for desired type");
}

/**
 * Push and define a vertex attribute for floats.
 */
template<>
void BufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * BufferElement::GetSizeOfType(GL_FLOAT);
}
