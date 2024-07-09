#pragma once

#include "Common/Renderer/RendererUtils.h"

#include <GL/glew.h>

namespace utils { namespace graphics { namespace gl
{
/**
 * Convert the data type to its corresponding OpenGL type.
 *
 * @param dataType The type of data.
 *
 * @return OpenGL data type.
 *
 * @note If the input DataType value is not recognized, the function will assert with an error.
 */
inline GLenum ToOpenGLType(DataType dataType)
{
    switch (dataType)
    {
        case DataType::Bool:  return GL_BOOL;
        case DataType::Int:   return GL_INT;
        case DataType::Float: return GL_FLOAT;
        case DataType::Vec2:  return GL_FLOAT;
        case DataType::Vec3:  return GL_FLOAT;
        case DataType::Vec4:  return GL_FLOAT;
    }
    
    CORE_ASSERT(false, "Unknown vertex data type!");
    return 0;
}

/**
 * Convert the buffers state to its corresponding OpenGL clear mask.
 *
 * @param buffersActive State of the buffers.
 *
 * @return Bitwise OR of masks that indicate the buffers to be cleared.
 */
inline GLbitfield ToClearMask(const BufferState& bufferState) {
    GLbitfield mask = 0;
    if (bufferState.colorBufferActive) {
        mask |= GL_COLOR_BUFFER_BIT;
    }
    if (bufferState.depthBufferActive) {
        mask |= GL_DEPTH_BUFFER_BIT;
    }
    if (bufferState.stencilBufferActive) {
        mask |= GL_STENCIL_BUFFER_BIT;
    }
    return mask;
}

/**
 * Convert a primitive to the corresponding OpenGL primitive type.
 *
 * @param primitiveType The primitive value to be converted.
 * @return The corresponding OpenGL primitive type as a GLenum.
 */
inline GLenum ToOpenGLPrimitive(PrimitiveType primitiveType)
{
    switch (primitiveType)
    {
        case PrimitiveType::Point:         return GL_POINTS;
        case PrimitiveType::Line:          return GL_LINES;
        case PrimitiveType::LineStrip:     return GL_LINE_STRIP;
        case PrimitiveType::Triangle:      return GL_TRIANGLES;
        case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
    }
    
    CORE_ASSERT(false, "Unknown primitive type!");
    return 0;
}

/**
 * Convert the face culling mode to its corresponding OpenGL mode.
 *
 * @param culling The face culling mode to be converted.
 *
 * @return The corresponding OpenGL face culling mode.
 *
 * @note If the input face culling mode is not recognized, the function will assert with an error.
 */
inline GLenum ToOpenGLCulling(FaceCulling culling)
{
    switch (culling)
    {
        case FaceCulling::Front:        return GL_FRONT;
        case FaceCulling::Back:         return GL_BACK;
        case FaceCulling::FrontAndBack: return GL_FRONT_AND_BACK;
    }
    
    CORE_ASSERT(false, "Unknown face culling mode!");
    return 0;
}

/**
 * Convert the depth function to its corresponding OpenGL function.
 *
 * @param depth The depth function mode to be converted.
 *
 * @return The corresponding OpenGL depth function.
 *
 * @note If the input depth function is not recognized, the function will assert with an error.
 */
inline GLenum ToOpenGLDepthFunc(DepthFunction depth)
{
    switch (depth)
    {
        case DepthFunction::Always:   return GL_ALWAYS;
        case DepthFunction::Never:    return GL_NEVER;
        case DepthFunction::Less:     return GL_LESS;
        case DepthFunction::Equal:    return GL_EQUAL;
        case DepthFunction::LEqual:   return GL_LEQUAL;
        case DepthFunction::Greater:  return GL_GREATER;
        case DepthFunction::NotEqual: return GL_NOTEQUAL;
        case DepthFunction::GEqual:   return GL_GEQUAL;
    }
    
    CORE_ASSERT(false, "Unknown depth function!");
    return 0;
}

} // namespace gl
} // namespace graphics
} // namespace utils
