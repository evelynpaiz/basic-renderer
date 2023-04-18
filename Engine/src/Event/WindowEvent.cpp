#include "Event/WindowEvent.h"

// --------------------------------------------
// Window Event
// --------------------------------------------

/**
 * Generate a window event.
 *
 * @param title The window title.
 */
WindowEvent::WindowEvent(const std::string& title)
    : m_Title(title)
{}

/**
 * Get the title of the window.
 *
 * @returns The window name.
 */
const std::string& WindowEvent::GetTitle() const
{
    return m_Title;
}

// --------------------------------------------
// Window Resize Event
// --------------------------------------------

/**
 * Generate a window resize event.
 *
 * @param title The window title.
 * @param width Updated window size (width).
 * @param height Updated window size (height).
 */
WindowResizeEvent::WindowResizeEvent(const std::string& title, unsigned int width,
                                     unsigned int height)
    : WindowEvent(title), m_Width(width), m_Height(height)
{}

/**
 * Get the resize event size.
 *
 * @returns The updated size (width).
 */
unsigned int WindowResizeEvent::GetWidth() const
{
    return m_Width;
}
/**
 * Get the resize event size.
 *
 * @returns The updated size (height).
 */
unsigned int WindowResizeEvent::GetHeight() const
{
    return m_Height;
}

/**
 * Get the type of the event.
 *
 * @returns WindowResize type.
 */
EventType WindowResizeEvent::GetEventTypeStatic()
{
    return EventType::WindowResize;
}

/**
 * Get the type of the event.
 *
 * @returns WindowResize type.
 */
EventType WindowResizeEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns WindowResizeEvent name.
 */
const char* WindowResizeEvent::GetName() const
{
    return "WindowResizeEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (updated size).
 */
std::string WindowResizeEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Window '" << m_Title << "' resized: " << m_Width << " x " << m_Height;
    return ss.str();
}

// --------------------------------------------
// Window Close Event
// --------------------------------------------

/**
 * Generate a window close event.
 *
 * @param title The window title.
 */
WindowCloseEvent::WindowCloseEvent(const std::string& title)
    : WindowEvent(title)
{}

/**
 * Get the type of the event.
 *
 * @returns WindowClose type.
 */
EventType WindowCloseEvent::GetEventTypeStatic()
{
    return EventType::WindowClose;
}

/**
 * Get the type of the event.
 *
 * @returns WindowClose type.
 */
EventType WindowCloseEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns WindowResizeEvent name.
 */
const char* WindowCloseEvent::GetName() const
{
    return "WindowCloseEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (closed window).
 */
std::string WindowCloseEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Window '" << m_Title << "' closed";
    return ss.str();
}
