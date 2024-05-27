#include "Viewer/Simple.h"

#include "Common/Renderer/RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Define a layer for a 3D viewer.
 */
Simple::Simple(int width, int height)
    : Layer("Test Layer")
{}

/**
 * Attach (add) the viewer layer to the rendering engine.
 */
void Simple::OnAttach()
{}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Simple::OnUpdate(Timestep ts)
{
    // Reset rendering statistics
    Renderer::ResetStats();
    
    RendererCommand::Clear(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
}

/**
 * Handle an event that possibly occurred inside the viewer layer.
 * @param e Event.
 */
void Simple::OnEvent(Event &e)
{
    // Define the event dispatcher
    EventDispatcher dispatcher(e);
    
    // Dispatch the event to the application event callbacks
    dispatcher.Dispatch<WindowResizeEvent>(
        BIND_EVENT_FN(Simple::OnWindowResize));
}

/**
 * Function to be called when a window resize event happens.
 *
 * @param e Event to be handled.
 * @return True if the event has been handled.
 */
bool Simple::OnWindowResize(WindowResizeEvent &e)
{
    return true;
}
