#include "Viewer/Viewer.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Define a layer for a 3D viewer.
 */
Viewer::Viewer(int width, int height)
    : Layer("Viewer Layer"), m_RenderContext(std::make_unique<RenderContext>(width, height))
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
    auto shadowFramebuffer = m_RenderContext->GetFramebuffer("Shadow");
    shadowFramebuffer->Bind();
    Renderer::Clear(shadowFramebuffer->GetActiveBuffers());
    
    auto depthMaterial = m_RenderContext->GetMaterial("Depth");
    m_Cube.SetMaterial(depthMaterial);
    m_Cube.DrawModel();
    m_Plane.SetMaterial(depthMaterial);
    m_Plane.DrawModel();
    
    shadowFramebuffer->Unbind();
    
    Renderer::SetFaceCulling(FaceCulling::Back);
    Renderer::EndScene();
    
    // First pass: scene
    //--------------------------------
    Renderer::BeginScene(m_RenderContext->GetCamera());
    
    // Render into the framebuffer
    auto viewportFramebuffer = m_RenderContext->GetViewport()->GetFramebuffer();
    viewportFramebuffer->Bind();
    
    Renderer::Clear(glm::vec4(0.93f, 0.93f, 0.93f, 1.0f), viewportFramebuffer->GetActiveBuffers());
    
    m_Cube.SetMaterial(m_RenderContext->GetMaterial("PhongTexture"));
    m_Cube.DrawModel();
    m_Plane.SetMaterial(m_RenderContext->GetMaterial("PhongColor"));
    m_Plane.DrawModel();
    
    // Update the camera
    m_RenderContext->GetCamera()->OnUpdate(ts);
    
    viewportFramebuffer->Unbind();
    Renderer::EndScene();
    
    // Second pass: scene
    //--------------------------------
    m_RenderContext->RenderToScreen();
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
    m_RenderContext->GetCamera()->OnEvent(e);
}

/**
 * Initialize all components inside the viewer layer.
 */
void Viewer::InitializeViewer()
{
    int viewportWidth = m_RenderContext->GetViewport()->GetWidth();
    int viewportHeight = m_RenderContext->GetViewport()->GetHeight();
    
    // Define the environment and its light source
    auto light = std::make_shared<DirectionalLight>(viewportWidth, viewportHeight,
                                                    glm::vec3(1.0f), glm::vec3(0.5f, -0.5f, 0.0f));
    
    m_Environment = std::make_shared<EnvironmentLight>(viewportWidth, viewportHeight);
    m_Environment->SetLightSource(light);
    
    // Update the position of the rendering camera
    m_RenderContext->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
    
    // Define the framebuffer(s) to render into
    DefineFramebuffers();
    
    // Define the material(s) to be used for shading
    DefineMaterials();
    
    // Define the geometry in the scene
    DefineSceneGeometry();
}

/**
 * Defines the framebuffers used in the rendering process.
 */
void Viewer::DefineFramebuffers()
{
    int viewportWidth = m_RenderContext->GetViewport()->GetWidth();
    int viewportHeight = m_RenderContext->GetViewport()->GetHeight();
    
    FrameBufferSpecification shadowSpec;
    shadowSpec.SetFrameBufferSize(viewportWidth, viewportHeight);
    shadowSpec.AttachmentsSpec = { TextureFormat::DEPTH24 };
    m_RenderContext->CreateFrameBuffer("Shadow", shadowSpec);
}

/**
 * Defines the materials used in the rendering process.
 */
void Viewer::DefineMaterials()
{
    auto depthMaterial = m_RenderContext->CreateMaterial<Material>("Depth", "Resources/shaders/depth/DepthMap.glsl");
    
    auto cubeMaterial = m_RenderContext->CreateMaterial<PhongTextureMaterial>("PhongTexture", m_Environment,
        "Resources/shaders/phong/PhongTextureShadow.glsl");
    cubeMaterial->SetDiffuseMap(std::make_shared<Texture2DResource>("Resources/textures/diffuse.jpeg"));
    cubeMaterial->SetSpecularMap(std::make_shared<Texture2DResource>("Resources/textures/specular.jpeg"));
    cubeMaterial->SetShadowMap(m_RenderContext->GetFramebuffer("Shadow")->GetDepthAttachment());
    cubeMaterial->SetShininess(32.0f);
    
    auto planeMaterial = m_RenderContext->CreateMaterial<PhongColorMaterial>("PhongColor", m_Environment,
        "Resources/shaders/phong/PhongColorShadow.glsl");
    planeMaterial->SetAmbientColor(glm::vec3(0.8f, 0.2f, 0.4f));
    planeMaterial->SetDiffuseColor(glm::vec3(0.8f, 0.2f, 0.4f));
    planeMaterial->SetSpecularColor(glm::vec3(1.0f));
    planeMaterial->SetShadowMap(m_RenderContext->GetFramebuffer("Shadow")->GetDepthAttachment());
    planeMaterial->SetShininess(100.0f);
}

/**
 * Defines the scene geometry for the rendering process.
 */
void Viewer::DefineSceneGeometry()
{
    // Define the cube and plane model
    m_Cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>();
    m_Cube.SetScale(glm::vec3(2.0f));
    
    m_Plane = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec3>>();
    m_Plane.SetPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    m_Plane.SetScale(glm::vec3(10.0f));
    m_Plane.SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
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
    m_RenderContext->GetViewport()->SetWidth(e.GetWidth());
    m_RenderContext->GetViewport()->SetHeight(e.GetHeight());
    
    // Update the camera size
    m_RenderContext->GetCamera()->SetViewportSize(e.GetWidth(), e.GetHeight());
    
    // Update the screen and the framebuffer
    m_RenderContext->GetViewport()->Resize(e.GetWidth(), e.GetHeight());
    m_RenderContext->GetFramebuffer("Shadow")->Resize(e.GetWidth(), e.GetHeight());
    return true;
}
