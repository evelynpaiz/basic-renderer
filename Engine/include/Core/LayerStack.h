#pragma once

#include "Core/Layer.h"

/**
 * Manage a stack of layers in the rendering engine (stack wrapper).
 */
class LayerStack
{
public:
    // Constructor(s)/Destructor
    LayerStack() = default;
    ~LayerStack();
    // Stack management
    void PushLayer(const std::shared_ptr<Layer>& layer);
    void PushOverlay(const std::shared_ptr<Layer>& overlay);
    void PopLayer(const std::shared_ptr<Layer>& layer);
    void PopOverlay(const std::shared_ptr<Layer>& overlay);
    // Iterator
    std::vector<std::shared_ptr<Layer>>::iterator begin();
    std::vector<std::shared_ptr<Layer>>::iterator end();
    std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin();
    std::vector<std::shared_ptr<Layer>>::reverse_iterator rend();
    
    std::vector<std::shared_ptr<Layer>>::const_iterator begin() const;
    std::vector<std::shared_ptr<Layer>>::const_iterator end() const;
    std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rbegin() const;
    std::vector<std::shared_ptr<Layer>>::const_reverse_iterator rend() const;
    
private:
    ///< Set of layers in the stack
    std::vector<std::shared_ptr<Layer>> m_Layers;
    ///< Insert index (separating the overlays and rendering layers)
    unsigned int m_LayerInsertIndex = 0;
};
