#pragma once

#include <GL/glew.h>

/**
 * Structure to represent the state of color, depth, and stencil buffers.
 */
struct BufferState
{
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a buffer state with predefined buffer activation states.
    /// @param color Whether the color buffer is active (default: true).
    /// @param depth Whether the depth buffer is active (default: false).
    /// @param stencil Whether the stencil buffer is active (default: false).
    BufferState(bool color = true, bool depth = false, bool stencil = false)
        : colorBufferActive(color), depthBufferActive(depth), stencilBufferActive(stencil)
    {}
    
    // Buffer state variables
    // ----------------------------------------
    bool colorBufferActive;     ///< Indicates whether the color buffer is active.
    bool depthBufferActive;     ///< Indicates whether the depth buffer is active.
    bool stencilBufferActive;   ///< Indicates whether the stencil buffer is active.
};

namespace utils { namespace OpenGL
{

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
} // namespace utils
