#include "enginepch.h"
#include "Renderer/Light/EnvironmentLight.h"

/**
 * Generate an environment light source in the world space.
 *
 * @param width The width that the light source covers.
 * @param height The height that the light source covers.
 * @param color The color of the light source.
 * @param position The position of the light source.
 */
EnvironmentLight::EnvironmentLight(const unsigned int width, const unsigned int height,
                                   const glm::vec3 &color, const glm::vec3 &position)
    : Light(color), m_Position(position)
  {
      // Define the shadow camera for the light source
      auto shadowCamera = std::make_shared<PerspectiveShadow>();
      shadowCamera->SetViewportSize(width, height);
      shadowCamera->SetPosition(position);
      shadowCamera->SetFieldOfView(90.0f);
      m_ShadowCamera = shadowCamera;
      
      // Define the framebuffer(s) for the environment
      const static unsigned int scale = 4;
      InitEnvironmentFramebuffers(scale * width);
      
      // Define the material(s) for the environment
      InitEnvironmentMaterials();
      
      // Define 3D model of the light source
      m_Model = utils::Geometry::ModelCube<GeoVertexData<glm::vec4>>(m_EnvMaterials["Environment"]);
  }

/**
 * Initialize framebuffers for the environment light.
 *
 * @param cubeSize Cube map resolution (width = height).
 */
void EnvironmentLight::InitEnvironmentFramebuffers(const unsigned int cubeSize)
{
    FrameBufferSpecification spec(cubeSize, cubeSize);
    spec.AttachmentsSpec = {
        TextureFormat::DEPTH24,
        { TextureFormat::RGB16F, TextureType::TextureCube }
    };
    
    spec.MipMaps = true;
    m_EnvFramebuffers["Environment"] = std::make_shared<FrameBuffer>(spec);
    
    spec.SetFrameBufferSize(32, 32);
    spec.MipMaps = false;
    m_EnvFramebuffers["Irradiance"] = std::make_shared<FrameBuffer>(spec);
    
    spec.SetFrameBufferSize(128, 128);
    spec.MipMaps = true;
    m_EnvFramebuffers["PreFilter"] = std::make_shared<FrameBuffer>(spec);
}

/**
 * Initialize materials for the environment light.
 */
void EnvironmentLight::InitEnvironmentMaterials()
{
    auto& environment = m_EnvFramebuffers["Environment"]->GetColorAttachment(0);
    
    // Equirectangular mapping
    m_EnvMaterials["Equirectangular"] = std::make_shared<SimpleTextureMaterial>(
        "Resources/shaders/environment/EquirectangularMap.glsl"
    );
    
    // Irradiance mapping
    m_EnvMaterials["Irradiance"] = std::make_shared<SimpleTextureMaterial>(
        "Resources/shaders/environment/IrradianceMap.glsl"
    );
    m_EnvMaterials["Irradiance"]->SetTextureMap(environment);
    
    // Pre-filtering mapping
    m_EnvMaterials["PreFilter"] = std::make_shared<SimpleTextureMaterial>(
        "Resources/shaders/environment/PreFilterMap.glsl"
    );
    m_EnvMaterials["PreFilter"]->SetTextureMap(environment);
    
    // Cube mapping
    m_EnvMaterials["Environment"] = std::make_shared<SimpleTextureMaterial>(
        "Resources/shaders/environment/CubeMap.glsl"
    );
    m_EnvMaterials["Environment"]->SetTextureMap(environment);
}

/**
 * Change the environment map.
 * 
 * @param texture The texture to be used as the environment map.
 */
void EnvironmentLight::SetEnvironmentMap(const std::shared_ptr<Texture> texture)
{
    // Define the tranformation matrices
    static const glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
    static const std::array<glm::mat4, 6>& views =
    {
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
       glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };
    
    // Update the current texture representing the environment map
    m_EnvMaterials["Equirectangular"]->SetTextureMap(texture);
    
    // Update the size of the environment (cube) model
    m_Model.SetScale(glm::vec3(2.0f));
    
    // Render the environment map into a cube map configuration
    RenderCubeMap(views, projection, m_EnvMaterials["Equirectangular"],
                  m_EnvFramebuffers["Environment"]);
    
    // Render the irradiance map
    RenderCubeMap(views, projection, m_EnvMaterials["Irradiance"],
                  m_EnvFramebuffers["Irradiance"]);
    
    // Render the pre-filter map
    static const unsigned int maxMipMapLevel = 5;
    for (unsigned int mip = 0; mip < maxMipMapLevel; ++mip)
    {
        // Define the roughness
        float roughness = (float)mip / (float)(maxMipMapLevel - 1);
        m_EnvMaterials["PreFilter"]->GetShader()->SetFloat("u_Material.Roughness", roughness);
        
        // reisze framebuffer according to mip-level size.
        unsigned int mipWidth  = 128 * std::pow(0.5, mip);
        unsigned int mipHeight = 128 * std::pow(0.5, mip);
        
        // Render into the cubemap
        RenderCubeMap(views, projection, m_EnvMaterials["PreFilter"],
                      m_EnvFramebuffers["PreFilter"],
                      mipWidth, mipHeight, mip, false);
    }
    
    m_EnvFramebuffers["PreFilter"]->Unbind(false);
    
    // Update the 3D model of the light source with the rendered environment map
    m_Model.SetMaterial(m_EnvMaterials["Environment"]);
    m_Model.SetScale(glm::vec3(70.0f));
}

/**
 * Render a cube map from multiple perspectives using the specified material and framebuffer.
 *
 * @param views An array of view matrices representing the six cube map faces.
 * @param projection The projection matrix for the rendering.
 * @param material The material to be used for rendering each cube map face.
 * @param framebuffer The framebuffer where the cube map is rendered.
 * @param level The mip level of the framebuffer to which the cube map is rendered.
 * @param genMipMaps A flag indicating whether to generate mipmaps for the resulting cube map.
 */
void EnvironmentLight::RenderCubeMap(const std::array<glm::mat4, 6>& views, const glm::mat4 &projection,
                                     const std::shared_ptr<SimpleTextureMaterial>& material,
                                     const std::shared_ptr<FrameBuffer>& framebuffer,
                                     const unsigned int& viewportWidth, const unsigned int& viewportHeight,
                                     const unsigned int &level, const bool &genMipMaps)
{
    // Set the material for rendering
        m_Model.SetMaterial(material);

    // Loop through each face of the cube map
    for (unsigned int i = 0; i < views.size(); ++i)
    {
        // Begin rendering scene with the specified view and projection matrices
        Renderer::BeginScene(views[i], projection);

        // Bind the framebuffer for drawing to the current cube map face and mip level
        framebuffer->BindForDrawAttachmentCube(0, i, level);

        // Set the viewport dimensions if provided
        if (viewportWidth > 0 && viewportHeight > 0)
            Renderer::SetViewport(0, 0, viewportWidth, viewportHeight);

        // Clear the active buffers in the framebuffer
        Renderer::Clear(framebuffer->GetActiveBuffers());

        // Draw the model using the specified material
        m_Model.DrawModel();

        // End the rendering scene
        Renderer::EndScene();
    }

    // Unbind the framebuffer and optionally generate mipmaps
    framebuffer->Unbind(genMipMaps);
}

/**
 * Define in the shader the irradiance map computed from the environment.
 *
 * @param shader The shader program.
 * @param slot The texture slot.
 */
void EnvironmentLight::DefineIrradianceMap(const std::shared_ptr<Shader> &shader,
                                           const unsigned int slot)
{
    utils::Texturing::SetTextureMap(shader, "u_Light.IrradianceMap",
                                    m_EnvFramebuffers["Irradiance"]->GetColorAttachment(0), slot);
}

/**
 * Define in the shader the pre-filter map computed from the environment.
 *
 * @param shader The shader program.
 * @param slot The texture slot.
 */
void EnvironmentLight::DefinePreFilterMap(const std::shared_ptr<Shader> &shader,
                                          const unsigned int slot)
{
    utils::Texturing::SetTextureMap(shader, "u_Light.PreFilterMap",
                                    m_EnvFramebuffers["PreFilter"]->GetColorAttachment(0), slot);
}
