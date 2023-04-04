#pragma once

#include <string>

struct GLFWwindow;

/**
 * A representation of the information inside a window.
 */
struct WindowData
{
    /// Window title
    std::string Title;
    /// Window size
    unsigned int Width, Height;
    
    /// Constructor(s)/ Destructor
    WindowData(const std::string& title, const int width, const int height);
    ~WindowData() = default;
};

/**
 * Defines the display containing the running application.
 */
class Window
{
public:
    /// Constructor(s)/ Destructor
    Window(const std::string& title, const int width, const int height);
    ~Window();
    /// Update
    void OnUpdate() const;
    /// Gets
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    void* GetNativeWindow() const;
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    /// Operators
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    
private:
    /// Init/Close
    void Init();
    void Shutdown();
    
private:
    /// Native window (GLFW)
    GLFWwindow* m_Window;
    /// Window information
    WindowData m_Data;
};
