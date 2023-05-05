#pragma once

#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"

/**
 * Rendering application handler.
 */
class Application
{
public:
    // Constructor(s)/ Destructor
    Application(const std::string &name = "Basic Renderer", const int width = 800,
                const int height = 600);
    virtual ~Application() = default;
    // Run
    void Run();
    void OnEvent(Event& e);
    // Rendering layers
    void PushLayer(const std::shared_ptr<Layer>& layer);
    void PushOverlay(const std::shared_ptr<Layer>& overlay);
    void PopLayer(const std::shared_ptr<Layer>& layer);
    void PopOverlay(const std::shared_ptr<Layer>& overlay);
    
private:
    // Events handlers
    bool OnWindowResize(WindowResizeEvent &e);
    bool OnWindowClose(WindowCloseEvent &e);
    
// Remove the possibility of copying this resource
public:
    // Copy
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    // Operators
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    
private:
    ///< Application window
    std::unique_ptr<Window> m_Window;
    ///< Application status
    bool m_Running = true;
    
    ///< Rendering time
    float m_LastFrame = 0.0f;
    
    ///< Layers to be rendered
    LayerStack m_LayerStack;
};
