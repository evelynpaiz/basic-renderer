#pragma once

#include "Common/Renderer/Texture/TextureUtils.h"
#include "Common/Renderer/Texture/Texture.h"

#include <filesystem>

/**
 * Represents a 2D texture that can be bound to geometry during rendering.
 *
 * The `Texture2D` class provides functionality to create, bind, unbind, and configure 2D textures.
 * 2D textures consist of a single surface with texture data. These textures can
 * be bound to specific texture slots for use in a `Shader`.
 *
 * Copying or moving `Texture2D` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class Texture2D : public Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture2D(const int& samples = 1);
    Texture2D(const void *data, const int& samples = 1);
    Texture2D(const TextureSpecification& spec, const int& samples = 1);
    Texture2D(const void *data, const TextureSpecification& spec, const int& samples = 1);
    
protected:
    // Target type
    // ----------------------------------------
    GLenum TextureTarget() const override;
    
    // Texture creation
    // ----------------------------------------
    void CreateTexture(const void *data) override;
    
    // Texture variables
    // ----------------------------------------
protected:
    ///< The number of samples in the texture.
    int m_Samples = 1;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Texture2D(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;

    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;
};

// Forward declarations
class Texture2DResource;

/**
 * Utility functions related to texture operations.
 */
namespace utils { namespace Draw {

inline bool TextureLoader(std::shared_ptr<Texture2DResource> &texture,
                          std::filesystem::path &name, const char *label,
                          const char *filter, const bool &flip);
} // namespace Draw
} // namespace utils

/**
 * Represents a (loaded) 2D texture used to add details to rendered geometry.
 *
 * The `Texture2DResource` class is a specialized subclass of  `Texture` that provides
 * functionality to load and bind 2D textures that can be applied to geometry during rendering.
 * The class supports loading textures from file paths, binding them to specific texture slots for
 * use in a `Shader`, and unbinding them after they have been used.
 *
 * Copying or moving `Texture2DResource` objects is disabled to ensure single ownership
 * and prevent unintended texture duplication.
 */
class Texture2DResource : public Texture2D
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture2DResource(const std::filesystem::path& filePath, bool flip = true);
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the file path of the texture.
    /// @return The path to the file.
    std::filesystem::path GetPath() const { return m_FilePath; }
    /// @brief Get the name of the loaded texture (file name).
    /// @return The texture name.
    std::string GetName() { return m_FilePath.filename().string(); }
    /// @brief Get the directory where the texture file is located.
    /// @return The directory of the texture.
    std::string GetDirectory() { return m_FilePath.parent_path().string(); }
    
    // Friend class definition(s)
    // ----------------------------------------
    friend bool utils::Draw::TextureLoader(std::shared_ptr<Texture2DResource> &texture,
                                           std::filesystem::path &name, const char *label,
                                           const char *filter, const bool &flip);
        
private:
    // Loading
    // ----------------------------------------
    void LoadFromFile(const std::filesystem::path& filePath);
    
    // Texture variables
    // ----------------------------------------
private:
    ///< Path to the file.
    std::filesystem::path m_FilePath;
    
    ///< Texture flipping.
    bool m_Flip;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Texture2DResource(const Texture2DResource&) = delete;
    Texture2DResource(Texture2DResource&&) = delete;

    Texture2DResource& operator=(const Texture2DResource&) = delete;
    Texture2DResource& operator=(Texture2DResource&&) = delete;
};

/**
 * Utility functions related to texture operations.
 */
namespace utils {
/// @brief Namespace containing utility functions for texturing operations.
namespace Texturing {

/**
 * Get a shared pointer to an empty texture with a checkerboard pattern.
 *
 * This function returns a shared pointer to an empty texture with a checkerboard pattern.
 * If the texture has already been created, it will be reused to avoid redundant texture creation.
 *
 * @return A shared pointer to the empty texture with a checkerboard pattern.
 */
inline std::shared_ptr<Texture2DResource> EmptyTexture()
{
    // Static variable to hold the shared pointer to the texture
    static std::shared_ptr<Texture2DResource> texture;
    
    // Check if the texture has already been created
    if (texture)
        return texture;
    
    // Create the empty texture using a ccheckerboard pattern
    texture = std::make_shared<Texture2DResource>("resources/common/checkerboard.png");
    
    // Return the created texture
    return texture;
}

} // namespace Texturing
} // namespace utils
