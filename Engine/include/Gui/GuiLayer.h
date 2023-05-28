#pragma once

#include "Core/Layer.h"

struct ImGuiContext;

class GuiLayer : public Layer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    GuiLayer();
    
    // Layer handlers
    // ----------------------------------------
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnEvent(Event& event) override;
    
    // GUI layer variables
    // ----------------------------------------
private:
    ///< GUI context (using ImGui)
    ImGuiContext *m_GuiContext = nullptr;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    GuiLayer(const GuiLayer&) = delete;
    GuiLayer(GuiLayer&&) = delete;
    
    GuiLayer& operator=(const GuiLayer&) = delete;
    GuiLayer& operator=(GuiLayer&&) = delete;
};
