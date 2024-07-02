#pragma once

#include <GL/glew.h>

namespace utils { namespace data { namespace OpenGL
{
/**
 * Convert the data type to its corresponding OpenGL type.
 *
 * @param type Data type.
 *
 * @return OpenGL data type.
 *
 * @note If the input DataType value is not recognized, the function will assert with an error.
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
 * Convert the buffers state to its corresponding OpenGL mask.
 *
 * @param buffersActive State of the buffers.
 *
 * @return Bitwise OR of masks that indicate the buffers to be cleared.
 */
inline GLbitfield BufferStateToOpenGLMask(const BufferState& buffersActive)
{
    GLbitfield mask = 0;
    if (buffersActive.colorBufferActive)
        mask |= GL_COLOR_BUFFER_BIT;
    if (buffersActive.depthBufferActive)
        mask |= GL_DEPTH_BUFFER_BIT;
    if (buffersActive.stencilBufferActive)
        mask |= GL_STENCIL_BUFFER_BIT;
    
    return mask;
}

} // namespace OpenGL
} // namespace data
} // namespace utils
