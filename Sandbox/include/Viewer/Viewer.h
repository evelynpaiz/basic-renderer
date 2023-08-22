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
    void OnUpdate(float deltaTime) override;
    void OnEvent(Event& e) override;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light source.
    /// @return The light source.
    const std::shared_ptr<PointLight>& GetLightSource() { return m_LightSource; }
    
    // Setters(s)
    // ----------------------------------------
    /// @brief Set the interaction state inside this layer.
    /// @param e Enable/disable the interaction.
    void EnableInteraction(const bool e) { m_Camera->Enable(e); }
    
private:
    // Initialization
    // ----------------------------------------
    void InitializeViewer();
    
    // Events handler(s)
    // ----------------------------------------
    bool OnWindowResize(WindowResizeEvent &e);
    
    // Viewer layer variables
    // ----------------------------------------
private:
    ///< Size of the viewport.
    int m_ViewportWidth = 0;
    int m_ViewportHeight = 0;
    
    ///< Framebufer(s).
    std::shared_ptr<FrameBuffer> m_Framebuffer;
    
    ///< Camera.
    std::shared_ptr<PerspectiveCamera> m_Camera;
    
    ///< Light source.
    std::shared_ptr<PointLight> m_LightSource;
    
    ///< Model(s).
    Model<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>> m_Cube;
    Model<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>> m_Plane;
    Model<GeoVertexData<glm::vec4, glm::vec2>> m_Screen;
    
    ///< Material(s).
    std::shared_ptr<Material> m_DepthMaterial;
    std::shared_ptr<PhongTextureMaterial> m_CubeMaterial;
    std::shared_ptr<SimpleTextureMaterial> m_ScreenMaterial;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Viewer(const Viewer&) = delete;
    Viewer(Viewer&&) = delete;
    
    Viewer& operator=(const Viewer&) = delete;
    Viewer& operator=(Viewer&&) = delete;
};
