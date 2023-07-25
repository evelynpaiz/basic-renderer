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
    
private:
    // Initialization
    // ----------------------------------------
    void InitializeViewer();
    
    // Viewer layer variables
    // ----------------------------------------
private:
    ///< Size of the viewport.
    int m_ViewportWidth = 0;
    int m_ViewportHeight = 0;
    
    ///< Rendering camera.
    std::shared_ptr<PerspectiveCamera> m_Camera;
    
    ///< Loaded model.
    Mesh<GeoVertexData<glm::vec4, glm::vec3>> m_Cube;
    ///< Model material.
    std::shared_ptr<PhongColorMaterial> m_CubeMaterial;
    ///< Model texture.
    std::shared_ptr<Texture> m_CubeTexture;
    ///< Model transformation matrix.
    glm::mat4 m_CubeMatrix = glm::mat4(1.0f);
    
    ///< Light geometry.
    Mesh<GeoVertexData<glm::vec4>> m_Light;
    ///< Light material.
    std::shared_ptr<SimpleColorMaterial> m_LightMaterial;
    ///< Light type.
    std::shared_ptr<PointLight> m_LightType;
    ///< Light transformation matrix.
    glm::mat4 m_LightMatrix = glm::mat4(1.0f);
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Viewer(const Viewer&) = delete;
    Viewer(Viewer&&) = delete;
    
    Viewer& operator=(const Viewer&) = delete;
    Viewer& operator=(Viewer&&) = delete;
};
