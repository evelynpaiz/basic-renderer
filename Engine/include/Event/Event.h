#pragma once

/**
 * An enumeration for describing the different event types that are supported.
 */
enum class EventType
{
    None = 0,
    WindowResize, WindowClose,
    KeyPressed, KeyReleased,
    MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
};

/**
 * Abstraction that represents an event on the application.
 */
class Event {
public:
    /// Destructor
    virtual ~Event() = default;
    /// Gets
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual std::string GetDescription() const { return GetName(); }
    
public:
    /// Status
    bool Handled = false;
    
// Do not allow its construction, if it is not done from a child definition.
protected:
    Event() = default;
    Event(const Event &) = default;
    Event(Event &&) = default;
    
    Event &operator=(const Event &) = default;
    Event &operator=(Event &&) = default;
};

/**
 * Abstraction of a dispatcher (of events) inside the application.
 */
class EventDispatcher {
public:
    /// Constructor(s)/ Destructor
    EventDispatcher(Event &event)  : m_Event(event) {}
    ~EventDispatcher() = default;
    /// Dispatcher
    /**
     * Dispatch an event generated in the application.
     *
     * @tparam E Event type.
     
     * @param func Callback function.
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
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher(EventDispatcher&&) = delete;
    /// Operators
    EventDispatcher& operator=(const EventDispatcher&) = delete;
    EventDispatcher& operator=(EventDispatcher&&) = delete;
    
private:
    /// Event (reference) to be dispatched
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
