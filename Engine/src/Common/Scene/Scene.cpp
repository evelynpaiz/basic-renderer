#include "enginepch.h"
#include "Scene/Scene.h"

#include "Renderer/Material/SimpleMaterial.h"
#include "Renderer/Light/PositionalLight.h"

/**
 * Define a scene to be rendered.
 *
 * @param width Viewport width.
 * @param height Viewport height.
 * @param viewportShader The shader file path to be used for shading the viewport.
 */
Scene::Scene(int width, int height,
             const std::filesystem::path& viewportShader)
{
    // Define the rendering camera
    m_Camera = std::make_shared<PerspectiveCamera>(width, height);
    
    // Define the lights
    m_Environment = std::make_shared<EnvironmentLight>(width, height);
    m_Models.Add("Environment", m_Environment->GetModel());
    
    // Define the viewport
    m_Viewport = std::make_shared<Viewport>(width, height, viewportShader);
    
    Renderer::GetMaterialLibrary().Add("Viewport", m_Viewport->m_Material);
    m_FramebufferLibrary.Add("Viewport", m_Viewport->m_Framebuffer);
    m_Models.Add("Viewport", m_Viewport->m_Geometry);
}

/**
 * Draws the scene using the provided render pass specification.
 *
 * @param pass The render pass specification containing the parameters for drawing the scene.
 */
void Scene::Draw(const RenderPassSpecification &pass)
{
    // Run the post-rendering code
    if (pass.PreRenderCode)
        pass.PreRenderCode();
    
    // Bind the framebuffer if it is provided
    if (pass.Framebuffer)
        pass.Framebuffer->Bind();
    
    // Begin the scene with the provided camera, or without a camera if none is provided
    if (pass.Camera)
        Renderer::BeginScene(pass.Camera);
    else
        Renderer::BeginScene();
    
    if(pass.Size.has_value())
        Renderer::SetViewport(0, 0, pass.Size.value().x, pass.Size.value().y);
    
    // Clear the framebuffer with the specified color (if provided), or clear it with the active buffers
    if (pass.Framebuffer && pass.Color.has_value())
        Renderer::Clear(pass.Color.value(), pass.Framebuffer->GetActiveBuffers());
    else if (pass.Framebuffer)
        Renderer::Clear(pass.Framebuffer->GetActiveBuffers());
    else if (pass.Color.has_value())
        Renderer::Clear(pass.Color.value());
    else
        Renderer::Clear();
    
    // Render each model with its associated material
    for (auto& pair : pass.Models)
    {
        auto& model = m_Models.Get(pair.first);
        
        // Check that the model has been defined
        if (model)
        {
            if (!pair.second.empty())
                model->SetMaterial(Renderer::GetMaterialLibrary().Get(pair.second));
            
            // Draw the environment with a different configuration
            if (pair.first == "Environment" &&
                m_Environment->GetEnvironmentMap())
            {
                Renderer::SetDepthFunction(DepthFunction::LEqual);
                model->DrawModel();
                Renderer::SetDepthFunction(DepthFunction::Less);
            }
            // Draw the model
            else
                model->DrawModel();
        }
    }
        
    // End the scene
    Renderer::EndScene();
    
    // Unbind the framebuffer if it was provided
    if (pass.Framebuffer)
        pass.Framebuffer->Unbind();
    
    // Run the post-rendering code
    if (pass.PostRenderCode)
        pass.PostRenderCode();
}

/**
 * Draws the scene according to the specified render passes.
 */
void Scene::Draw()
{
    for (auto& name : m_RenderPasses.m_Order)
    {
        auto& pass = m_RenderPasses.Get(name);
        if (pass.Active);
            Draw(pass);
    }
}
