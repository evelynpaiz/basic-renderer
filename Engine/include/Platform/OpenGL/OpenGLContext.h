#pragma once

#include "Common/Renderer/GraphicsContext.h"

struct GLFWwindow;

/**
 *  Manages an OpenGL graphics context.
 *
 *  The `OpenGLContext` class is responsible for initializing, managing, and interacting
 *  with an OpenGL rendering context. It uses GLFW to interface with the windowing system.
 */
class OpenGLContext : public GraphicsContext
{
public:
    // Constructor(s)
    // ----------------------------------------
    OpenGLContext(GLFWwindow* windowHandle);

    // Initialization
    // ----------------------------------------
    void Init() override;
    
    // Setter(s)
    // ----------------------------------------
    static void SetWindowHints();
    void SetVerticalSync(bool enabled) override;
    
    // Buffers
    // ----------------------------------------
    void SwapBuffers() override;
    
    // Clear
    // ----------------------------------------
    void Clear(const BufferState& buffersActive = {}) override;
    void Clear(const glm::vec4& color, const BufferState& buffersActive = {}) override;
    
    // Graphics context variables
    // ----------------------------------------
private:
    ///< Native window (GLFW).
    GLFWwindow* m_WindowHandle;
};
