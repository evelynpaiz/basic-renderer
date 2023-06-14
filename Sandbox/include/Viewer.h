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
    
    ///< Renderer.
    Renderer m_Renderer;
    ///< Camera.
    std::shared_ptr<PerspectiveCamera> m_Camera;
    
    ///< Vertex array.
    std::shared_ptr<VertexArray> m_VertexArray;
    ///< Vertex buffer.
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    ///< Index buffer.
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    
    ///< Layout of the data.
    BufferLayout m_Layout;
    
    ///< Shader.
    std::shared_ptr<Shader> m_Shader;
    
    ///< Texture.
    std::shared_ptr<Texture> m_Texture;
    
    ///< Transformation matrices.
    glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    glm::mat4 m_ProjMatrix = glm::mat4(1.0f);
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Viewer(const Viewer&) = delete;
    Viewer(Viewer&&) = delete;
    
    Viewer& operator=(const Viewer&) = delete;
    Viewer& operator=(Viewer&&) = delete;
};
