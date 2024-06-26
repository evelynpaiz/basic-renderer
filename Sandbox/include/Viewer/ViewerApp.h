#pragma once

#include "Engine.h"

#include "Viewer/Simple.h"
#include "Viewer/Viewer.h"
#include "Viewer/ViewerGui.h"

/**
 * Handles a 3D viewer application.
 *
 * The `ViewerApp` class is a derived class of the `Application` class, specifically designed for creating
 * a 3D viewer application. It inherits all the properties and functionality of the base `Application` class
 * and adds  a rendering layer, called `ViewerLayer`, which is responsible for rendering the 3D scene.
 *
 * Copying or moving `ViewerApp` objects is disabled to ensure single ownership and prevent unintended
 * duplication.
 */
class ViewerApp : public Application
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    ViewerApp(const std::string &name = "Viewer Application", const int width = 800,
                const int height = 600);
    ~ViewerApp();
    
    // Viewer application variables
    // ----------------------------------------
private:
    ///< 3D viewer (rendering layer).
    std::shared_ptr<Viewer> m_Viewer;
    std::shared_ptr<ViewerGui> m_Gui;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    ViewerApp(const ViewerApp&) = delete;
    ViewerApp(ViewerApp&&) = delete;

    ViewerApp& operator=(const ViewerApp&) = delete;
    ViewerApp& operator=(ViewerApp&&) = delete;
};
