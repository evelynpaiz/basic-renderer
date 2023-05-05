#pragma once

#include "Engine.h"
#include "ViewerLayer.h"

/**
 * Sandbox application handler.
 */
class Sandbox : public Application
{
public:
    /// Constructor(s)/ Destructor
    Sandbox(const std::string &name = "Sandbox Renderer", const int width = 800,
                const int height = 600);
    ~Sandbox();
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Sandbox(const Sandbox&) = delete;
    Sandbox(Sandbox&&) = delete;
    /// Operators
    Sandbox& operator=(const Sandbox&) = delete;
    Sandbox& operator=(Sandbox&&) = delete;
    
private:
    std::shared_ptr<ViewerLayer> m_ViewerLayer;
};
