#pragma once

#include "Engine.h"

#include <glm/glm.hpp>

/**
 * Rendering layer containing a basic 3D viewer.
 *
 * The `Viewer` class is a derived class of the `Layer` class and represents a rendering layer
 * specifically designed for a basic 3D viewer. It provides functionality for attaching, detaching, updating,
 * and handling events specific to the layer.
 *
 * Copying or moving `Viewer` objects is disabled to ensure single ownership and prevent
 * unintended layer duplication.
 */
class Viewer : public Layer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Viewer(int width, int height);
    
    // Layer handlers
    // ----------------------------------------
    void OnAttach() override;
    void OnUpdate(Timestep ts) override;
    void OnEvent(Event& e) override;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light source.
    /// @return The light source.
    const std::shared_ptr<Light>& GetLightSource() { return m_Environment->GetLightSource(); }
    
    // Setters(s)
    // ----------------------------------------
    /// @brief Set the interaction state inside this layer.
    /// @param e Enable/disable the interaction.
    void EnableInteraction(const bool e) { m_RenderContext->GetCamera()->Enable(e); }
    
private:
    // Initialization
    // ----------------------------------------
    void InitializeViewer();
    
    void DefineFramebuffers();
    void DefineMaterials();
    void DefineSceneGeometry();
    
    // Events handler(s)
    // ----------------------------------------
    bool OnWindowResize(WindowResizeEvent &e);
    
    // Viewer layer variables
    // ----------------------------------------
private:
    ///< Context of rendering.
    std::unique_ptr<RenderContext> m_RenderContext;
    
    ///< Environment along with its light source.
    std::shared_ptr<EnvironmentLight> m_Environment;
    
    ///< Model(s).
    Model<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>> m_Cube;
    Model<GeoVertexData<glm::vec4, glm::vec3>> m_Plane;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Viewer(const Viewer&) = delete;
    Viewer(Viewer&&) = delete;
    
    Viewer& operator=(const Viewer&) = delete;
    Viewer& operator=(Viewer&&) = delete;
};
