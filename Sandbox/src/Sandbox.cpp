#include "Sandbox.h"

/**
 * Generate a (sandbox) rendering application.
 */
Sandbox::Sandbox(const std::string &name, const int width, const int height)
    : Application(name, width, height)
{
    // Push the viewer layer to the layer stack
    m_ViewerLayer = std::make_shared<ViewerLayer>(width, height);
    PushLayer(m_ViewerLayer);
}

/**
 * Delete this application.
 */
Sandbox::~Sandbox()
{
    PopLayer(m_ViewerLayer);
}
