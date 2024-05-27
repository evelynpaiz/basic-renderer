#pragma once

#include "Common/Renderer/RendererAPI.h"

/**
 * Concrete implementation of the RendererAPI interface for OpenGL.
 *
 * The `OpenGLRendererAPI` class implements the `RendererAPI` abstract methods
 * specifically for the OpenGL rendering API.
 */
class OpenGLRendererAPI : public RendererAPI
{
public:
    // Initialization
    // ----------------------------------------
    void Init() override;
};
