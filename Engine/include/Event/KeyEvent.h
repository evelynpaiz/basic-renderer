#pragma once

#include "Event/Event.h"

/**
 * Represents a keyboard event on the application.
 *
 * The `KeyEvent` class is a base class for keyboard events. It inherits from the `Event` class
 * and provides common functionality and attributes related to keyboard events.
 */
class KeyEvent : public Event
{
public:
    // Get(s)
    int GetKeyCode() const;
    
protected:
    // Constructor(s)
    KeyEvent(const int keyCode);
    
protected:
    ///< Code of the key pressed/released.
    int m_KeyCode;
};

/**
 * An event representing the pressing of a key on the keyboard.
 *
 * The `KeyPressedEvent` class is derived from `KeyEvent` and represents the event of a key being
 * pressed on the keyboard. It provides additional functionality and attributes specific to key pressed events.
 */
class KeyPressedEvent : public KeyEvent
{
public:
    // Constructor(s)
    KeyPressedEvent(const int keyCode, const unsigned int repeatCount);
    // Get(s)
    unsigned int GetRepeatCount() const;
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
    
private:
    ///< Key pressed counter.
    unsigned int m_RepeatCount;
};

/**
 * An event representing the releasing of a key on the keyboard.
 *
 * The `KeyReleasedEvent` class is derived from `KeyEvent` and represents the event of a key
 * being released on the keyboard. It provides additional functionality and attributes specific to key
 * released events.
 */
class KeyReleasedEvent : public KeyEvent
{
public:
    // Constructor(s)
    KeyReleasedEvent(const int keyCode);
    // Get(s)
    static EventType GetEventTypeStatic();
    EventType GetEventType() const override;
    const char* GetName() const override;
    std::string GetDescription() const override;
};
