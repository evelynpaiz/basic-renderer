#include "ViewerLayer.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Define a layer for a 3D viewer.
 */
ViewerLayer::ViewerLayer(int width, int height)
    : Layer("Viewer Layer"), m_ViewportWidth(width), m_ViewportHeight(height)
{}

/**
 * Attach (add) the viewer layer to the rendering engine.
 */
void ViewerLayer::OnAttach()
{
    // Initialize all the elements of the viewer
    InitializeViewer();
    
    // Define a depth testing for the renderer
    m_Renderer.setDepthTest(true);
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void ViewerLayer::OnUpdate(float deltaTime)
{
    // Render
    m_Shader->Bind();
    m_ViewMatrix = m_Camera->GetViewMatrix();
    m_ProjMatrix = m_Camera->GetProjectionMatrix();
    m_Shader->SetMat4("u_Transform", m_ProjMatrix * m_ViewMatrix * m_ModelMatrix);
    
    m_Renderer.Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
    m_Renderer.Draw(m_VertexArray, m_Shader);
    
    // Update the camera
    m_Camera->OnUpdate(deltaTime);
}

/**
 * Handle an event that possibly occurred inside the viewer layer.
 * @param e Event.
 */
void ViewerLayer::OnEvent(Event &e)
{
    // Print the information of the event (DEGUB)
    //CORE_DEBUG("{0}", e);
}

/**
 * Initialize all components inside the viewer layer.
 */
void ViewerLayer::InitializeViewer()
{
    // Define the layout of the data to be defined:
    // position : (x, y)
    // texture coords : (u, v)
    m_Layout = {
        { "a_Position", DataType::Vec2 },
        { "a_TextureCoord", DataType::Vec2 }
    };
    
    // Define the data to be drawn (vertices and indices)
    float vertices[] = {
        -0.5f, -0.5f,  0.0f,  0.0f,     // bottom left (0)
         0.5f, -0.5f,  1.0f,  0.0f,     // bottom right (1)
         0.5f,  0.5f,  1.0f,  1.0f,     // top right (2)
        -0.5f,  0.5f,  0.0f,  1.0f      // top left (3)
    };
    
    unsigned int indices[] = {
        0, 1, 2,        // first triangle
        2, 3, 0         // second triangle
    };
    
    // Generate a vertex array
    m_VertexArray = std::make_shared<VertexArray>();
    // Copy the vertex data in the vertex buffer
    m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    m_VertexBuffer->SetLayout(m_Layout);
    // Copy the index data in the index buffer
    m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(unsigned int));
    // Add the buffers information to the vertex array
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    
    // Build and compile the shader program to be used
    m_Shader = std::make_shared<Shader>("resources/shaders/basic.glsl");
    m_Shader->Bind();
    
    // Define the texture(s)
    m_Texture = std::make_shared<Texture>("resources/textures/container.jpg");
    
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(m_ViewportWidth, m_ViewportHeight);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    
    // Define the shader uniforms
    m_Shader->SetVec4("u_Color", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
    
    m_Texture->Bind(0);
    m_Shader->SetInt("u_Texture", 0);
    
    m_ModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f),
                                glm::vec3(1.0f, 0.0f, 0.0f));
    
    m_ViewMatrix = m_Camera->GetViewMatrix();
    m_ProjMatrix = m_Camera->GetProjectionMatrix();
    
    m_Shader->SetMat4("u_Transform", m_ProjMatrix * m_ViewMatrix * m_ModelMatrix);

    // Unbind the resources
    m_VertexArray->Unbind();
    m_VertexBuffer->Unbind();
    m_IndexBuffer->Unbind();
    m_Shader->Unbind();
}
