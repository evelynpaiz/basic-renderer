#pragma once

#include "Common/Renderer/Material/Material.h"
#include "Common/Renderer/Texture/Texture.h"
#include "Common/Renderer/Camera/Camera.h"

#include <random>

/**
 * A material class for Screen Space Ambient Occlusion (SSAO) calculations.
 *
 * The `OcclusionMaterial` class inherits from `Material` and provides functionality
 * for performing SSAO calculations. It allows setting textures and parameters required
 * for SSAO computations, including the generation of kernel samples and noise texture.
 *
 * Copying or moving `OcclusionMaterial` objects is disabled to ensure single ownership
 * and prevent unintended duplication of material resources.
 */
class OcclusionMaterial : public Material
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    OcclusionMaterial(const std::shared_ptr<Camera>& view, unsigned int sampleCout = 64,
                      const std::filesystem::path& filePath = std::filesystem::path("Resources/shaders/ao/SSAO.glsl"));
    /// @brief Destructor for the occlusion material.
    virtual ~OcclusionMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the depth texture map.
    /// @param texture Texture map.
    void SetDepthMap(const std::shared_ptr<Texture>& texture) { m_DepthTexture = texture; }
    
    /// @brief Set the view/camera.
    /// @param view The rendering camera.
    void SetView(const std::shared_ptr<Camera>& view) { m_View = view; }
    
    /// @brief Set the sampling radius.
    /// @param radius The radius where the samples will be generated.
    void SetRadius(const float radius) { m_Radius = radius; }
    /// @brief Set a specific bias for depth testing.
    /// @param bias The bias to be added to the depth tested.
    void SetBias(const float bias) { m_Bias = bias; }
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties into the uniforms of the shader program.
    void SetMaterialProperties() override;
    
    // Kernel
    // ----------------------------------------
    float Lerp(float a, float b, float f);
    
    void GenerateKernelSamples(std::uniform_real_distribution<float>& randomFloats,
                               std::default_random_engine& generator);
    void GenerateNoiseTexture(std::uniform_real_distribution<float>& randomFloats,
                              std::default_random_engine& generator);
    
    // Occlusion variables
    // ----------------------------------------
public:
    ///< Depth map.
    std::shared_ptr<Texture> m_DepthTexture;
    ///< Noise map.
    std::shared_ptr<Texture> m_NoiseTexture;
    
    ///< Sample kernel.
    std::vector<glm::vec3> m_Kernel;
    ///< Size of the kernel.
    unsigned int m_SampleCount;
    
    ///< View (the camera used for rendering).
    std::shared_ptr<Camera> m_View;
    
    ///< Testing radius.
    float m_Radius = 0.6f;
    float m_Bias = 0.002f;
    ///< Depth bias.
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    DISABLE_COPY_AND_MOVE(OcclusionMaterial);
};
