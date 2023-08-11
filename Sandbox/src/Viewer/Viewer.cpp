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
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Viewer::OnUpdate(float deltaTime)
{
    // Shadow mapping: light source
    //--------------------------------
    Renderer::BeginScene(m_LightSource->GetShadowCamera());
    Renderer::SetFaceCulling(FaceCulling::Front);
    
    Renderer::SetDepthBuffer(true);
    Renderer::SetColorBuffer(false);
    
    // Render into the lights framebuffer
    m_LightSource->GetFramebuffer()->Bind();
    
    Renderer::Clear();
    
    m_Cube.SetMaterial(m_ShadowMaterial);
    m_Cube.DrawModel();
    
    m_Plane.SetMaterial(m_ShadowMaterial);
    m_Plane.DrawModel();
    
    m_LightSource->GetFramebuffer()->Unbind();
    
    Renderer::SetFaceCulling(FaceCulling::Back);
    Renderer::EndScene();
    
    // First pass: scene
    //--------------------------------
    Renderer::BeginScene(m_Camera);
    Renderer::SetDepthBuffer(true);
    Renderer::SetColorBuffer(true);
    
    // Render into the framebuffer
    m_Framebuffer->Bind();
    
    Renderer::Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f));
    
    m_LightSource->GetModel().DrawModel();
    
    m_Cube.SetMaterial(m_CubeMaterial);
    m_Cube.DrawModel();
    m_Plane.SetMaterial(m_CubeMaterial);
    m_Plane.DrawModel();
    
    // Update the camera
    m_Camera->OnUpdate(deltaTime);
    
    m_Framebuffer->Unbind();
    Renderer::EndScene();
    
    // Second pass: scene
    //--------------------------------
    Renderer::BeginScene();
    Renderer::SetColorBuffer(true);
    Renderer::SetDepthBuffer(false);
    
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
    
    // Define the light source and its framebuffer for shadow mapping
    m_LightSource = std::make_shared<PointLight>(glm::vec3(1.0f), glm::vec3(2.0f, 2.5f, 6.0f));
    
    m_LightSource->SetShadowMap(true);
    m_LightSource->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    
    // Define the material(s) to be used for shading
    m_ShadowMaterial = std::make_shared<SimpleColorMaterial>("Resources/shaders/base/SimpleDepth.glsl");
    
    m_CubeMaterial = std::make_shared<PhongTextureMaterial>("Resources/shaders/phong/PhongTextureShadow.glsl");
    m_CubeMaterial->SetDiffuseMap(std::make_shared<Texture2D>("Resources/textures/diffuse.jpeg"));
    m_CubeMaterial->SetSpecularMap(std::make_shared<Texture2D>("Resources/textures/specular.jpeg"));
    m_CubeMaterial->SetShininess(32.0f);
    m_CubeMaterial->SetLight(m_LightSource);
    
    //m_ScreenMaterial = std::make_shared<SimpleTextureMaterial>("Resources/shaders/base/SimpleDepthTexture.glsl");
    //m_ScreenMaterial->SetTextureMap(m_LightSource->GetFramebuffer()->GetDepthAttachment());
    
    m_ScreenMaterial = std::make_shared<SimpleTextureMaterial>();
    m_ScreenMaterial->SetTextureMap(m_Framebuffer->GetColorAttachment(0));
    
    // Define the cube and plane model
    m_Cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>(m_CubeMaterial);
    m_Cube.SetScale(glm::vec3(2.0f));
    
    m_Plane = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>(m_CubeMaterial);
    m_Plane.SetPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    m_Plane.SetScale(glm::vec3(10.0f));
    m_Plane.SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
    
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
