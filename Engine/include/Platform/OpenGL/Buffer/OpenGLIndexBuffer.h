#pragma once

#include "Common/Renderer/Buffer/IndexBuffer.h"

/**
 * Concrete implementation of `IndexBuffer` for the OpenGL rendering API.
 *
 * The `OpenGLIndexBuffer` handles the creation, binding, and management of index buffers
 * specifically for OpenGL. It uses OpenGL functions to interact with the GPU.
 *
 * Copying or moving `OpenGLIndexBuffer` objects is disabled to ensure single ownership
 * and prevent unintended buffer duplication.
 */
class OpenGLIndexBuffer : public IndexBuffer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    OpenGLIndexBuffer(const uint32_t *indices, const uint32_t count);
    virtual ~OpenGLIndexBuffer();
    
    // Usage
    // ----------------------------------------
    void Bind() const override;
    void Unbind() const override;
    
    // Index buffer variables
    // ----------------------------------------
private:
    ///< ID of the index buffer.
    uint32_t m_ID = 0;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    OpenGLIndexBuffer(const OpenGLIndexBuffer&) = delete;
    OpenGLIndexBuffer(OpenGLIndexBuffer&&) = delete;

    OpenGLIndexBuffer& operator=(const OpenGLIndexBuffer&) = delete;
    OpenGLIndexBuffer& operator=(OpenGLIndexBuffer&&) = delete;
};