#pragma once

#include "Event/Event.h"

struct GLFWwindow;

/**
 * Represents the information inside a window.
 */
struct WindowData
{
    ///< Window title.
    std::string Title;
    ///< Window size.
    unsigned int Width, Height;
    ///< Callback function to handle events.
    std::function<void(Event&)> EventCallback;
    
    // Constructor(s)/Destructor
    WindowData(const std::string& title, const int width, const int height);
    ~WindowData() = default;
};

/**
 * Defines a window that contains the running application.
 *
 * The `Window` class represents a window in the application. It provides methods to create, update,
 * and interact with the window. The event callback function can be set to handle window events.
 *
 * Copying or moving `Window` objects is disabled to ensure single ownership and prevent unintended
 * window duplication.
 */
class Window
{
public:
    // Constructor(s)/Destructor
    Window(const std::string& title, const int width, const int height);
    ~Window();
    // Update
    void OnUpdate() const;
    // Get(s)
    const std::string& GetTitle() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void* GetNativeWindow() const;
    // Set(s)
    void SetEventCallback(const std::function<void(Event&)>& callback);
    
private:
    // Init/Close
    void Init();
    void Shutdown();
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    // Operators
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    
private:
    ///< Native window (GLFW).
    GLFWwindow* m_Window;
    ///< Window information.
    WindowData m_Data;
};
