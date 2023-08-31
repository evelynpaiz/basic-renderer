#pragma once

#include "Renderer/Material/Material.h"
#include "Renderer/Texture/Texture.h"

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
    OcclusionMaterial(const std::shared_ptr<Camera>& view, const std::filesystem::path& filePath =
                      std::filesystem::path("Resources/shaders/ao/SSAO.glsl"));
    /// @brief Destructor for the occlusion material.
    virtual ~OcclusionMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the depth texture map.
    /// @param texture Texture map.
    void SetDepthMap(const std::shared_ptr<Texture>& texture)
    {
        m_DepthTexture = texture;
    }
    
    /// @brief Set the view/camera.
    /// @param view The rendering camera.
    void SetView(const std::shared_ptr<Camera>& view) { m_View = view; }
    
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
    ///< Sample kernel.
    std::vector<glm::vec3> m_Kernel;
    
    ///< Depth map.
    std::shared_ptr<Texture> m_DepthTexture;
    ///< Noise map.
    std::shared_ptr<Texture> m_NoiseTexture;
    
    ///< View (the camera used for rendering).
    std::shared_ptr<Camera> m_View;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    OcclusionMaterial(const OcclusionMaterial&) = delete;
    OcclusionMaterial(OcclusionMaterial&&) = delete;

    OcclusionMaterial& operator=(const OcclusionMaterial&) = delete;
    OcclusionMaterial& operator=(OcclusionMaterial&&) = delete;
};
