#include "Core/Window.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/Log.h"
#include "Core/Assert.h"

// Variable initialization
// --------------------------------------------
/// Window counter for GLFW.
static unsigned int g_WindowCount = 0;

// --------------------------------------------

/**
 * Generate a window.
 */
Window::Window(const std::string& title, const int width, const int height)
    : m_Title(title), m_Width(width), m_Height(height)
{
    Init();
}

/**
 * Delete the window.
 */
Window::~Window()
{
    Shutdown();
}

/**
 * Update the window.
 */
void Window::OnUpdate() const
{
    // Swap front and back buffers
    glfwSwapBuffers(m_Window);
    
    // Poll for and process events
    glfwPollEvents();
}

/**
 * Get the size (width) of the window.
 *
 * @returns the width of the window.
 */
unsigned int Window::GetWidth() const
{
    return m_Width;
}

/**
 * Get the size (height) of the window.
 *
 * @returns the height of the window.
 */
unsigned int Window::GetHeight() const
{
    return m_Height;
}

/**
 * Get the GLFW window.
 *
 * @returns the native window.
 */
void* Window::GetNativeWindow() const
{
    return m_Window;
}

/**
 * Initialize the window with all its corresponding components.
 */
void Window::Init()
{
    // Check if GLFW is already initialized, if not initialize it
    if (g_WindowCount == 0)
    {
        CORE_TRACE("Initializing GLFW");
        CORE_ASSERT(glfwInit(), "Failed to initialize GLFW!");
    }
    
    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // Create a windowed mode window and its OpenGL context
    CORE_INFO("Creating {0} window ({1} x {2})", m_Title, m_Width, m_Height);
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
    CORE_ASSERT(m_Window, "Failed to create a GLFW window!");
    
    // Make the window's context current
    glfwMakeContextCurrent(m_Window);
    ++g_WindowCount;
    
    // Initialize GLEW
    CORE_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW!");
    
    // Display the version of OpenGL
    CORE_INFO("Using OpenGL version {0}",
              (const char*)glGetString(GL_VERSION));
}

/**
 * Shutdown and close the window.
 */
void Window::Shutdown()
{
    // Close the window
    glfwDestroyWindow(m_Window);
    g_WindowCount -= 1;
    
    // Check if is the only window available, if so, terminate GLFW too
    if (g_WindowCount == 0)
    {
        CORE_TRACE("Terminating GLFW");
        glfwTerminate();
    }
}
