#pragma once

#include "Event/Event.h"

/**
 * Abstraction that represents a window event on the application.
 */
class WindowEvent : public Event
{
public:
    /// Gets
    const std::string& GetTitle() const;
    
protected:
    /// Constructor(s)
    WindowEvent(const std::string& title);
    
protected:
    /// Code of the key pressed
    std::string m_Title;
};

/**
 * An event to represent the resizing of the application window.
 */
class WindowResizeEvent : public WindowEvent
{
public:
    /// Constructor(s)
    WindowResizeEvent(const std::string& title, unsigned int width,
                      unsigned int height);
    /// Gets
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    /// Size
    unsigned int m_Width, m_Height;
};

/**
 * An event to represent the closing of the application window.
 */
class WindowCloseEvent : public WindowEvent {
public:
    /// Constructor(s)
    WindowCloseEvent(const std::string& title);
    /// Gets
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};
