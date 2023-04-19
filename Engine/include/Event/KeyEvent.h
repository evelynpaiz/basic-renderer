#pragma once

#include "Event/Event.h"

/**
 * Abstraction that represents a keyboard event on the application.
 */
class KeyEvent : public Event
{
public:
    /// Gets
    int GetKeyCode() const;
    
protected:
    /// Constructor(s)
    KeyEvent(const int keyCode);
    
protected:
    /// Code of the key pressed/released
    int m_KeyCode;
};

/**
 * An event to represent the pressing of a key on the keyboard.
 */
class KeyPressedEvent : public KeyEvent
{
public:
    /// Constructor(s)
    KeyPressedEvent(const int keyCode, const unsigned int repeatCount);
    /// Gets
    unsigned int GetRepeatCount() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    /// Key pressed counter
    unsigned int m_RepeatCount;
};

/**
 * An event to represent the releasing of a key on the keyboard.
 */
class KeyReleasedEvent : public KeyEvent
{
public:
    /// Constructor(s)
    KeyReleasedEvent(const int keyCode);
    /// Gets
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};
