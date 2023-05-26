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
    // ----------------------------------------
    /// @brief Delete the event.
    virtual ~Event() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the type of the event.
    /// @return An `EventType`.
    virtual EventType GetEventType() const = 0;
    /// @brief Get the name of the event.
    /// @return The event name.
    virtual const char* GetName() const = 0;
    /// @brief Get the description of the event.
    /// @return The event description.
    virtual std::string GetDescription() const { return GetName(); }
    
    // Event variables
    // ----------------------------------------
public:
    ///< Status of the event.
    bool Handled = false;
    
    // Disable its construction, if it is not done from a child
    // ----------------------------------------
protected:
    Event() = default;
    Event(const Event &) = default;
    Event(Event &&) = default;
    
    Event &operator=(const Event &) = default;
    Event &operator=(Event &&) = default;
};

/**
 * Macro to override the definition of the event types inside a child event class.
 *
 * @param type The name of the event type to be defined.
 */
#define EVENT_CLASS_TYPE(type)\
    static EventType GetEventTypeStatic() { return EventType::type; }\
    virtual EventType GetEventType() const override { return GetEventTypeStatic(); }\
    virtual const char* GetName() const override { return #type; }

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
    // ----------------------------------------
    /// @brief Generate a dispatcher for the event.
    EventDispatcher(Event &event)  : m_Event(event) {}
    /// @brief Delete the event dispatcher.
    ~EventDispatcher() = default;
    
    // Dispatcher
    // ----------------------------------------
    /// @brief Dispatch an event to the appropiate callback function.
    /// @tparam E Event type.
    /// @param func Callback function to handle the event.
    /// @return `true` if the event was successfully dispatched and handled.
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
    
    // Event dispatcher variables
    // ----------------------------------------
private:
    ///< Event (reference) to be dispatched.
    Event &m_Event;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;

    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;
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
