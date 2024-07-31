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
    auto material = materialLibrary.Create<Material>("Simple", "resources/shaders/base/Simple");
    
    auto cube = utils::Geometry::ModelCube<GeoVertexData<glm::vec4, glm::vec2, glm::vec3>>();
    cube->SetScale(glm::vec3(2.0f));
    cube->SetMaterial(material);
    m_Models.Add("Cube", cube);
}

/**
 * Render the viewer layer.
 *
 * @param deltaTime Times passed since the last update.
 */
void Simple::OnUpdate(Timestep ts)
{
    static float t = 0;
    t += ts;
    
    // Reset rendering statistics
    Renderer::ResetStats();
    
    RendererCommand::Clear(glm::vec4(0.33f, 0.33f, 0.33f, 1.0f));
    
    auto shader  = Renderer::GetMaterialLibrary().Get("Simple")->GetShader();
    shader->Bind();
    shader->SetVec3("u_Color", glm::vec3(std::cos(t), 0.0f, std::sin(t)));
    
    Renderer::BeginScene(m_Camera);
    
    m_Models.Get("Cube")->DrawModel();
    
    Renderer::EndScene();
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
