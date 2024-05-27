#pragma once

#include "Engine.h"

#include <glm/glm.hpp>

class Simple : public Layer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Simple(int width, int height);
    
    // Layer handlers
    // ----------------------------------------
    void OnAttach() override;
    void OnUpdate(Timestep ts) override;
    void OnEvent(Event& e) override;
    
private:
    // Events handler(s)
    // ----------------------------------------
    bool OnWindowResize(WindowResizeEvent &e);
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Simple(const Simple&) = delete;
    Simple(Simple&&) = delete;
    
    Simple& operator=(const Simple&) = delete;
    Simple& operator=(Simple&&) = delete;
};
