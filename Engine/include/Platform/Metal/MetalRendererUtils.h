#pragma once

#include "Common/Renderer/RendererUtils.h"

#include <Metal/Metal.h>

namespace utils { namespace graphics { namespace mtl
{
/**
 * Convert the data type to its corresponding Metal format.
 *
 * @param dataType The type of data.
 *
 * @return Metal data format.
 *
 * @note If the input DataType value is not recognized, the function will assert with an error.
 */
inline MTLVertexFormat ToMetalFormat(DataType dataType)
{
    switch (dataType)
    {
        case DataType::Bool:  return MTLVertexFormatInt;
        case DataType::Int:   return MTLVertexFormatInt;
        case DataType::Float: return MTLVertexFormatFloat;
        case DataType::Vec2:  return MTLVertexFormatFloat2;
        case DataType::Vec3:  return MTLVertexFormatFloat3;
        case DataType::Vec4:  return MTLVertexFormatFloat4;
    }
    
    CORE_ASSERT(false, "Unknown vertex data type!");
    return MTLVertexFormatInvalid;
}

/**
 * Convert a primitive to the corresponding Metal primitive type.
 *
 * @param primitiveType The primitive value to be converted.
 * @return The corresponding Metal primitive type as a GLenum.
 */
inline MTLPrimitiveType ToMetalPrimitive(PrimitiveType primitiveType) 
{
    switch (primitiveType)
    {
        case PrimitiveType::Point:         return MTLPrimitiveTypePoint;
        case PrimitiveType::Line:          return MTLPrimitiveTypeLine;
        case PrimitiveType::LineStrip:     return MTLPrimitiveTypeLineStrip;
        case PrimitiveType::Triangle:      return MTLPrimitiveTypeTriangle;
        case PrimitiveType::TriangleStrip: return MTLPrimitiveTypeTriangleStrip;
    }

    CORE_ASSERT(false, "Unknown primitive type!");
    return MTLPrimitiveTypeTriangle;
}

} // namespace mtl
} // namespace graphics
} // namespace utils
