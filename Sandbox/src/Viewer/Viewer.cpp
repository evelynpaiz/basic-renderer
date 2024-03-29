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
void Viewer::OnUpdate(Timestep ts)
{
    // Reset rendering statistics
    Renderer::ResetStats();
    
    // Shadow mapping: light source
    //--------------------------------
    Renderer::BeginScene(m_Environment->GetLightSource()->GetShadowCamera());
    Renderer::SetFaceCulling(FaceCulling::Front);
    
    // Render into the lights framebuffer
    m_Framebuffers["Shadow"]->Bind();
    
    Renderer::Clear(m_Framebuffers["Shadow"]->GetActiveBuffers());
    
    m_Cube.SetMaterial(m_Materials["Depth"]);
    m_Cube.DrawModel();
    
    m_Plane.SetMaterial(m_Materials["Depth"]);
    m_Plane.DrawModel();
    
    m_Framebuffers["Shadow"]->Unbind();
    
    Renderer::SetFaceCulling(FaceCulling::Back);
    Renderer::EndScene();
    
    // First pass: scene
    //--------------------------------
    Renderer::BeginScene(m_Camera);
    
    // Render into the framebuffer
    m_Framebuffers["Viewport"]->Bind();
    
    Renderer::Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f), m_Framebuffers["Viewport"]->GetActiveBuffers());
    
    m_Cube.SetMaterial(m_Materials["PhongTexture"]);
    m_Cube.DrawModel();
    m_Plane.SetMaterial(m_Materials["PhongColor"]);
    m_Plane.DrawModel();
    
    // Update the camera
    m_Camera->OnUpdate(ts);
    
    m_Framebuffers["Viewport"]->Unbind();
    Renderer::EndScene();
    
    // Second pass: scene
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
    // Define the environment and its light source
    auto light = std::make_shared<DirectionalLight>(m_ViewportWidth, m_ViewportHeight,
                                                    glm::vec3(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
    
    m_Environment = std::make_shared<EnvironmentLight>(m_ViewportWidth, m_ViewportHeight);
    m_Environment->SetLightSource(light);
    
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(m_ViewportWidth, m_ViewportHeight);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    
    // Define the framebuffer(s)
    FrameBufferSpecification framebufferSpec;
    framebufferSpec.SetFrameBufferSize(m_ViewportWidth, m_ViewportHeight);
    
    framebufferSpec.AttachmentsSpec = {
        TextureFormat::DEPTH24
    };
    m_Framebuffers["Shadow"] = std::make_shared<FrameBuffer>(framebufferSpec);
    
    framebufferSpec.AttachmentsSpec = {
        TextureFormat::RGB8,
        TextureFormat::DEPTH24
    };
    m_Framebuffers["Viewport"] = std::make_shared<FrameBuffer>(framebufferSpec);
    
    // Define the material(s) to be used for shading
    auto depthMaterial = std::make_shared<Material>("Resources/shaders/depth/DepthMap.glsl");
    m_Materials["Depth"] = depthMaterial;
    
    auto cubeMaterial = std::make_shared<PhongTextureMaterial>(m_Environment, "Resources/shaders/phong/PhongTextureShadow.glsl");
    cubeMaterial->SetDiffuseMap(std::make_shared<Texture2DResource>("Resources/textures/diffuse.jpg"));
    cubeMaterial->SetSpecularMap(std::make_shared<Texture2DResource>("Resources/textures/specular.jpg"));
    cubeMaterial->SetShadowMap(m_Framebuffers["Shadow"]->GetDepthAttachment());
    cubeMaterial->SetShininess(32.0f);
    m_Materials["PhongTexture"] = cubeMaterial;
    
    auto planeMaterial = std::make_shared<PhongColorMaterial>(m_Environment, "Resources/shaders/phong/PhongColorShadow.glsl");
    planeMaterial->SetAmbientColor(glm::vec3(0.8f, 0.2f, 0.4f));
    planeMaterial->SetDiffuseColor(glm::vec3(0.8f, 0.2f, 0.4f));
    planeMaterial->SetSpecularColor(glm::vec3(1.0f));
    planeMaterial->SetShadowMap(m_Framebuffers["Shadow"]->GetDepthAttachment());
    planeMaterial->SetShininess(100.0f);
    m_Materials["PhongColor"] = planeMaterial;
    
    auto viewportMaterial = std::make_shared<SimpleTextureMaterial>();
    viewportMaterial->SetTextureMap(m_Framebuffers["Viewport"]->GetColorAttachment(0));
    m_Materials["Viewport"] = viewportMaterial;
    
    // Define the cube and plane model
    m_Cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>(cubeMaterial);
    m_Cube.SetScale(glm::vec3(2.0f));
    
    m_Plane = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec3>>(planeMaterial);
    m_Plane.SetPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    m_Plane.SetScale(glm::vec3(10.0f));
    m_Plane.SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
    
    // Define the screen model
    m_Screen = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec2>>(m_Materials["Viewport"]);
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
    m_Framebuffers["Viewport"]->Resize(e.GetWidth(), e.GetHeight());
    m_Framebuffers["Shadow"]->Resize(e.GetWidth(), e.GetHeight());
    return true;
}
