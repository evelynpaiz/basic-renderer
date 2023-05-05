#include "enginepch.h"
#include "Core/LayerStack.h"

/**
 * Empty resources and delete the stack.
 */
LayerStack::~LayerStack()
{
    // Detach all layers in the stack
    for (std::shared_ptr<Layer> layer : m_Layers)
        layer->OnDetach();
}

/**
 * Add a rendering layer to the stack.
 * @param layer New rendering layer.
 */
void LayerStack::PushLayer(const std::shared_ptr<Layer>& layer)
{
    // Add the rendering layer above all layers in the stack
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
    m_LayerInsertIndex++;

    layer->OnAttach();
}

/**
 * Add an overlay layer (rendered on top) to the stack.
 * @param overlay New overlay layer.
 */
void LayerStack::PushOverlay(const std::shared_ptr<Layer>& overlay)
{
    // Add the overlay layer on top of all layers in the stack
    m_Layers.emplace_back(overlay);
    overlay->OnAttach();
}

/**
 * Remove a rendering layer from the stack.
 * @param layer Rendering layer.
 */
void LayerStack::PopLayer(const std::shared_ptr<Layer>& layer)
{
    // Check if the stack contains the rendering layer
    auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
    
    // If the layer exists, remove it
    if (it != m_Layers.begin() + m_LayerInsertIndex)
    {
        layer->OnDetach();
        m_Layers.erase(it);
        m_LayerInsertIndex--;
    }
}

/**
 * Remove an overlay (rendered on top) layer from the stack.
 * @param overlay Overlay layer.
 */
void LayerStack::PopOverlay(const std::shared_ptr<Layer>& overlay)
{
    // Check if the stack contains the overlay layer
    auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
    
    // If the layer exists, remove it
    if (it != m_Layers.end())
    {
        overlay->OnDetach();
        m_Layers.erase(it);
    }
}

/**
 * Get an iterator pointing to the bottom rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::iterator LayerStack::begin()
{
    return m_Layers.begin();
}

/**
 * Get an iterator pointing to the top rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::iterator LayerStack::end()
{
    return m_Layers.end();
}

/**
 * Get an iterator pointing to the top rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::reverse_iterator LayerStack::rbegin()
{
    return m_Layers.rbegin();
}

/**
 * Get an iterator pointing to the bottom rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::reverse_iterator LayerStack::rend()
{
    return m_Layers.rend();
}

/**
 * Get an iterator pointing to the bottom rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::const_iterator LayerStack::begin() const
{
    return m_Layers.begin();
}

/**
 * Get an iterator pointing to the top rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::const_iterator LayerStack::end() const
{
    return m_Layers.end();
}

/**
 * Get an iterator pointing to the top rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::const_reverse_iterator LayerStack::rbegin() const
{
    return m_Layers.rbegin();
}

/**
 * Get an iterator pointing to the bottom rendered layer.
 * @return An iterator of the layer stack.
 */
std::vector<std::shared_ptr<Layer>>::const_reverse_iterator LayerStack::rend() const
{
    return m_Layers.rend();
}
