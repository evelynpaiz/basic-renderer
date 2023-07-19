#include "Viewer/Viewer.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Define a layer for a 3D viewer.
 */
Viewer::Viewer(int width, int height)
    : Layer("Viewer Layer"), m_ViewportWidth(width), m_ViewportHeight(height)
{}

/**
 * Attach (add) the viewer layer to the rendering engine.
 */
void Viewer::OnAttach()
{
    // Initialize all the elements of the viewer
    InitializeViewer();
    
    // Define a depth testing for the renderer
    Renderer::setDepthTest(true);
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Viewer::OnUpdate(float deltaTime)
{
    Renderer::BeginScene(m_Camera);

    // Render
    Renderer::Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
    
    m_Model.DrawModel();
    
    // Update the camera
    m_Camera->OnUpdate(deltaTime);
    
    Renderer::EndScene();
}

/**
 * Handle an event that possibly occurred inside the viewer layer.
 * @param e Event.
 */
void Viewer::OnEvent(Event &e)
{
    // Handle the events on the camera
    m_Camera->OnEvent(e);
}

/**
 * Initialize all components inside the viewer layer.
 */
void Viewer::InitializeViewer()
{
    // Define the texture(s)
    m_Texture = std::make_shared<Texture>("resources/models/backpack/diffuse.jpg", false);
    
    // Define the material to be used for shading
    m_Material = std::make_shared<BasicMaterial>();
    m_Material->SetColor(glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));
    m_Material->SetTexture(m_Texture);
    
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(m_ViewportWidth, m_ViewportHeight);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    
    // Define the model matrix for the geometry
    m_ModelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f),
                                glm::vec3(1.0f, 0.0f, 0.0f));
    
    // Define the data to be drawn (vertices and indices)
    std::vector<VertexData> vertices= {
        { {-0.5f, -0.5f, 0.0f, 1.0f}, {0.0f,  0.0f} },     // bottom left (0)
        { { 0.5f, -0.5f, 0.0f, 1.0f}, {1.0f,  0.0f} },     // bottom right (1)
        { { 0.5f,  0.5f, 0.0f, 1.0f}, {1.0f,  1.0f} },     // top right (2)
        { {-0.5f,  0.5f, 0.0f, 1.0f}, {0.0f,  1.0f} }      // top left (3)
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2,        // first triangle
        2, 3, 0         // second triangle
    };
    
    // Define how the data is defined
    BufferLayout layout = {
        { "a_Position", DataType::Vec4 },
        { "a_TextureCoord", DataType::Vec2 }
    };
    
    // Set the data into the mesh
    m_Mesh.DefineMesh(vertices, indices, layout);
    m_Mesh.SetMaterial(m_Material);
    
    // Load the model
    m_Model.LoadModel("resources/models/backpack/backpack.obj");
    m_Model.SetMaterial(m_Material);
    m_Model.SetScale(glm::vec3(0.75f));
}
