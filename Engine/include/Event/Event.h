#pragma once

/**
 * Enumeration of supported event types.
 *
 * The `EventType` enumeration  provides a set of values to represent different types of events that
 * can occur. It is used to categorize and handle events in event-driven systems. The supported event
 * types include window events, keyboard events and mouse events.
 */
enum class EventType
{
    None = 0,
    WindowResize, WindowClose,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
};

/**
 * Represents an event on the application.
 *
 * The `Event` class serves as a base class for all types of events that can occur in the application.
 * It provides common functionality and interfaces to access information about the events.
 */
class Event {
public:
    // Destructor
    virtual ~Event() = default;
    // Get(s)
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string GetDescription() const { return GetName(); }
    
public:
    // Status
    bool Handled = false;
    
// Do not allow its construction, if it is not done from a child definition.
protected:
    // Constructor(s)
    Event() = default;
    Event(const Event &) = default;
    Event(Event &&) = default;
    
    Event &operator=(const Event &) = default;
    Event &operator=(Event &&) = default;
};

/**
 * Represents a dispatcher (of events) inside the application.
 *
 * The `EventDispatcher` class provides a mechanism to dispatch events. It is responsible for verifying
 * the event type and invoking the appropriate callback function if the event matches.
 *
 * Copying or moving `EventDispatcher` objects is disabled to ensure single ownership and prevent
 * unintended duplication.
 */
class EventDispatcher {
public:
    // Constructor(s)/Destructor
    EventDispatcher(Event &event)  : m_Event(event) {}
    ~EventDispatcher() = default;
    // Dispatcher
    /**
     * Dispatch an event to the appropiate callback function.
     *
     * @tparam E Event type.
     
     * @param func Callback function to handle the event.
     *
     * @return `true` if the event was successfully dispatched and handled.
     */
    template <typename E>
    bool Dispatch(const std::function<bool(E&)> &func)
    {
        // Verify event type
        if (m_Event.GetEventType() == E::GetEventTypeStatic())
        {
            m_Event.Handled |= func(*(E*)&m_Event);
            return true;
        }
        
        // The event is not the same type
        return false;
    }
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    // Operators
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;
    
private:
    ///< Event (reference) to be dispatched.
    Event &m_Event;
};

/**
 * Operator that allows to log the event information.
 
 * @param os Output stream.
 * @param e Event to be described.
 */
inline std::ostream &operator<<(std::ostream &os, const Event &e)
{
    return os << e.GetDescription();
}
