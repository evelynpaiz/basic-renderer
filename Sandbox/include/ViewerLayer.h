#pragma once

#include "Engine.h"

#include <glm/glm.hpp>

/**
 * Rendering layer containg a basic 3D viewer.
 */
class ViewerLayer : public Layer
{
public:
    // Constructor(s)/ Destructor
    ViewerLayer(int width, int height);
    ~ViewerLayer() = default;
    // Layer handlers
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(float deltaTime) override;
    void OnEvent(Event& event) override;
    
private:
    void InitializeViewer();
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    ViewerLayer(const ViewerLayer&) = delete;
    ViewerLayer(ViewerLayer&&) = delete;
    /// Operators
    ViewerLayer& operator=(const ViewerLayer&) = delete;
    ViewerLayer& operator=(ViewerLayer&&) = delete;
    
private:
    ///< Size of the viewport
    int m_ViewportWidth = 0;
    int m_ViewportHeight = 0;
    
    ///< Renderer
    Renderer m_Renderer;
    ///< Camera
    std::shared_ptr<PerspectiveCamera> m_Camera;
    
    ///< Vertex array
    std::shared_ptr<VertexArray> m_VertexArray;
    ///< Vertex buffer
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    ///< Index buffer
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    
    ///< Layout of the data
    BufferLayout m_Layout;
    
    ///< Shader
    std::shared_ptr<Shader> m_Shader;
    
    ///< Texture
    std::shared_ptr<Texture> m_Texture;
    
    ///< Transformation matrices
    glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    glm::mat4 m_ProjMatrix = glm::mat4(1.0f);
};
