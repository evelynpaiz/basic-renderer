#pragma once

#include "Renderer/Texture/TextureCube.h"

#include "Renderer/Light/Light.h"

#include "Renderer/Material/SimpleMaterial.h"

#include "Renderer/Mesh/MeshUtils.h"
#include "Renderer/Model/ModelUtils.h"

#include <glm/glm.hpp>

/**
 * Represents an environment light source in 3D rendering.
 *
 * The `EnvironmentLight` class extends the `Light` base class to define an environment light source.
 * It provides methods to set and retrieve the light's position, environment map, and additional properties
 * such as the shadow camera and 3D model representation.
 *
 * Copying or moving `EnvironmentLight` objects is disabled to ensure single ownership and prevent
 * unintended duplication of light resources.
 */
class EnvironmentLight : public Light
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate an environment light source in the world space.
    /// @param width The width that the light source covers.
    /// @param height The height that the light source covers.
    /// @param color The color of the light source.
    /// @param position The position of the light source.
    EnvironmentLight(const unsigned int width, const unsigned int height,
                     const glm::vec3 &color = glm::vec3(1.0f),
                    const glm::vec3 &position = glm::vec3(0.0f))
        : Light(color), m_Position(position)
    {
        // Define the shadow camera for the light source
        auto shadowCamera = std::make_shared<PerspectiveShadow>();
        shadowCamera->SetViewportSize(width, height);
        shadowCamera->SetPosition(position);
        shadowCamera->SetFieldOfView(90.0f);
        m_ShadowCamera = shadowCamera;
        
        // Define the framebuffer for the environment
        FrameBufferSpecification spec(width, width);
        spec.AttachmentsSpec = { TextureFormat::DEPTH24, { TextureFormat::RGB16F, TextureType::TextureCube } };
        m_Framebuffer = std::make_shared<FrameBuffer>(spec);
        
        // Define the materias for the light source
        m_EquirectangularMaterial = std::make_shared<SimpleTextureMaterial>("Resources/shaders/environment/EquirectangularMap.glsl");
        m_CubeMaterial = std::make_shared<SimpleTextureMaterial>("Resources/shaders/environment/CubeMap.glsl");
        
        // Define the light source 3D model
        m_Model = utils::Geometry::ModelCube<GeoVertexData<glm::vec4>>(m_CubeMaterial);
    }
    
    /// @brief Destructor for the environment light.
    ~EnvironmentLight() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the environment map.
    /// @param texture The texture to be used as the environment map.
    void SetEnvironmentMap(const std::shared_ptr<Texture> texture)
    {
        // Define the tranformation matrices
        static const glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
        static const glm::mat4 views[] =
        {
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
           glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
        };
        
        // Render into the cube map
        Renderer::ResetStats();
        
        m_EquirectangularMaterial->SetTextureMap(texture);
    
        m_Model.SetMaterial(m_EquirectangularMaterial);
        m_Model.SetScale(glm::vec3(2.0f));
        
        for (unsigned int i = 0; i < 6; ++i)
        {
            Renderer::BeginScene(views[i], projection);
            m_Framebuffer->BindForDrawAttachmentCube(0, i);
            
            Renderer::Clear(m_Framebuffer->GetActiveBuffers());
            m_Model.DrawModel();
            
            Renderer::EndScene();
        }
        
        m_Framebuffer->Unbind();
        
        // Update the 3D model of the light source with the rendered environment map
        m_CubeMaterial->SetTextureMap(m_Framebuffer->GetColorAttachment(0));
        
        m_Model.SetMaterial(m_CubeMaterial);
        m_Model.SetScale(glm::vec3(70.0f));
    }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the light 3D model representing a positional light.
    /// @return The light 3D model.
    Model<GeoVertexData<glm::vec4>>& GetModel() {return m_Model; }
    
    // Properties
    // ----------------------------------------
    /// @brief Define light properties into the uniforms of the shader program.
    /// @param shader The shader program.
    void DefineLightProperties(const std::shared_ptr<Shader> &shader) override
    {
        // Define basic light properties
        Light::DefineLightProperties(shader);
        // Define the positional light properties
        // (set .w coordiante as 1 to identify it as a position vector)
        shader->SetVec4("u_Light.Vector", glm::vec4(m_Position, 1.0f));
    }
    
    // Light variables
    // ----------------------------------------
private:
    ///< The position of the environment light.
    glm::vec3 m_Position;
    
    ///< Environment light's 3D model.
    Model<GeoVertexData<glm::vec4>> m_Model;
    ///< Framebuffer for environment rendering.
    std::shared_ptr<FrameBuffer> m_Framebuffer;
    
    ///< Environment light's materials.
    std::shared_ptr<SimpleTextureMaterial> m_EquirectangularMaterial;
    std::shared_ptr<SimpleTextureMaterial> m_CubeMaterial;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    EnvironmentLight(const EnvironmentLight&) = delete;
    EnvironmentLight(EnvironmentLight&&) = delete;

    EnvironmentLight& operator=(const EnvironmentLight&) = delete;
    EnvironmentLight& operator=(EnvironmentLight&&) = delete;
};
