#pragma once

#include "Renderer/Texture/TextureUtils.h"

class FrameBuffer;

/**
 * Specifications (properties) of a texture.
 *
 * The `TextureSpecification` provides a set of properties to define the characteristics of a
 * texture. These specifications include the size (width and height), the internal format of the texture
 * data, the texture wrap mode, the texture filtering mode, the number of samples (for multisampling),
 * and whether mipmaps should be created for the texture.
 */
struct TextureSpecification
{
    // Constructor(s)
    // ----------------------------------------
    /// @brief Define a texture with a default format.
    TextureSpecification() = default;
    /// @brief Define a texture with a specific format.
    /// @param format The texture format.
    TextureSpecification(const TextureFormat& format) :
        Format(format)
    { }
    
    /// @brief Define the size of the texture (in pixels).
    /// @param width The texture size (width).
    /// @param height The texture size (height)
    void SetTextureSize(unsigned int width, unsigned int height)
    {
        Width = width;
        Height = height;
    }
    
    // Texture specification variables
    // ----------------------------------------
    ///< The size (width and height) in pixels.
    int Width = 0, Height = 0;
    
    ///< The internal format of the texture data.
    TextureFormat Format = TextureFormat::None;
    ///< The texture wrap mode, specifying how texture coordinates outside the [0, 1] range
    ///< are handled.
    TextureWrap Wrap = TextureWrap::None;
    ///< The texture filtering mode, specifying how the texture is sampled during rendering.
    TextureFilter Filter = TextureFilter::None;
    
    ///< The number of samples in the texture. Typically used for multisampling to improve
    ///< image quality.
    int Samples = 1;
    
    ///< A flag indicating whether mipmaps should be created for the texture. Mipmaps are
    ///< precalculated versions of the texture at different levels of detail, providing smoother
    ///< rendering at varying distances
    bool MipMaps = false;
};

/**
 * Represents a texture that can be bound to geometry during rendering.
 *
 * The `Texture` class provides functionality to create, bind, unbind, and configure the texture.
 * Textures can be bound to specific texture slots for use in a `Shader`. The class supports
 * loading texture data with specified specifications using the `TextureSpecification` struct.
 *
 * Copying or moving `Texture` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture();
    Texture(const void *data);
    Texture(const TextureSpecification& spec);
    Texture(const void *data, const TextureSpecification& spec);
    virtual ~Texture();
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void BindToTextureUnit(const unsigned int slot) const;
    void Unbind() const;
    
    // Friend class definition(s)
    // ----------------------------------------
    friend class FrameBuffer;
    
protected:
    // Target type
    // ----------------------------------------
    GLenum TextureTarget() const;
    
    // Constructor
    // ----------------------------------------
    void CreateTexture(const void *data);
    
    // Destructor
    // ----------------------------------------
    void ReleaseTexture();
    
    // Texture variables
    // ----------------------------------------
protected:
    ///< ID of the texture.
    unsigned int m_ID = 0;
    ///< Texture properties.
    TextureSpecification m_Spec;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;

    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;
};

/**
 * Represents a (loaded) 2D texture used to add details to rendered geometry.
 *
 * The `Texture2D` class is a specialized subclass of  `Texture` that provides functionality to
 * load and bind 2D textures that can be applied to geometry during rendering. The class supports
 * loading textures from file paths, binding them to specific texture slots for use in a `Shader`, and
 * unbinding them after they have been used.
 *
 * Copying or moving `Texture2D` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class Texture2D : public Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture2D(const std::filesystem::path& filePath, bool flip = true);
    
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
        
private:
    // Loading
    // ----------------------------------------
    void LoadFromFile(const std::filesystem::path& filePath);
    void GenerateTexture2D(const void *data);
    
    // Texture variables
    // ----------------------------------------
private:
    ///< Path to the file.
    std::filesystem::path m_FilePath;
    ///< Texture flipping.
    bool m_Flip;

    ///< Number of channels.
    int m_Channels = 0;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Texture2D(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;

    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;
};
