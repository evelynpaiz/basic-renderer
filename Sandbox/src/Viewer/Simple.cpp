#include "Viewer/Simple.h"

#include "Common/Renderer/RendererCommand.h"
#include "Common/Renderer/Shader/Shader.h"
#include "Common/Renderer/Material/Material.h"

#include <glm/gtc/matrix_transform.hpp>

/**
 * Define a layer for a 3D viewer.
 */
Simple::Simple(int width, int height)
    : Layer("Test Layer")
{
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(width, height);
    m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
}

/**
 * Attach (add) the viewer layer to the rendering engine.
 */
void Simple::OnAttach()
{
    // Define the models
    auto& materialLibrary = Renderer::GetMaterialLibrary();
    auto material = materialLibrary.Create<SimpleTextureMaterial>("SimpleColor");
    
    auto cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2>>();
    cube->SetScale(glm::vec3(2.0f));
    cube->SetMaterial(material);
    m_Models.Add("Cube", cube);
    
    auto plane = utils::Geometry::ModelPlane<GeoVertexData<glm::vec4, glm::vec2>>();
    plane->SetPosition(glm::vec3(0.0f, -1.5f, 0.0f));
    plane->SetScale(glm::vec3(10.0f));
    plane->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
    plane->SetMaterial(material);
    m_Models.Add("Plane", plane);
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Simple::OnUpdate(Timestep ts)
{
    auto& material = Renderer::GetMaterialLibrary().Get("SimpleColor");
    std::shared_ptr<SimpleTextureMaterial> simpleMaterial =
        std::dynamic_pointer_cast<SimpleTextureMaterial>(material);
    
    auto texture1 = Texture2D::CreateFromFile("Resources/textures/diffuse.jpeg");
    auto texture2 = Texture2D::CreateFromFile("Resources/textures/specular.jpeg");
    auto texture3 = utils::textures::WhiteTexture2D();
    
    // Reset rendering statistics
    Renderer::ResetStats();
    
    // Clear buffer
    RendererCommand::Clear(glm::vec4(0.33f, 0.33f, 0.33f, 1.0f));
    
    // Render
    Renderer::BeginScene(m_Camera);
    simpleMaterial->SetTextureMap(texture1);
    m_Models.Get("Plane")->DrawModel();
    //simpleMaterial->SetTextureMap(texture2);
    //m_Models.Get("Cube")->DrawModel();
    Renderer::EndScene();
    
    // Update camera
    m_Camera->OnUpdate(ts);
}

/**
 * Handle an event that possibly occurred inside the viewer layer.
 * @param e Event.
 */
void Simple::OnEvent(Event &e)
{
    // Define the event dispatcher
    EventDispatcher dispatcher(e);
    
    // Dispatch the event to the application event callbacks
    dispatcher.Dispatch<WindowResizeEvent>(
        BIND_EVENT_FN(Simple::OnWindowResize));
    
    // Handle the events on the camera
    m_Camera->OnEvent(e);
}

/**
 * Function to be called when a window resize event happens.
 *
 * @param e Event to be handled.
 * @return True if the event has been handled.
 */
bool Simple::OnWindowResize(WindowResizeEvent &e)
{
    return true;
}
