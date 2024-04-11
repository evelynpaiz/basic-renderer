#pragma once

#include "Renderer/Light/Light.h"
#include "Renderer/Light/EnvironmentLight.h"

#include "Scene/Viewport.h"

/**
 * Represents the specification for a render pass in a rendering pipeline.
 *
 * The `RenderPassSpecification` struct defines the parameters and settings
 * for a single render pass in a rendering pipeline. It includes information
 * about the camera, framebuffer, models to be rendered, and optionally the
 * clear color for the framebuffer.
 */
struct RenderPassSpecification
{
    ///< Active flag.
    bool Active = true;
    
    ///< The camera used for rendering in this pass.
    std::shared_ptr<Camera> Camera;
    ///< The models to render in this pass, along with their associated materials.
    std::unordered_map<std::string, std::string> Models;
    ///< The framebuffer to render to in this pass.
    std::shared_ptr<FrameBuffer> Framebuffer;
    
    ///< The clear color for the framebuffer, if specified.
    std::optional<glm::vec4> Color;
    ///< The viewport size to render into, if specified.
    std::optional<glm::vec2> Size;
    
    ///< Optional piece of code to be executed after rendering the pass.
    std::function<void()> PreRenderCode;
    ///< Optional piece of code to be executed after rendering the pass.
    std::function<void()> PostRenderCode;
};

/**
 * A library for managing render passes used in rendering.
 *
 * The `RenderPassLibrary` class provides functionality to add, create, retrieve, and check for
 * the existence of render passes within the library. Render passes can be associated with unique names
 * for easy access.
 */
class RenderPassLibrary : public Library<RenderPassSpecification>
{
public:
    // Constructor/Destructor
    // ----------------------------------------
    /// @brief Delete the library.
    ~RenderPassLibrary() override = default;
    
    // Add/Load
    // ----------------------------------------
    /// @brief Adds an object to the library.
    /// @param name The name to associate with the object.
    /// @param object The object to add.
    /// @note If an object with the same name already exists in the library, an assertion failure
    /// will occur.
    void Add(const std::string& name,
             const RenderPassSpecification& object) override
    {
        Library::Add(name, object);
        m_Order.push_back(name);
    }
    
    // Library variables
    // ----------------------------------------
private:
    ///< Rendering order.
    std::vector<std::string> m_Order;
    
    // Friend classes
    // ----------------------------------------
public:
    friend class Scene;
};

class Scene
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    /// @brief Create a new scene.
    Scene(int width, int height,
          const std::filesystem::path& viewportShader = "");
    /// @brief Delete the specified scene.
    ~Scene() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the size (width) of the viewport.
    /// @return The width size.
    const int GetViewportWidth() const { return m_Viewport->m_Width; };
    /// @brief Get the size (height) of the viewport.
    /// @return The height size.
    const int GetViewportHeight() const { return m_Viewport->m_Height; };
    
    /// @brief Get the viewport where the scene is being rendered.
    /// @return The viewport.
    const std::shared_ptr<Viewport>& GetViewport() const { return m_Viewport; }
    
    /// @brief Get the camera used currently to render the scene.
    /// @return The active camera.
    const std::shared_ptr<Camera>& GetCamera() const { return m_Camera; }
    /// @brief Get the light in the scene.
    /// @return The light source.
    const std::shared_ptr<Light>& GetLightSource() const { return m_Light; }
    ///< @brief Get the surrounding environment light around the scene.
    ///< @return The environment light.
    const std::shared_ptr<EnvironmentLight>& GetEnvironment() const { return m_Environment; }
    
    /// @brief Get the models defined in the scene.
    /// @return The scene's models.
    ModelLibrary& GetModels() { return m_Models; }
    
    /// @brief Get the framebuffers library.
    /// @return The defined framebuffers.
    FrameBufferLibrary& GetFrameBufferLibrary() { return m_FramebufferLibrary; }
    
    /// @brief Get the render passes on the scene.
    /// @return The defined render passes with its specifications.
    RenderPassLibrary& GetRenderPasses() { return m_RenderPasses; }
    
    // Setter(s)
    // ----------------------------------------
    ///< @brief Define the light source in the scene.
    ///< @param light The light source.
    void SetLightSource(const std::shared_ptr<Light>& light) 
    {
        m_Light = light;
        
        if (m_Models.Exists("Light"))
            m_Models.Get("Light") = m_Light->GetModel();
        else
            m_Models.Add("Light", m_Light->GetModel());
    }
    
    // Render
    // ----------------------------------------
    void Draw();
    
private:
    void Draw(const RenderPassSpecification& pass);
    
    // Scene variables
    // ----------------------------------------
private:
    ///< Viewport (displays the rendered image).
    std::shared_ptr<Viewport> m_Viewport;
    
    ///< Main camera.
    std::shared_ptr<Camera> m_Camera;
    ///< Light sources in the scene.
    std::shared_ptr<Light> m_Light;
    std::shared_ptr<EnvironmentLight> m_Environment;
    
    ///< Set of objects in the scene.
    ModelLibrary m_Models;
    
    ///< Framebuffer(s) library with all the rendered images.
    FrameBufferLibrary m_FramebufferLibrary;
    
    ///< Render passes for the rendering of the scene.
    RenderPassLibrary m_RenderPasses;
};
