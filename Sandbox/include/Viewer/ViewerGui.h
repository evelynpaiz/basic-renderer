#pragma once

#include "Engine.h"

/**
 * Rendering layer responsible for the graphics interface using the ImGui library.
 *
 * The `ViewerGui` class is a derived class of the `GuiLayer` class and represents a graphical
 * user interface (GUI) to provide graphical support to a 3D viewer. It offers functionality for attaching,
 * detaching, updating, and handling events specific to the layer.
 *
 * Copying or moving `ViewerGui` objects is disabled to ensure single ownership and prevent
 * unintended layer duplication.
 */
class ViewerGui : public GuiLayer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    ViewerGui();
    
    // Layer handlers
    // ----------------------------------------
    void OnUpdate(float deltaTime) override;
    
private:
    // Setter(s)
    // ----------------------------------------
    void SetStyle() override;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    ViewerGui(const ViewerGui&) = delete;
    ViewerGui(ViewerGui&&) = delete;
    
    ViewerGui& operator=(const ViewerGui&) = delete;
    ViewerGui& operator=(ViewerGui&&) = delete;
};
