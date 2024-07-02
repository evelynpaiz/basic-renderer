#include "Viewer/ViewerApp.h"

/**
 * Generate a (sandbox) rendering application.
 *
 * @param name Name of the application.
 * @param width Size of the window (width).
 * @param height Size of the window (height).
 */
ViewerApp::ViewerApp(const std::string &name, const int width, const int height)
    : Application(name, width, height)
{
    // Push the viewer layer to the layer stack
    m_Viewer = std::make_shared<Simple>(GetWindow().GetWidth(), GetWindow().GetHeight());
    //m_Gui = std::make_shared<ViewerGui>(m_Viewer);
    
    PushLayer(m_Viewer);
    //PushOverlay(m_Gui);
}

/**
 * Delete this application.
 */
ViewerApp::~ViewerApp()
{
    PopLayer(m_Viewer);
    //PopOverlay(m_Gui);
}
