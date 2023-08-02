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
    
    m_Light.DrawMesh(m_LightMatrix);
    m_Cube.DrawMesh(m_CubeMatrix);
    
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
    m_CubeDiffuse = std::make_shared<Texture>("Resources/textures/diffuse.jpeg", false);
    m_CubeSpecular = std::make_shared<Texture>("Resources/textures/specular.jpeg", false);
    
    // Define the light type
    m_LightType = std::make_shared<PointLight>(glm::vec3(1.0f),
                                               glm::vec3(1.2f, 1.0f, 2.0f));
    
    // Define the material(s) to be used for shading
    m_CubeMaterial = std::make_shared<PhongTextureMaterial>();
    m_CubeMaterial->SetDiffuseMap(m_CubeDiffuse);
    m_CubeMaterial->SetSpecularMap(m_CubeSpecular);
    m_CubeMaterial->SetShininess(32.0f);
    
    m_CubeMaterial->SetLight(m_LightType);
    
    m_LightMaterial = std::make_shared<SimpleColorMaterial>();
    m_LightMaterial->SetColor(glm::vec4(m_LightType->GetColor(), 1.0f));
    
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(m_ViewportWidth, m_ViewportHeight);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    
    // Load the cube model
    std::vector<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>> cubeVertices;
    std::vector<unsigned int> cubeIndices;
    Geometry::DefineCubeGeometry(cubeVertices, cubeIndices);
    
    BufferLayout cubeLayout = {
        { "a_Position", DataType::Vec4 },
        { "a_TextureCoord", DataType::Vec2 },
        { "a_Normal", DataType::Vec3 }
    };
    
    m_Cube.DefineMesh(cubeVertices, cubeIndices, cubeLayout);
    m_Cube.SetMaterial(m_CubeMaterial);
    
    m_CubeMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
    
    // Define the light geometry
    std::vector<GeoVertexData<glm::vec4>> lightVertices;
    std::vector<unsigned int> lightIndices;
    Geometry::DefineCubeGeometry(lightVertices, lightIndices);
    
    BufferLayout lightLayout = {
        { "a_Position", DataType::Vec4 }
    };
    
    m_Light.DefineMesh(lightVertices, lightIndices, lightLayout);
    m_Light.SetMaterial(m_LightMaterial);
    
    m_LightMatrix = glm::translate(glm::mat4(1.0f), m_LightType->GetPosition());
}
