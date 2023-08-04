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
    Renderer::SetDepthTest(true);
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Viewer::OnUpdate(float deltaTime)
{
    // Update the light position
    m_Light.SetPosition(m_LightSource->GetPosition());
    
    // First pass
    //--------------------------------
    Renderer::BeginScene(m_Camera);
    
    // Render into the framebuffer
    m_Framebuffer->Bind();
    
    Renderer::Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
    m_Light.DrawModel();
    m_Cube.DrawModel();
    
    // Update the camera
    m_Camera->OnUpdate(deltaTime);
    m_Framebuffer->Unbind();
    Renderer::EndScene();
    
    // Second pass
    //--------------------------------
    Renderer::BeginScene();
    // Render to the screen
    Renderer::Clear(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    m_Screen.DrawModel();
    Renderer::EndScene();
}

/**
 * Handle an event that possibly occurred inside the viewer layer.
 * @param e Event.
 */
void Viewer::OnEvent(Event &e)
{
    // Define the event dispatcher
    EventDispatcher dispatcher(e);
    
    // Dispatch the event to the application event callbacks
    dispatcher.Dispatch<WindowResizeEvent>(
        BIND_EVENT_FN(Viewer::OnWindowResize));
    
    // Handle the events on the camera
    m_Camera->OnEvent(e);
}

/**
 * Initialize all components inside the viewer layer.
 */
void Viewer::InitializeViewer()
{
    // Define the output framebuffer
    FrameBufferSpecification framebufferSpec(m_ViewportWidth, m_ViewportHeight);
    framebufferSpec.AttachmentsSpec = {
        TextureFormat::RGB8,
        TextureFormat::DEPTH24
    };
    m_Framebuffer = std::make_shared<FrameBuffer>(framebufferSpec);
    
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(m_ViewportWidth, m_ViewportHeight);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    
    // Define the light type
    m_LightSource = std::make_shared<PointLight>(glm::vec3(1.0f),
                                               glm::vec3(1.2f, 1.0f, 2.0f));
    
    // Define the material(s) to be used for shading
    m_CubeMaterial = std::make_shared<PhongTextureMaterial>();
    m_CubeMaterial->SetDiffuseMap(std::make_shared<Texture2D>("Resources/textures/diffuse.jpeg"));
    m_CubeMaterial->SetSpecularMap(std::make_shared<Texture2D>("Resources/textures/specular.jpeg"));
    m_CubeMaterial->SetShininess(32.0f);
    m_CubeMaterial->SetLight(m_LightSource);
    
    m_LightMaterial = std::make_shared<SimpleColorMaterial>();
    m_LightMaterial->SetColor(glm::vec4(m_LightSource->GetColor(), 1.0f));
    
    m_ScreenMaterial = std::make_shared<SimpleTextureMaterial>();
    m_ScreenMaterial->SetTextureMap(m_Framebuffer->GetColorAttachment(0));
    
    // Define the cube model
    m_Cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>(m_CubeMaterial);
    m_Cube.SetScale(glm::vec3(2.0f));
    
    // Define the light model
    m_Light = utils::Geometry::ModelCube<GeoVertexData<glm::vec4>>(m_LightMaterial);
    m_Light.SetPosition(m_LightSource->GetPosition());
    
    // Define the screen model
    m_Screen = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec2>>(m_ScreenMaterial);
    m_Screen.SetScale(glm::vec3(2.0f));
}

/**
 * Function to be called when a window resize event happens.
 *
 * @param e Event to be handled.
 * @return True if the event has been handled.
 */
bool Viewer::OnWindowResize(WindowResizeEvent &e)
{
    // Update the viewport size
    m_ViewportWidth = e.GetWidth();
    m_ViewportHeight = e.GetHeight();
    
    // Update the camera size
    m_Camera->SetViewportSize(e.GetWidth(), e.GetHeight());
    
    // Update the screen and the framebuffer
    m_ScreenMaterial->SetTextureMap(nullptr);
    m_Framebuffer->Resize(e.GetWidth(), e.GetHeight());
    m_ScreenMaterial->SetTextureMap(m_Framebuffer->GetColorAttachment(0));
    return true;
}
