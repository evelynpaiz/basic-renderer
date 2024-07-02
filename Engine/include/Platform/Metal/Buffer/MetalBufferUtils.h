#pragma once

#include <Metal/Metal.h>

namespace utils { namespace data { namespace Metal
{
/**
 * Convert the data type to its corresponding Metal format.
 *
 * @param type Data type.
 *
 * @return Metal data format.
 *
 * @note If the input DataType value is not recognized, the function will assert with an error.
 */
inline MTLVertexFormat DataTypeToMetalFormat(DataType type)
{
    switch (type)
    {
        case DataType::Bool:  return MTLVertexFormatInt;
        case DataType::Int:   return MTLVertexFormatInt;
        case DataType::Float: return MTLVertexFormatFloat;
        case DataType::Vec2: return MTLVertexFormatFloat2;
        case DataType::Vec3: return MTLVertexFormatFloat3;
        case DataType::Vec4: return MTLVertexFormatFloat4;
    }
    
    CORE_ASSERT(false, "Unknown vertex data type!");
    return MTLVertexFormatInvalid;
}
} // namespace Metal
} // namespace data
} // namespace utils
