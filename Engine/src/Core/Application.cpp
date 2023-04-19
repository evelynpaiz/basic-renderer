#include "enginepch.h"
#include "Core/Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// Binding event function definition
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

/**
 * Generate a rendering application.
 *
 * @param name Application name.
 * @param width Size (width) of the application window.
 * @param height Size (height) of the application window.
 */
Application::Application(const std::string& name, const int width,
                         const int height)
{
    // Create the application window
    m_Window = std::make_unique<Window>(name, width, height);
    // Define the event callback function for the application
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

/**
 * Run this current application.
 */
void Application::Run()
{
    // Run until the user quits
    while (m_Running)
    {
        // Per-frame time logic
        float currentFrame = (float)glfwGetTime();
        float deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        
        /// TODO: remove it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Update the window
        m_Window->OnUpdate();
    }
}

/**
 * Callback function definition for event handling on the application.
 *
 * @param e Event to be handled.
 */
void Application::OnEvent(Event& e)
{
    // Define the event dispatcher
    EventDispatcher dispatcher(e);
    
    // Dispatch the event to the application event callbacks
    dispatcher.Dispatch<WindowResizeEvent>(
        BIND_EVENT_FN(Application::OnWindowResize));
    dispatcher.Dispatch<WindowCloseEvent>(
        BIND_EVENT_FN(Application::OnWindowClose));
    
    // Print the information of the event (DEGUB)
    // CORE_DEBUG("{0}", e);
}

/**
 * Function to be called when a window resize event happens.
 *
 * @param e Event to be handled.
 */
bool Application::OnWindowResize(WindowResizeEvent &e)
{
    return true;
}

/**
 * Function to be called when a window close event happens.
 *
 * @param e Event to be handled.
 */
bool Application::OnWindowClose(WindowCloseEvent &e)
{
    // Close the application
    m_Running = false;
    return true;
}
