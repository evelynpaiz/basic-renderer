#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

/**
 * Enumeration representing different types of primitives for rendering.
 */
enum class PrimitiveType
{
    Points,         ///< Points, each vertex represents a point.
    Lines,          ///< Lines, each pair of vertices forms a line segment.
    LineStrip,      ///< Line strip, consecutive vertices form connected lines.
    Triangles,      ///< Triangles, each group of three vertices forms a triangle.
    TriangleStrip   ///< Triangle strip, consecutive vertices form connected triangles.
};

/**
 * Enumeration representing face culling options.
 */
enum class FaceCulling
{
    Front, Back, FrontAndBack,
};

namespace utils { namespace OpenGL
{
/**
 * Convert a PrimitiveType value to the corresponding OpenGL primitive type.
 *
 * @param type The PrimitiveType value to be converted.
 * @return The corresponding OpenGL primitive type as a GLenum.
 */
inline GLenum PrimitiveTypeToOpenGLType(PrimitiveType type)
{
    switch (type)
    {
        case PrimitiveType::Points: return GL_POINTS;
        case PrimitiveType::Lines: return GL_LINES;
        case PrimitiveType::LineStrip: return GL_LINE_STRIP;
        case PrimitiveType::Triangles: return GL_TRIANGLES;
        case PrimitiveType::TriangleStrip: return GL_TRIANGLE_STRIP;
    }

    CORE_ASSERT(false, "Unknown primitive type!");
    return 0;
}

/**
 * Convert the face culling enumeration to its corresponding OpenGL type.
 *
 * @param culling The face culling mode to be converted.
 *
 * @return The corresponding OpenGL face culling mode.
 *
 * @note If the input face culling mode is not recognized, the function will assert with an error.
 */
inline GLenum CullingToOpenGLType(FaceCulling culling)
{
    switch (culling)
    {
        case FaceCulling::Front: return GL_FRONT;
        case FaceCulling::Back: return GL_BACK;
        case FaceCulling::FrontAndBack: return GL_FRONT_AND_BACK;
    }
    
    CORE_ASSERT(false, "Unknown face culling mode!");
    return 0;
}

} // namespace OpenGL
} // namespace utils
