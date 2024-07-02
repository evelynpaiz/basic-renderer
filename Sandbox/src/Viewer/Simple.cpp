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
{}

/**
 * Attach (add) the viewer layer to the rendering engine.
 */
void Simple::OnAttach()
{
    auto& materialLibrary = Renderer::GetMaterialLibrary();
    auto material = materialLibrary.Create<Material>("Simple", "resources/shaders/base/Simple.Metal");
    
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
    // Reset rendering statistics
    Renderer::ResetStats();
    
    RendererCommand::Clear(glm::vec4(0.33f, 0.33f, 0.33f, 1.0f));
    
    Renderer::BeginScene();
    
    //shader->SetMat4("u_Transform.Model", glm::mat4(1.0f));
    //shader->SetMat4("u_Transform.View", glm::mat4(1.0f));
    //shader->SetMat4("u_Transform.Projection", glm::mat4(1.0f));
    
    //shader->SetVec4("u_Material.Color", glm::vec4(0.8f, 0.0f, 0.2f, 1.0f));
    
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
