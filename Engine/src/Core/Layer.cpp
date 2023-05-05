#include "enginepch.h"
#include "Core/Layer.h"

/**
 * Define a rendering layer.
 * @param name Name of the layer.
 */
Layer::Layer(const std::string &name)
    : m_LayerName(name)
{}

/**
 * Attach (add) this layer to the rendering engine.
 */
void Layer::OnAttach()
{}

/**
 * Detach (remove) this layer to the rendering engine.
 */
void Layer::OnDetach()
{}

/**
 * Render this layer.
 */
void Layer::OnUpdate(float deltaTime)
{}

/**
 * Handle an event possibly occurred inside the layer.
 * @param e Event.
 */
void Layer::OnEvent(Event &e)
{}

/**
 * Get the name of the layer.
 * @return Name of the layer.
 */
const std::string &Layer::GetName() const
{
    return m_LayerName;
}
