#include "Event/MouseEvent.h"

// --------------------------------------------
// Mouse Button Event
// --------------------------------------------

/**
 * Generate a mouse button event.
 *
 * @param button Numerical value of the button.
 */
MouseButtonEvent::MouseButtonEvent(const int button)
    : m_Button(button)
{}

/**
 * Get the numerical code of the mouse button.
 *
 * @returns The mouse code.
 */
int MouseButtonEvent::GetMouseButton() const
{
    return m_Button;
}

// --------------------------------------------
// Mouse Button Pressed Event
// --------------------------------------------

/**
 * Generate a mouse button pressed event.
 *
 * @param button Numerical value of the button.
 */
MouseButtonPressedEvent::MouseButtonPressedEvent(const int button)
    : MouseButtonEvent(button)
{}

/**
 * Get the type of the event.
 *
 * @returns MouseButtonPressed type.
 */
EventType MouseButtonPressedEvent::GetEventTypeStatic()
{
    return EventType::MouseButtonPressed;
}

/**
 * Get the type of the event.
 *
 * @returns MouseButtonPressed type.
 */
EventType MouseButtonPressedEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns MouseButtonPressedEvent name.
 */
const char* MouseButtonPressedEvent::GetName() const
{
    return "MouseButtonPressedEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (mouse button pressed).
 */
std::string MouseButtonPressedEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Mouse button '" << m_Button << "' pressed";
    return ss.str();
}

// --------------------------------------------
// Mouse Button Released Event
// --------------------------------------------

/**
 * Generate a mouse button released event.
 *
 * @param button Numerical value of the button.
 */
MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button)
    : MouseButtonEvent(button)
{}

/**
 * Get the type of the event.
 *
 * @returns MouseButtonReleased type.
 */
EventType MouseButtonReleasedEvent::GetEventTypeStatic()
{
    return EventType::MouseButtonReleased;
}

/**
 * Get the type of the event.
 *
 * @returns MouseButtonReleased type.
 */
EventType MouseButtonReleasedEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns MouseButtonReleasedEvent name.
 */
const char* MouseButtonReleasedEvent::GetName() const
{
    return "MouseButtonReleasedEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (mouse button released).
 */
std::string MouseButtonReleasedEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Mouse button '" << m_Button << "' released";
    return ss.str();
}

// --------------------------------------------
// Mouse Scrolled Event
// --------------------------------------------

/**
 * Generate a mouse scrolled event.
 *
 * @param xOffset The scroll offset in the x-axis (horizontally).
 * @param yOffset The scroll offset in the y-axis (vertically).
 */
MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset)
    : m_XOffset(xOffset), m_YOffset(yOffset)
{}

/**
 * Get the scroll offset.
 *
 * @returns The offset in the x-axis.
 */
float MouseScrolledEvent::GetXOffset() const
{
    return m_XOffset;
}

/**
 * Get the scroll offset.
 *
 * @returns The offset in the y-axis.
 */
float MouseScrolledEvent::GetYOffset() const
{
    return m_YOffset;
}

/**
 * Get the type of the event.
 *
 * @returns MouseScrolled type.
 */
EventType MouseScrolledEvent::GetEventTypeStatic()
{
    return EventType::MouseScrolled;
}

/**
 * Get the type of the event.
 *
 * @returns MouseScrolled type.
 */
EventType MouseScrolledEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns MouseScrolledEvent name.
 */
const char* MouseScrolledEvent::GetName() const
{
    return "MouseScrolledEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (mouse scrolled).
 */
std::string MouseScrolledEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Mouse scrolled (" << m_XOffset << " , " << m_YOffset << ")";
    return ss.str();
}

// --------------------------------------------
// Mouse Moved Event
// --------------------------------------------

/**
 * Generate a mouse moved event.
 *
 * @param x The mouse position in the x-axis.
 * @param y The mouse position in the y-axis.
 */
MouseMovedEvent::MouseMovedEvent(const float x, const float y)
    : m_X(x), m_Y(y)
{}

/**
 * Get the mouse position.
 *
 * @returns The mouse position in the x-axis.
 */
float MouseMovedEvent::GetX() const
{
    return m_X;
}

/**
 * Get the mouse position.
 *
 * @returns The mouse position in the y-axis.
 */
float MouseMovedEvent::GetY() const
{
    return m_Y;
}

/**
 * Get the type of the event.
 *
 * @returns MouseMoved type.
 */
EventType MouseMovedEvent::GetEventTypeStatic()
{
    return EventType::MouseMoved;
}

/**
 * Get the type of the event.
 *
 * @returns MouseMoved type.
 */
EventType MouseMovedEvent::GetEventType() const
{
    return GetEventTypeStatic();
}

/**
 * Get the name of the event.
 *
 * @returns MouseMovedEvent name.
 */
const char* MouseMovedEvent::GetName() const
{
    return "MouseMovedEvent";
}

/**
 * Get the description of the event.
 *
 * @returns Event description (mouse moved).
 */
std::string MouseMovedEvent::GetDescription() const
{
    std::stringstream ss;
    ss << "Mouse moved (" << m_X << " , " << m_Y << ")";
    return ss.str();
}
