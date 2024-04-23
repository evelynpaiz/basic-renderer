#pragma once

#include "Renderer/Texture/TextureUtils.h"
#include <filesystem>

/**
 * Enumeration representing the types of textures.
 *
 * The `TextureType` enum class defines the various types of textures that can be used
 * within a graphics application. It provides identifiers for different texture categories,
 * such as regular 2D textures and cube maps, which are used for different rendering purposes.
 * This enum is typically used in functions and structures to specify the type of a texture.
 */
enum class TextureType
{
    None = 0,
    TEXTURE1D,
    TEXTURE2D,
    TEXTURE3D,
    TEXTURECUBE,
};

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
    /// @brief Define a texture with a specific format.
    /// @param format The texture format.
    /// @param type The type of the texture.
    TextureSpecification(const TextureFormat& format, const TextureType& type) :
        Type(type), Format(format)
    { }
    /// @brief Define a texture with a specific format.
    /// @param format The texture format.
    /// @param wrap The texture wrap.
    TextureSpecification(const TextureFormat& format, const TextureWrap& wrap) :
        Format(format), Wrap(wrap)
    { }
    
    /// @brief Define the size of the texture (in pixels).
    /// @param width The texture size (width).
    /// @param height The texture size (height)
    void SetTextureSize(unsigned int width, unsigned int height = 0,
                        unsigned int depth = 0)
    {
        Width = width;
        Height = height;
        Depth = depth;
    }
    
    // Texture specification variables
    // ----------------------------------------
    ///< The size (width and height) in pixels.
    int Width = 0, Height = 0, Depth = 0;
    
    ///< The type (dimension) of the texture.
    TextureType Type = TextureType::TEXTURE2D;
    
    ///< The internal format of the texture data.
    TextureFormat Format = TextureFormat::None;
    ///< The texture wrap mode, specifying how texture coordinates outside the [0, 1] range
    ///< are handled.
    TextureWrap Wrap = TextureWrap::None;
    ///< The texture filtering mode, specifying how the texture is sampled during rendering.
    TextureFilter Filter = TextureFilter::None;
    
    ///< A flag indicating whether mipmaps should be created for the texture. Mipmaps are
    ///< precalculated versions of the texture at different levels of detail, providing smoother
    ///< rendering at varying distances
    bool MipMaps = false;
};

// Forward declarations
class FrameBuffer;

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
    // Destructor
    // ----------------------------------------
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
    // Constructor(s)
    // ----------------------------------------
    Texture();
    Texture(const TextureSpecification& spec);
    
    // Target type
    // ----------------------------------------
    virtual GLenum TextureTarget() const = 0;
    
    // Texture creation
    // ----------------------------------------
    virtual void CreateTexture(const void *data) = 0;
    
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
 * Utility functions related to texture operations.
 */
namespace utils {
/// @brief Namespace containing utility functions for texturing operations.
namespace Texturing {

/**
 * Get a shared pointer to a 1x1 white texture.
 *
 * This function returns a shared pointer to a 1x1 texture with a single white pixel.
 * If the texture has already been created, it will be reused to avoid redundant texture creation.
 *
 * @tparam T The type of texture to create (e.g., 1D, 2D, or 3D).
 * @return A shared pointer to the 1x1 white texture.
 */
template <typename T>
inline std::shared_ptr<T>& WhiteTexture()
{
    // Static variable to hold the shared pointer to the texture
    static std::shared_ptr<T> texture;
    
    // Check if the texture has already been created
    if (texture)
        return texture;
    
    // Define the texture specifications
    TextureSpecification spec = TextureSpecification(TextureFormat::RGB8);
    spec.SetTextureSize(1, 1);
    spec.Wrap = TextureWrap::Repeat; // Set texture wrap mode to repeat
    
    // Define the color data for a single white pixel (R, G, B values)
    const unsigned char whitePixel[] = { 255, 255, 255 };
    
    // Create the 1x1 white texture using the specified data and specifications
    texture = std::make_shared<T>(whitePixel, spec);
    
    // Return the created texture
    return texture;
}

/**
 * Update the specifications of a texture resource based on width, height, channels, and extension.
 *
 * This function updates the specifications of a texture resource (`TextureSpecification`) based on the provided
 * width, height, channels, and extension information. It determines the texture format, wrap mode, filter mode,
 * and whether mipmaps are enabled based on the input data.
 *
 * @param spec The texture specification to be updated.
 * @param width The width of the texture.
 * @param height The height of the texture.
 * @param channels The number of color channels in the texture.
 * @param extension The file extension (e.g., ".hdr") to determine if the texture is HDR.
 */
inline void UpdateSpecsTextureResource(TextureSpecification& spec, const unsigned int width,
                                       const unsigned int height, const unsigned int channels,
                                       const std::string& extension = "")
{
    // Update width and height
    spec.Width = width;
    spec.Height = height;
    
    // Determine if the texture is HDR based on the file extension
    bool isHDR = (extension == ".hdr");
    
    // Define the format of the data to be used
    spec.Format = TextureFormat::None;
    if (!isHDR && channels == 4)
        spec.Format = TextureFormat::RGBA8;
    else if (!isHDR && channels == 3)
        spec.Format = TextureFormat::RGB8;
    else if (isHDR && channels == 3)
        spec.Format = TextureFormat::RGB16F;
    
    // Set default wrap mode based on HDR status
    if (spec.Wrap == TextureWrap::None)
        spec.Wrap = isHDR ? TextureWrap::ClampToEdge : TextureWrap::Repeat;
    
    // Set default filter mode
    if (spec.Filter == TextureFilter::None)
        spec.Filter = TextureFilter::Linear;
    
    // Enable mipmaps by default
    spec.MipMaps = true;
}

} // namespace Texturing
} // namespace utils
