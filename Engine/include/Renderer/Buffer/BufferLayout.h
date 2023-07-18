#pragma once

#include <GL/glew.h>

/**
 * Enumeration of vertex attribute data types.
 *
 * The `DataType` enumeration represents different data types that can be used for vertex attributes.
 * It includes boolean, integer, floating-point, vectors (2D, 3D, 4D), and matrices (2x2, 3x3, 4x4) types.
 */
enum class DataType
{
    Bool, Int, Float,
    Vec2, Vec3, Vec4,
    Mat2, Mat3, Mat4
};

/**
 * Get the component count of a data type.
 *
 * @param type Data type.
 *
 * @return The number of components that the data has.
 */
inline unsigned int GetCompCountOfType(DataType type)
{
    switch (type)
    {
        case DataType::Bool: return 1;
        case DataType::Int: return 1;
        case DataType::Float: return 1;
        case DataType::Vec2: return 2;
        case DataType::Vec3: return 3;
        case DataType::Vec4: return 4;
        case DataType::Mat2: return 2;
        case DataType::Mat3: return 3;
        case DataType::Mat4: return 4;
    }

    CORE_ASSERT(false, "Unknown vertex data type!");
    return 0;
}

/**
 * Get the size (in bytes) of the data depending on its type.
 *
 * @param type Data type.
 *
 * @return The size of the data (in bytes).
 */
inline unsigned int GetSizeOfType(DataType type)
{
    switch (type)
    {
        case DataType::Bool: return 1;
        case DataType::Int: return 4;
        case DataType::Float: return 4;
        case DataType::Vec2: return 4 * 2;
        case DataType::Vec3: return 4 * 3;
        case DataType::Vec4: return 4 * 4;
        case DataType::Mat2: return 4 * 2 * 2;
        case DataType::Mat3: return 4 * 3 * 3;
        case DataType::Mat4: return 4 * 4 * 4;
    }
    
    CORE_ASSERT(false, "Unknown vertex data type!");
    return 0;
}

/**
 * Convert the data type to its corresponding OpenGL type.
 *
 * @param type Data type.
 *
 * @return OpenGL data type.
 */
inline GLenum DataTypeToOpenGLType(DataType type)
{
    switch (type)
    {
        case DataType::Bool: return GL_BOOL;
        case DataType::Int: return GL_INT;
        case DataType::Float: return GL_FLOAT;
        case DataType::Vec2: return GL_FLOAT;
        case DataType::Vec3: return GL_FLOAT;
        case DataType::Vec4: return GL_FLOAT;
        case DataType::Mat2: return GL_FLOAT;
        case DataType::Mat3: return GL_FLOAT;
        case DataType::Mat4: return GL_FLOAT;
    }

    CORE_ASSERT(false, "Unknown vertex data type!");
    return 0;
}

/**
 * Represents a vertex attribute (element).
 */
struct BufferElement
{
    // Buffer element variables
    // ----------------------------------------
    ///< Name of the element.
    std::string Name;
    ///< Data type.
    DataType Type;
    ///< Size (in bytes) of the element.
    unsigned int Size;
    ///< Offset value for the element.
    unsigned int Offset;
    ///< Specifies if the data should be normalized.
    bool Normalized;
    
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate an attribute (element) for a buffer.
    /// @param name Name of the element.
    /// @param type Data type of the element.
    /// @param normalized Normalize the data.
    BufferElement(const std::string& name, DataType type, bool normalized = false)
        : Name(name), Type(type), Size(GetSizeOfType(type)), Offset(0),
        Normalized(normalized)
    {}
    /// @brief Delete the buffer element.
    ~BufferElement() = default;
};

/**
 * Describes the layout of vertex attributes within a single vertex buffer.
 *
 * The `BufferLayout` class represents a collection of `BufferElements` that define the
 * arrangement and format of vertex attributes in a vertex buffer. It provides methods to retrieve
 * information about the elements in the layout.
 *
 * `BufferLayout` objects are typically used in conjunction with a `VertexBuffer` to define
 * the structure of vertex data stored in GPU memory.
 */
class BufferLayout
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    /// @brief Generate a layout for the buffer(s).
    BufferLayout() = default;
    /// @brief Generate a layout for the buffer(s).
    /// @param elements List of buffer elements to be set.
    BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_Elements(elements)
    {
        CalculateOffsetAndStride();
    }
    /// @brief Delete the defined layout.
    ~BufferLayout() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the space between consecutive vertex attributes.
    /// @return The stride value.
    unsigned int GetStride() const { return m_Stride; }
    /// @brief Get all the elements inside the vertex buffer layout.
    /// @return Buffer elements.
    const std::vector<BufferElement> GetElements() const
    {
        return m_Elements;
    }
    
    // Iteration support
    // ----------------------------------------
    /// @brief Get the first element  of the buffer.
    /// @return Iterator pointing to the first buffer element.
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    /// @brief Get the last element of the buffer.
    /// @return Iterator pointing to the last buffer element.
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    /// @brief Get the first element of the buffer (constant value).
    /// @return Iterator pointing to the first buffer element.
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    /// @brief Get the last element of the buffer (constant value).
    /// @return Iterator pointing to the last buffer element.
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
    
private:
    // Calculators
    // ----------------------------------------
    /// @brief  Calculate the offset (starting position of each vertex attribute) and the stride
    /// (space between consecutives vertex attributes) for the defined vertex attributes.
    void CalculateOffsetAndStride()
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

    // Buffer layout variables
    // ----------------------------------------
private:
    ///< Vertex buffer elements.
    std::vector<BufferElement> m_Elements;
    ///< Space between consecutive vertex attributes.
    unsigned int m_Stride = 0;
};
