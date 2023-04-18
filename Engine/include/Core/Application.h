#pragma once

#include "Core/Window.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"

/**
 * Rendering application handler.
 */
class Application
{
public:
    /// Constructor(s)/ Destructor
    Application(const std::string &name = "Basic Renderer", const int width = 800,
                const int height = 600);
    virtual ~Application() = default;
    /// Run
    void Run();
    void OnEvent(Event& e);
    
private:
    /// Events handlers
    bool OnWindowResize(WindowResizeEvent &e);
    bool OnWindowClose(WindowCloseEvent &e);
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    /// Operators
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    
private:
    /// Application window
    std::unique_ptr<Window> m_Window;
    /// Application status
    bool m_Running = true;
    /// Rendering time
    float m_LastFrame = 0.0f;
};
