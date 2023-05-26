#include "ViewerApp.h"

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
    m_ViewerLayer = std::make_shared<ViewerLayer>(width, height);
    PushLayer(m_ViewerLayer);
}

/**
 * Delete this application.
 */
ViewerApp::~ViewerApp()
{
    PopLayer(m_ViewerLayer);
}
