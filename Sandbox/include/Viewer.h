#pragma once

#include "Engine.h"
#include "ViewerLayer.h"

/**
 * Handles a 3D viewer application.
 *
 * The `Viewer` class is a derived class of the `Application` class, specifically designed for creating
 * a 3D viewer application. It inherits all the properties and functionality of the base `Application` class
 * and adds  a rendering layer, called `ViewerLayer`, which is responsible for rendering the 3D scene.
 *
 * Copying or moving `Viewer` objects is disabled to ensure single ownership and prevent unintended
 * duplication.
 */
class Viewer : public Application
{
public:
    // Constructor(s)/Destructor
    Viewer(const std::string &name = "Sandbox Renderer", const int width = 800,
                const int height = 600);
    ~Viewer();
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    Viewer(const Viewer&) = delete;
    Viewer(Viewer&&) = delete;
    // Operators
    Viewer& operator=(const Viewer&) = delete;
    Viewer& operator=(Viewer&&) = delete;
    
private:
    ///< 3D viewer (rendering layer).
    std::shared_ptr<ViewerLayer> m_ViewerLayer;
};
