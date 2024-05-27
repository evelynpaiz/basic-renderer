#pragma once

#include "Common/Renderer/GraphicsContext.h"

struct GLFWwindow;

/**
 *  Manages a Metal graphics context.
 *
 *  The `MetalContext` class is responsible for initializing, managing, and interacting
 *  with a Metal rendering context. It uses GLFW to interface with the windowing system
 *   and interacts with Metal for rendering on Apple platforms.
 */
class MetalContext : public GraphicsContext
{
public:
    // Constructor(s)
    // ----------------------------------------
    MetalContext(GLFWwindow* windowHandle);

    // Initialization
    // ----------------------------------------
    virtual void Init() override;
    
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
    
    ///< Holds the core Metal objects required for rendering.
    struct MetalState;
    std::shared_ptr<MetalState> m_State;
};
