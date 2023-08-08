#pragma once

#include "Renderer/Buffer/FrameBuffer.h"

#include "Renderer/Camera/OrthographicCamera.h"
#include "Renderer/Camera/PerspectiveCamera.h"

#include <glm/glm.hpp>

/**
 * Represents an orthographic shadow camera projection.
 *
 * The `OrthographicShadow` class extends the `OrthographicCamera` class to define a
 * camera projection suitable for rendering shadows. It inherits the functionality of the orthographic
 * camera and updates the view matrix accordingly for shadow calculations.
 */
class OrthographicShadow : public OrthographicCamera
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    /// @brief Generate an orthographic shadow camera with default values.
    OrthographicShadow() : OrthographicCamera(1, 1) {}
    /// @brief Destructs the orthographic shadow camera.
    virtual ~OrthographicShadow() = default;
    
    // Transformation matrices
    // ----------------------------------------
    /// @brief Update the camera view matrix.
    /// This method updates the camera's view matrix based on its position and target, using the
    /// `CalculateLookAtMatrix` utility function.
    virtual void UpdateViewMatrix()
    {
        m_ViewMatrix = utils::matrix::CalculateLookAtMatrix(m_Position, m_Target);
    }
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    OrthographicShadow(const OrthographicShadow&) = delete;
    OrthographicShadow(Camera&&) = delete;

    OrthographicShadow& operator=(const OrthographicShadow&) = delete;
    OrthographicShadow& operator=(OrthographicShadow&&) = delete;
};

/**
 * Represents a perspective shadow camera projection.
 *
 * The `PerspectiveShadow` class extends the `PerspectiveCamera` class to define a
 * camera projection suitable for rendering shadows. It inherits the functionality of the perspective
 * camera and updates the view matrix accordingly for shadow calculations.
 */
class PerspectiveShadow : public PerspectiveCamera
{
public:
    // Constructor(s)/ Destructor
    // ----------------------------------------
    /// @brief Generate a perspective shadow camera with default values.
    PerspectiveShadow() : PerspectiveCamera(1, 1) {}
    /// @brief Destructs the orthographic shadow camera.
    virtual ~PerspectiveShadow() = default;
    
    // Transformation matrices
    // ----------------------------------------
    /// @brief Update the camera view matrix.
    /// This method updates the camera's view matrix based on its position and target, using the
    /// `CalculateLookAtMatrix` utility function.
    virtual void UpdateViewMatrix()
    {
        m_ViewMatrix = utils::matrix::CalculateLookAtMatrix(m_Position, m_Target);
    }
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    PerspectiveShadow(const PerspectiveShadow&) = delete;
    PerspectiveShadow(Camera&&) = delete;

    PerspectiveShadow& operator=(const PerspectiveShadow&) = delete;
    PerspectiveShadow& operator=(PerspectiveShadow&&) = delete;
};

/**
 * Base class for light sources used in 3D rendering.
 *
 * The `Light` class serves as a base class for defining different types of light sources used in 3D
 * rendering. It provides common functionality for defining and retrieving the color of the light source.
 * Derived classes can override the `DefineLightProperties` method to set additional light
 * properties in the shader, such as position or direction.
 *
 * Copying or moving `Light` objects is disabled to ensure single ownership and prevent unintended
 * duplication of light resources.
 */
class Light
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Destructor for the light type.
    virtual ~Light() = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the color of the light source.
    /// @param color The color of the light source.
    void SetColor(const glm::vec3 &color) { m_Color = color; }
    
    /// @brief Set the strength of the ambient component of the light source.
    /// @param s The strength of the ambient component (a value between 0 and 1).
    void SetAmbientStrength(float s) { m_AmbientStrength = s; }
    /// @brief Set the strength of the diffuse component of the light source.
    /// @param s The strength of the diffuse component (a value between 0 and 1).
    void SetDiffuseStrength(float s) { m_DiffuseStrength = s; }
    /// @brief Set the strength of the specular component of the light source.
    /// @param s The strength of the specular component (a value between 0 and 1).
    void SetSpecularStrength(float s) { m_SpecularStrength = s; }
    
    /// @brief Change the light framebuffer resolution.
    /// @param width Viewport size (width).
    /// @param height Viewport size (height).
    void SetViewportSize(const int width, const int height)
    {
        // Check input values
        if (width <= 0 || height <= 0)
        {
            CORE_WARN("Attempted to rezize light resolution to {0}, {1}", width, height);
            return;
        }

        // Define the new resolution value for light framebuffer
        m_Framebuffer->Resize(width, height);
        
        // Update the light viewpoint resolution
        m_Viewpoint->SetViewportSize(width, height);
    }
    /// @brief Set whether shadow mapping should be active.
    /// @param map Enable or disable shadow mapping
    void SetShadowMap(const bool map) { m_ShadowMapping = map; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the color of the light source.
    /// @return The color of the light source.
    glm::vec3 GetColor() const { return m_Color; }
    
    /// @brief Get the framebuffer containing the scene renderered from the light viewpoint.
    /// @return The light framebuffer.
    const std::shared_ptr<FrameBuffer>& GetFramebuffer() { return m_Framebuffer; }
    
    /// @brief Get the camera used for shadow mapping to generate depth maps for shadow calculations.
    /// @return The viewpoint of the light source.
    const std::shared_ptr<Camera>& GetViewPoint() { return m_Viewpoint; }
    /// @brief Defines if shadow mapping is currently applied.
    /// @return Whether shadow mapping is enabled or not.
    bool IsShadowMapActive() { return m_ShadowMapping; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    /// @param slot Next texture slot available.
    virtual void DefineLightProperties(const std::shared_ptr<Shader> &shader,
                                       unsigned int slot = 0)
    {
        shader->SetVec3("u_Light.Color", m_Color);
        
        shader->SetFloat("u_Light.La", m_AmbientStrength);
        shader->SetFloat("u_Light.Ld", m_DiffuseStrength);
        shader->SetFloat("u_Light.Ls", m_SpecularStrength);
        
        if (!m_ShadowMapping)
            return;
        
        shader->SetMat4("u_Transform.Light", m_Viewpoint->GetProjectionMatrix()
                        * m_Viewpoint->GetViewMatrix());

        m_Framebuffer->GetDepthAttachment()->BindToTextureUnit(slot);
        shader->SetInt("u_Light.ShadowMap", slot);
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a light source.
    /// @param color The color of the light source.
    Light(const glm::vec3 &color = glm::vec3(1.0f))
    : m_Color(color)
    {
        FrameBufferSpecification spec(1, 1);
        spec.AttachmentsSpec = {
            TextureFormat::DEPTH24
        };
        m_Framebuffer = std::make_shared<FrameBuffer>(spec);
    }
    
    // Light variables
    // ----------------------------------------
protected:
    ///< The light color.
    glm::vec3 m_Color;
    
    ///< The light intensities.
    float m_AmbientStrength = 0.4f;
    float m_DiffuseStrength = 0.6f;
    float m_SpecularStrength = 1.0f;
    
    ///< Defines if the variables for shadow mapping should be set.
    bool m_ShadowMapping = false;
    
    ///< The light viewpoint (used for rendering shadows).
    std::shared_ptr<Camera> m_Viewpoint;
    ///< The light framebuffer (rendering from the light point of view).
    std::shared_ptr<FrameBuffer> m_Framebuffer;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Light(const Light&) = delete;
    Light(Light&&) = delete;

    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;
};
