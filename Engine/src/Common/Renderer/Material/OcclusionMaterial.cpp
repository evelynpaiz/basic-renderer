#include "enginepch.h"
#include "Common/Renderer/Material/OcclusionMaterial.h"

#include "Common/Renderer/Texture/Texture2D.h"

/**
 * Generate an occlusion material object with the specified shader file path.
 *
 * @param view The rendering camera.
 * @param filePath The file path to the shader used by the material.
 */
OcclusionMaterial::OcclusionMaterial(const std::shared_ptr<Camera>& view, unsigned int sampleCout,
                                     const std::filesystem::path& filePath)
    : Material(filePath), m_View(view), m_SampleCount(sampleCout)
{
    // Create a random number generator for generating floats in the range [0.0f, 1.0f]
    std::uniform_real_distribution<float> randomFloats(0.0f, 1.0f);
    // Create a default random number engine
    std::default_random_engine generator;

    // Generate sample kernel
    GenerateKernelSamples(randomFloats, generator);
    // Generate noise texture
    GenerateNoiseTexture(randomFloats, generator);

}

/**
 * Set the material properties into the uniforms of the shader program.
 */
void OcclusionMaterial::SetMaterialProperties()
{
    Material::SetMaterialProperties();
    m_Shader->SetMat4("u_ViewProjection", m_View->GetProjectionMatrix());
    m_Shader->SetMat4("u_InvViewProjection", glm::inverse(m_View->GetProjectionMatrix()));
    
    utils::Texturing::SetTextureMap(m_Shader, "u_Material.DepthMap", m_DepthTexture, m_Slot++);
    utils::Texturing::SetTextureMap(m_Shader, "u_Material.NoiseMap", m_NoiseTexture, m_Slot++);
    
    m_Shader->SetInt("u_Material.SampleCount", m_SampleCount);
    for (unsigned int i = 0; i < m_SampleCount; ++i)
        m_Shader->SetVec3("u_Kernel[" + std::to_string(i) + "]", m_Kernel[i]);
    
    m_Shader->SetFloat("u_Material.Radius", m_Radius);
    m_Shader->SetFloat("u_Material.Bias", m_Bias);
}

/**
 * Perform a linear interpolation (lerp) between two values.
 *
 * @param a The starting value of the interpolation.
 * @param b The ending value of the interpolation.
 * @param f The interpolation factor, typically in the range [0, 1], where 0 corresponds to `a`
 *          and 1 corresponds to `b`.
 * @return The interpolated value between `a` and `b`.
 */
float OcclusionMaterial::Lerp(float a, float b, float f)
{
    return a + f * (b - a);
}

/**
 * Generate a set of SSAO kernel samples for occlusion calculations.
 *
 * This function generates a set of SSAO (Screen Space Ambient Occlusion) kernel samples
 * that are used for occlusion calculations. The samples are distributed on a unit hemisphere
 * and are scaled and oriented to bias them towards the center of the kernel.
 *
 * @param randomFloats A distribution providing random floating-point numbers in the range [0, 1].
 * @param generator The random number generator engine.
 */
void OcclusionMaterial::GenerateKernelSamples(std::uniform_real_distribution<float>& randomFloats,
                                              std::default_random_engine& generator)
{
    // Generate 64 SSAO kernel samples
    for (unsigned int i = 0; i < m_SampleCount; ++i)
    {
        // Generate a random 3D vector for the sample
        glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0,
                         randomFloats(generator) * 2.0 - 1.0,
                         randomFloats(generator));

        // Normalize the sample vector to ensure it lies on the unit sphere
        sample = glm::normalize(sample);

        // Randomly scale the sample along its direction
        sample *= randomFloats(generator);

        // Calculate a scale factor based on the index to make samples more aligned to the center of the kernel
        float scale = (float)i / m_SampleCount;

        // Apply a quadratic function to the scale factor to bias samples towards the center
        scale = Lerp(0.1f, 1.0f, scale * scale);

        // Scale the sample vector by the calculated scale factor
        sample *= scale;

        // Add the scaled sample to the SSAO kernel vector
        m_Kernel.push_back(sample);
    }
}

/**
 * Generates a noise texture for SSAO calculations.
 *
 * This function generates a noise texture that is used for randomization in SSAO calculations.
 * The texture is populated with randomly generated vectors that are distributed within the range
 * of [-1, 1] in the x and y dimensions.
 *
 * @param randomFloats A distribution providing random floating-point numbers in the range [0, 1].
 * @param generator The random number generator engine.
 */
void OcclusionMaterial::GenerateNoiseTexture(std::uniform_real_distribution<float>& randomFloats,
                                             std::default_random_engine& generator)
{
    std::vector<glm::vec3> ssaoNoise;
    for (unsigned int i = 0; i < 16; i++)
    {
        glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0,
                        randomFloats(generator) * 2.0 - 1.0, 0.0f);
        ssaoNoise.push_back(noise);
    }
    
    TextureSpecification spec(TextureFormat::RGBA16F);
    spec.SetTextureSize(4, 4);
    spec.Filter = TextureFilter::Nearest;
    spec.Wrap = TextureWrap::Repeat;
    
    m_NoiseTexture = std::make_shared<Texture2D>(ssaoNoise.data(), spec);
}
