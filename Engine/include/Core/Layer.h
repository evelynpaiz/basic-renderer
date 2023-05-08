#pragma once

#include "Event/Event.h"

/**
 * Represents a layer in a rendering engine.
 *
 * The `Layer` class provides a mechanism for organizing and managing the rendering process in a
 * rendering engine. Layers can be attached and detached, allowing for dynamic management of rendering
 * order. They also provide an interface for updating the layer state and handling events specific to the layer.
 *
 * Copying or moving `Layer` objects is disabled to ensure single ownership and prevent unintended
 * layer duplication.
 */
class Layer
{
public:
    // Constructor(s)/Destructor
    Layer(const std::string& name = "Unidentified Layer");
    virtual ~Layer() = default;
    // Layer handlers
    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnUpdate(float deltaTime);
    virtual void OnEvent(Event& event);
    // Get(s)
    const std::string& GetName() const;
    
// Remove the possibility of copying or moving this resource
public:
    // Copy
    Layer(const Layer&) = delete;
    Layer(Layer&&) = delete;
    // Operators
    Layer& operator=(const Layer&) = delete;
    Layer& operator=(Layer&&) = delete;
    
protected:
    ///< Layer name.
    std::string m_LayerName;
};
