#pragma once

#include "Renderer/Material/Material.h"
#include "Renderer/Material/SimpleMaterial.h"

#include "Renderer/Light/Light.h"
#include "Renderer/Light/PointLight.h"

/**
 * A material class for Phong shading with color-based lighting.
 *
 * The `PhongColorMaterial` class is a subclass of `SimpleColorMaterial` and provides a material
 * definition for shading 3D models using Phong lighting with color-based illumination. It uses a shader specified
 * by the given file path to apply the shading to the model. The light source can be set using the `SetLight`
 * method, and the material properties and light properties are then applied to the shader program using the
 * `SetMaterialProperties` method.
 *
 * Copying or moving `PhongColorMaterial` objects is disabled to ensure single ownership and prevent
 * unintended duplication of material resources.
 */
class PhongColorMaterial : public SimpleColorMaterial
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    /// @brief Generate a phong material object with the specified shader file path.
    /// @param filePath The file path to the shader used by the material.
    /// @param light The light type to use for shading.
    PhongColorMaterial(const std::filesystem::path& filePath =
                       std::filesystem::path("Resources/shaders/PhongColor.glsl"),
                       const std::shared_ptr<Light> &light = std::make_shared<PointLight>())
        : SimpleColorMaterial(filePath), m_Light(light)
    {
        m_NormalMatrix = true;
        m_ViewDirection = true;
    }
    /// @brief Destructor for the basic material.
    ~PhongColorMaterial() override = default;
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Set the albedo color.
    /// @param color Albedo color in RGBA.
    void SetColor (const glm::vec4& color) override {
        // Set the color as the ambient and diffuse coefficients
        m_Ka = color;
        m_Kd = color;
        
        // Set the color albedo information
        SimpleColorMaterial::SetColor(color);
    }

    /// @brief Set the ambient coefficient for the material.
    /// @param k The ambient coefficient representing the RGB color components.
    void SetAmbientCoefficient(const glm::vec3 &k) { m_Ka = k; }
    /// @brief Set the diffuse coefficient for the material.
    /// @param k The diffuse coefficient representing the RGB color components.
    void SetDiffuseCoefficient(const glm::vec3 &k) { m_Kd = k; }
    /// @brief Set the specular coefficient for the material.
    /// @param k The specular coefficient representing the RGB color components.
    void SetSpecularCoefficient(const glm::vec3 &k) { m_Ks = k; }
    
    /// @brief Set the shininess for the material.
    /// @param shininess The shininess value to set for the material.
    void SetShininess(float shininess) { m_Shininess = shininess; }
    
    /// @brief Set the light source for the material.
    /// @param texture The light source.
    void SetLight(const std::shared_ptr<Light>& light) { m_Light = light; }
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the ambient coefficient of the material.
    /// @return The ambient coefficient representing the RGB color components.
    const glm::vec3& GetAmbientCoefficient() const { return m_Ka; }
    /// @brief Get the diffuse coefficient of the material.
    /// @return The diffuse coefficient representing the RGB color components.
    const glm::vec3& GetDiffuseCoefficient() const { return m_Kd; }
    /// @brief Get the specular coefficient of the material.
    /// @return The specular coefficient representing the RGB color components.
    const glm::vec3& GetSpecularCoefficient() const { return m_Ks; }
    
    /// @brief Get the shininess of the material.
    /// @return The shininess value of the material.
    float GetShininess() const { return m_Shininess; }
    
    /// @brief Get the light source used for shading.
    /// @return The light source.
    std::shared_ptr<Light> GetLight() const { return m_Light; }
    
protected:
    // Properties
    // ----------------------------------------
    /// @brief Set the material properties into the uniforms of the shader program.
    void SetMaterialProperties() override
    {
        // Set the basic material properties
        SimpleColorMaterial::SetMaterialProperties();
        
        // Set the phong material properties
        m_Shader->SetVec3("u_Material.Ka", m_Ka);
        m_Shader->SetVec3("u_Material.Kd", m_Kd);
        m_Shader->SetVec3("u_Material.Ks", m_Ks);
        m_Shader->SetFloat("u_Material.Shininess", m_Shininess);
        
        // Set the light properties
        m_Light->DefineLightProperties(m_Shader);
    }
    
    // Basic material variables
    // ----------------------------------------
private:
    ///< Ambient coefficient.
    glm::vec3 m_Ka = glm::vec3(1.0f);
    ///< Diffuse coefficient.
    glm::vec3 m_Kd = glm::vec3(1.0f);
    ///< Specular coefficient.
    glm::vec3 m_Ks = glm::vec3(1.0f);
    
    ///< Material shininess.
    float m_Shininess = 32.0f;
    
    ///< Light source.
    std::shared_ptr<Light> m_Light;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    PhongColorMaterial(const PhongColorMaterial&) = delete;
    PhongColorMaterial(PhongColorMaterial&&) = delete;

    PhongColorMaterial& operator=(const PhongColorMaterial&) = delete;
    PhongColorMaterial& operator=(PhongColorMaterial&&) = delete;
};
