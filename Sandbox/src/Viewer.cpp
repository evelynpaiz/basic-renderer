#include "Viewer.h"

/**
 * Generate a (sandbox) rendering application.
 */
Viewer::Viewer(const std::string &name, const int width, const int height)
    : Application(name, width, height)
{
    // Push the viewer layer to the layer stack
    m_ViewerLayer = std::make_shared<ViewerLayer>(width, height);
    PushLayer(m_ViewerLayer);
}

/**
 * Delete this application.
 */
Viewer::~Viewer()
{
    PopLayer(m_ViewerLayer);
}
