#pragma once

#include "Event/Event.h"

/**
 * Represents a window event on the application.
 *
 * The `WindowEvent` class is a base class for window events. It inherits from the `Event` class
 * and provides common functionality and attributes related to window events.
 */
class WindowEvent : public Event
{
public:
    // Get(s)
    const std::string& GetTitle() const;
    
protected:
    // Constructor(s)
    WindowEvent(const std::string& title);
    
protected:
    ///< Code of the key pressed.
    std::string m_Title;
};

/**
 * An event representing the resizing of the application window.
 *
 * The `WindowResizeEvent` class is derived from `WindowEvent` and represents the event
 * of the application window being resized. It provides additional functionality and attributes specific
 * to window resize events.
 */
class WindowResizeEvent : public WindowEvent
{
public:
    // Constructor(s)
    WindowResizeEvent(const std::string& title, unsigned int width,
                      unsigned int height);
    // Get(s)
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    ///< Size.
    unsigned int m_Width, m_Height;
};

/**
 * An event representing the closing of the application window.
 *
 * The `WindowCloseEvent` class is derived from `WindowEvent` and represents the event of
 * the application window being closed. It provides additional functionality and attributes specific
 * to window close events.
 */
class WindowCloseEvent : public WindowEvent {
public:
    // Constructor(s)
    WindowCloseEvent(const std::string& title);
    // Get(s)
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};
