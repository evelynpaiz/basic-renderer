#include "enginepch.h"
#include "Renderer/Texture/Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

// --------------------------------------------
// Texture
// --------------------------------------------

/**
 * Create a base texture.
 */
Texture::Texture()
{
    glGenTextures(1, &m_ID);
}

/**
 * Create a texture from input data.
 *
 * @param data The texture data.
 */
Texture::Texture(const void *data)
    : Texture()
{
    CreateTexture(data);
}

/**
 * Create a base texture with specific properties.
 * 
 * @param spec The texture specifications.
 */
Texture::Texture(const TextureSpecification& spec)
    : m_Spec(spec)
{
    glGenTextures(1, &m_ID);
}

/**
 * Create a texture from input data and with specific properties.
 *
 * @param data The texture data.
 * @param spec The texture specifications.
 */
Texture::Texture(const void *data, const TextureSpecification& spec)
    : Texture(spec)
{
    CreateTexture(data);
}

/**
 * Delete the texture.
 */
Texture::~Texture()
{
    ReleaseTexture();
}

/**
 * Release the resources of the texture.
 */
void Texture::ReleaseTexture()
{
    if (this)
        glDeleteTextures(1, &m_ID);
}

/**
 * Bind the texture.
 */
void Texture::Bind() const
{
    glBindTexture(TextureTarget(), m_ID);
}

/**
 * Bind the texture to a specific texture unit.
 *
 * @param slot The texture unit slot to which the texture will be bound.
 */
void Texture::BindToTextureUnit(const unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    Bind();
}

/**
 * Unbind the texture.
 */
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

/**
 * Get the texture target based on the texture specification.
 *
 * @return The OpenGL texture target.
 */
GLenum Texture::TextureTarget() const
{
    return (GLenum)(m_Spec.Samples > 1 ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D);
}

/**
 * Create and configure the texture based on the texture specification and provided data.
 *
 * @param data The texture data. This can be nullptr if the texture is to be written.
 */
void Texture::CreateTexture(const void *data)
{
    // Bind the texture
    Bind();
    
    // For multisample textures, use glTexImage2DMultisample to create the texture
    if (m_Spec.Samples > 1)
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Spec.Samples,
                                utils::OpenGL::TextureFormatToOpenGLInternalType(m_Spec.Format),
                                m_Spec.Width, m_Spec.Height, GL_FALSE);
        return;
    }
    
    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, m_Spec.MipMaps));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, false));
    
    // Create the texture based on the format and data type
    if (utils::OpenGL::IsDepthFormat(m_Spec.Format))
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                       m_Spec.Width, m_Spec.Height);
        
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, utils::OpenGL::TextureFormatToOpenGLInternalType(m_Spec.Format),
                     m_Spec.Width, m_Spec.Height, 0, utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                     utils::OpenGL::TextureFormatToOpenGLDataType(m_Spec.Format), data);
    }
    
    // Generate mipmaps if specified
    if (m_Spec.MipMaps)
        glGenerateMipmap(GL_TEXTURE_2D);
    
}

// --------------------------------------------
// Texture 2D
// --------------------------------------------

/**
 * Generate a texture from the input source file.
 *
 * @param filePath Texture file path.
 * @param flip Fip the texture vertically.
 */
Texture2D::Texture2D(const std::filesystem::path& filePath, bool flip)
    : Texture(), m_FilePath(filePath), m_Flip(flip)
{
    LoadFromFile(filePath);
}

/**
 * Load the texture from an input (image) source file.
 *
 * @param filePath Texture file path.
 */
void Texture2D::LoadFromFile(const std::filesystem::path& filePath)
{
    // Flip vertically the image (if needed)
    stbi_set_flip_vertically_on_load(m_Flip);
    
    // Load the image into our local buffer
    int width, height, channels;
    unsigned char* data = stbi_load(filePath.string().c_str(), &width,
                                    &height, &channels, 0);
    
    // Verify that the image has been loaded correctly
    if (!data)
    {
        CORE_WARN("Failed to load: " + filePath.filename().string());
        return;
    }
    
    // Save the corresponding image information
    m_Spec.Width = width;
    m_Spec.Height = height;
    m_Channels = channels;
    
    // Generate the 2D texture
    GenerateTexture2D(data);
    
    // Free memory
    stbi_image_free(data);
}

/**
 * Generate a 2D texture from its loaded data.
 *
 * @param data Texture data.
 */
void Texture2D::GenerateTexture2D(const void *data)
{
    // Define the format of the data to be used
    if (m_Channels == 4)
        m_Spec.Format = TextureFormat::RGBA8;
    else if (m_Channels == 3)
        m_Spec.Format = TextureFormat::RGB8;
    
    if (m_Spec.Wrap == TextureWrap::None)
        m_Spec.Wrap = TextureWrap::Repeat;
    if (m_Spec.Filter == TextureFilter::None)
        m_Spec.Filter = TextureFilter::Linear;
    
    m_Spec.MipMaps = true;
    
    CORE_ASSERT((unsigned int)m_Spec.Format, "Data format of " + m_FilePath.filename().string() + " not supported!");
    
    // Generate a 2D texture
    Bind();
    CreateTexture(data);
    
    // Unbind the texture
    Unbind();
}
