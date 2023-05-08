#pragma once

#include "Event/Event.h"

/**
 * Represents a mouse button event on the application.
 *
 * The `MouseButtonEvent` class is a base class for mouse button events. It inherits from the
 * `Event` class and provides common functionality and attributes related to mouse button events.
 */
class MouseButtonEvent : public Event
{
public:
    // Get(s)
    int GetMouseButton() const;
    
protected:
    // Constructor(s)
    MouseButtonEvent(const int button);
    
protected:
    ///< Code of the button pressed/released.
    int m_Button;
};

/**
 * An event representing the pressing of a button on the mouse.
 *
 * The `MouseButtonPressedEvent` class is derived from `MouseButtonEvent` and represents
 * the event of a mouse button being pressed. It provides additional functionality and attributes specific
 * to mouse button pressed events.
 */
class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
    // Constructor(s)
    MouseButtonPressedEvent(const int button);
    // Gets
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};

/**
 * An event representing the releasing of a button on the mouse.
 *
 * The `MouseButtonReleasedEvent` class is derived from `MouseButtonEvent` and represents
 * the event of a mouse button being released. It provides additional functionality and attributes specific
 * to mouse button released events.
 */
class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
    // Constructor(s)
    MouseButtonReleasedEvent(const int button);
    // Get(s)
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};

/**
 * An event representing the scrolling of the mouse.
 *
 * The `MouseScrolledEvent` class is derived from `Event` and represents the event of the
 * mouse scrolling. It provides functionality and attributes specific to mouse scrolling events.
 */
class MouseScrolledEvent : public Event
{
public:
    // Constructor(s)
    MouseScrolledEvent(const float xOffset, const float yOffset);
    // Get(s)
    float GetXOffset() const;
    float GetYOffset() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    ///< Scroll offsets.
    float m_XOffset, m_YOffset;
};

/**
 * An event representing the movement of the mouse.
 *
 * The `MouseMovedEvent` class is derived from `Event` and represents the event of the
 * mouse moving. It provides functionality and attributes specific to mouse movement events.
 */
class MouseMovedEvent : public Event
{
public:
    // Constructor(s)
    MouseMovedEvent(const float x, const float y);
    // Get(s)
    float GetX() const;
    float GetY() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    ///< Mouse position.
    float m_X, m_Y;
};
