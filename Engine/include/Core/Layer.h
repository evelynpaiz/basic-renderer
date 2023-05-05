#pragma once

#include "Event/Event.h"

/**
 * Layer in a rendering engine.
 */
class Layer
{
public:
    // Constructor(s)/ Destructor
    Layer(const std::string& name = "Unidentified Layer");
    virtual ~Layer() = default;
    // Layer handlers
    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnUpdate();
    virtual void OnEvent(Event& event);
    // Get(s)
    const std::string& GetName() const;
    
// Remove the possibility of copying this resource
public:
    // Copy
    Layer(const Layer&) = delete;
    Layer(Layer&&) = delete;
    // Operators
    Layer& operator=(const Layer&) = delete;
    Layer& operator=(Layer&&) = delete;
    
protected:
    ///< Layer name
    std::string m_LayerName;
};
