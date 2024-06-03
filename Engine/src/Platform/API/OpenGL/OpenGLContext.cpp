#include "enginepch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 *  Constructs an OpenGL context for rendering.
 *
 *  @param windowHandle The GLFW window handle to associate with this context.
 */
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : GraphicsContext(), m_WindowHandle(windowHandle)
{
    CORE_ASSERT(windowHandle, "Window handle is null!");
}

/**
 *  Initializes the OpenGL context.
 *
 *  This function performs the following initialization steps:
 *  1. Makes the associated GLFW window's context current.
 *  2. Initializes the GLEW library for accessing OpenGL extensions.
 *  3. Prints the OpenGL version being used.
 */
void OpenGLContext::Init()
{
    // Make the window's context current
    glfwMakeContextCurrent(m_WindowHandle);

    // Initialize GLEW
    CORE_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW!");

    // Display the OpenGL general information
    CORE_INFO("Using OpenGL:");
    CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
}

/**
 *  Sets the window hints required for a OpenGL context.
 *
 *  This is a static function that should be called *before*
 *  creating the GLFW window to ensure a OpenGL-compatible
 *  context is created.
 */
void OpenGLContext::SetWindowHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

/**
 * Define if the window's buffer swap will be synchronized with the vertical
 * refresh rate of the monitor.
 *
 * @param enabled Enable or not the vertical synchronization.
 */
void OpenGLContext::SetVerticalSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

/**
 * Clear the buffers to preset values.
 * 
 * @param buffersActive State of the buffers.
 */
void OpenGLContext::Clear(const BufferState& buffersActive)
{
    // Clear buffers
    glClear(utils::OpenGL::BufferStateToOpenGLMask(buffersActive));
    
    // TODO: Activate depth testing if the depth buffer is active
    //SetDepthTesting(buffersActive.depthBufferActive);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 * @param buffersActive State of the buffers.
 */
void OpenGLContext::Clear(const glm::vec4& color, const BufferState& buffersActive)
{
    glClearColor(color.r, color.g, color.b, color.a);
    Clear(buffersActive);
}

/**
 *  Swaps the front and back buffers. This presents the rendered frame to the screen.
 */
void OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
