#include "Event/KeyEvent.h"

// --------------------------------------------
// Key Event
// --------------------------------------------

/**
 * Generate a keyboard event.
 *
 * @param keyCode Numerical value of the key.
 */
KeyEvent::KeyEvent(const int keyCode)
    : m_KeyCode(keyCode)
{}

/**
 * Get the numerical code of the key.
 *
 * @returns The key code.
 */
int KeyEvent::GetKeyCode() const
{
    return m_KeyCode;
}

// --------------------------------------------
// Key Pressed Event
// --------------------------------------------

/**
 * Generate a key pressed event.
 *
 * @param keyCode Numerical value of the key.
 * @param repeatCount Number of times the key has been pressed.
 */
KeyPressedEvent::KeyPressedEvent(const int keyCode, const unsigned int repeatCount)
    : KeyEvent(keyCode), m_RepeatCount(repeatCount)
{}

/**
 * Get the number of times the key has been pressed.
 *
 * @returns The key repeat count.
 */
unsigned int KeyPressedEvent::GetRepeatCount() const
{
    return m_RepeatCount;
}

/**
 * Get the type of the event.
 *
 * @returns KeyPressed type.
 */
EventType KeyPressedEvent::GetEventTypeStatic()
{
    return EventType::KeyPressed;
}

/**
 * Get the type of the event.
 *
 * @returns KeyPressed type.
 */
EventType KeyPressedEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns KeyPressedEvent name.
 */
const char* KeyPressedEvent::GetName() const
{
    return "KeyPressedEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (key pressed).
 */
std::string KeyPressedEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Key '" << m_KeyCode << "' pressed " << m_RepeatCount << " times";
    return ss.str();
}

// --------------------------------------------
// Key Released Event
// --------------------------------------------

/**
 * Generate a key released event.
 *
 * @param keyCode Numerical value of the key.
 */
KeyReleasedEvent::KeyReleasedEvent(const int keyCode)
    : KeyEvent(keyCode)
{}

/**
 * Get the type of the event.
 *
 * @returns KeyReleased type.
 */
EventType KeyReleasedEvent::GetEventTypeStatic()
{
    return EventType::KeyReleased;
}

/**
 * Get the type of the event.
 *
 * @returns KeyReleased type.
 */
EventType KeyReleasedEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns KeyReleasedEvent name.
 */
const char* KeyReleasedEvent::GetName() const
{
    return "KeyReleasedEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (key released).
 */
std::string KeyReleasedEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Key '" << m_KeyCode << "' released";
    return ss.str();
}
