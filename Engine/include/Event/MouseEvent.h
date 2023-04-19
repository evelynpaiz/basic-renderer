#pragma once

#include "Event/Event.h"

/**
 * Abstraction that represents a mouse button event on the application.
 */
class MouseButtonEvent : public Event
{
public:
    /// Gets
    int GetMouseButton() const;
    
protected:
    /// Constructor(s)
    MouseButtonEvent(const int button);
    
protected:
    /// Code of the button pressed/released
    int m_Button;
};

/**
 * An event to represent the pressing of a button on the mouse.
 */
class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    /// Constructor(s)
    MouseButtonPressedEvent(const int button);
    /// Gets
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};

/**
 * An event to represent the releasing of a button on the mouse.
 */
class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    /// Constructor(s)
    MouseButtonReleasedEvent(const int button);
    /// Gets
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};

/**
 * An event to represent the scrolling on the mouse.
 */
class MouseScrolledEvent : public Event
{
public:
    /// Constructor(s)
    MouseScrolledEvent(const float xOffset, const float yOffset);
    /// Gets
    float GetXOffset() const;
    float GetYOffset() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    /// Scroll offsets
    float m_XOffset, m_YOffset;
};

/**
 * An event to represent the movement of the mouse.
 */
class MouseMovedEvent : public Event
{
public:
    /// Constructor(s)
    MouseMovedEvent(const float x, const float y);
    /// Gets
    float GetX() const;
    float GetY() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    /// Scroll offsets
    float m_X, m_Y;
};
