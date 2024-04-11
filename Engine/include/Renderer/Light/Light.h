#pragma once

#include "Renderer/Shader/Shader.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Buffer/FrameBuffer.h"

#include "Renderer/Light/ShadowCamera.h"
#include "Renderer/Model/Model.h"

#include <glm/glm.hpp>

/**
 * Base class for light.
 *
 * Copying or moving `BaseLight` objects is disabled to ensure single ownership and prevent unintended
 * duplication of light resources.
 */
class BaseLight
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Delete the base light.
    virtual ~BaseLight() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light 3D model representing the light.
    /// @return The light 3D model.
    virtual const std::shared_ptr<BaseModel>& GetModel() { return m_Model; }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Define a base light.
    BaseLight()
    {
        // Define the depth material if it has not been define yet
        auto& library = Renderer::GetMaterialLibrary();
        if (!library.Exists("Depth"))
            library.Create<Material>("Depth", "Resources/shaders/depth/DepthMap.glsl");
    }
    
    // Light variables
    // ----------------------------------------
protected:
    ///< Light model (visible in the scene).
    std::shared_ptr<BaseModel> m_Model;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    BaseLight(const BaseLight&) = delete;
    BaseLight(BaseLight&&) = delete;

    BaseLight& operator=(const BaseLight&) = delete;
    BaseLight& operator=(BaseLight&&) = delete;
};

/**
 * Base class for light sources used in a scene.
 *
 * The `Light` class serves as a base class for defining different types of light sources used in 3D
 * rendering. It provides common functionality for defining and retrieving the color of the light source.
 * Derived classes can override the `DefineLightProperties` method to set additional light
 * properties in the shader, such as position or direction.
 *
 * Copying or moving `Light` objects is disabled to ensure single ownership and prevent unintended
 * duplication of light resources.
 */
class Light : public BaseLight
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
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the color of the light source.
    /// @return The color of the light source.
    glm::vec3 GetColor() const { return m_Color; }
    
    /// @brief Get the ambient strength of the light source.
    /// @return The ambient strength of the light source.
    float GetAmbientStrength() const { return m_AmbientStrength; }
    /// @brief Get the diffuse strength of the light source.
    /// @return The diffuse strength of the light source.
    float GetDiffuseStrength() const { return m_DiffuseStrength; }
    /// @brief Get the specular strength of the light source.
    /// @return The specular strength of the light source.
    float GetSpecularStrength() const { return m_SpecularStrength; }
    
    /// @brief Get the texture containing the shadow map of the light source.
    /// @return The shadow map.
    const std::shared_ptr<Texture>& GetShadowMap() const
    {
        return m_Framebuffer->GetDepthAttachment();
    }
    
    /// @brief Get the camera used for shadow mapping to generate depth maps for shadow calculations.
    /// @return The viewpoint of the light source.
    const std::shared_ptr<Camera>& GetShadowCamera() const { return m_ShadowCamera; }
    /// @brief Get the framebuffer with the rendered shadow map.
    /// @return The shadow map framebuffer.
    const std::shared_ptr<FrameBuffer>&  GetFramebuffer() const { return m_Framebuffer; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define the general properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineGeneralProperties(const std::shared_ptr<Shader> &shader)
    {
        shader->SetVec3("u_Light.Color", m_Color);
        shader->SetVec4("u_Light.Vector", m_Vector);
    }
    /// @brief Define the strength properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineStrenghtProperties(const std::shared_ptr<Shader> &shader)
    {
        if (m_AmbientStrength > 0.0)
            shader->SetFloat("u_Light.La", m_AmbientStrength);
        if (m_DiffuseStrength > 0.0)
            shader->SetFloat("u_Light.Ld", m_DiffuseStrength);
        if (m_SpecularStrength > 0.0)
            shader->SetFloat("u_Light.Ls", m_SpecularStrength);
    }
    /// @brief Define the transformation properties (from the light) into the uniforms of the shader program.
    /// @param shader Shader program to be used.
    void DefineTranformProperties(const std::shared_ptr<Shader> &shader)
    {
        const static glm::mat4 textureMatrix = glm::mat4(
            0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f
        );
        
        shader->SetMat4("u_Transform.Light",
                        m_ShadowCamera->GetProjectionMatrix() *
                        m_ShadowCamera->GetViewMatrix());
        shader->SetMat4("u_Transform.Texture", textureMatrix);
    }
    
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader)
    {
        DefineGeneralProperties(shader);
        DefineStrenghtProperties(shader);
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a light source.
    /// @param color The color of the light source.
    Light(const glm::vec4 &vector,
          const glm::vec3 &color = glm::vec3(1.0f))
        : BaseLight(), m_Vector(vector), m_Color(color)
    {};
    /// @brief Initialize the shadow map framebuffer.
    /// @param width Framebuffer's width.
    /// @param height Framebuffer's height.
    void InitShadowMapBuffer(int width, int height)
    {
        FrameBufferSpecification spec;
        spec.SetFrameBufferSize(width, height);
        spec.AttachmentsSpec = { TextureFormat::DEPTH24 };
        m_Framebuffer = std::make_shared<FrameBuffer>(spec);
    }
    
protected:
    // Light variables
    // ----------------------------------------
    ///< The position of the light if .w is defined as 1.0f, or
    ///< the direction of the light if .w is defined as 0.0f.
    glm::vec4 m_Vector;
    
    ///< The light color.
    glm::vec3 m_Color;
    
    ///< The light intensities.
    float m_AmbientStrength = 0.2f;
    float m_DiffuseStrength = 0.6f;
    float m_SpecularStrength = 0.4f;
    
    ///< The light viewpoint (used for rendering shadows).
    std::shared_ptr<Camera> m_ShadowCamera;
    ///< Framebuffer to render into the shadow map.
    std::shared_ptr<FrameBuffer> m_Framebuffer;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Light(const Light&) = delete;
    Light(Light&&) = delete;

    Light& operator=(const Light&) = delete;
    Light& operator=(Light&&) = delete;
};
