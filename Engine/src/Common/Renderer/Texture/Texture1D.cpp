#include "enginepch.h"
#include "Common/Renderer/Texture/Texture1D.h"

#include <GL/glew.h>
#include <stb_image.h>

// --------------------------------------------
// Texture (1D)
// --------------------------------------------

/**
 * Create a base 1D texture.
 */
Texture1D::Texture1D()
    : Texture()
{
    m_Spec.Type = TextureType::TEXTURE1D;
}

/**
 * Create a 1D texture from input data.
 *
 * @param data The data for the 1D texture.
 */
Texture1D::Texture1D(const void *data)
    : Texture1D()
{
    CreateTexture(data);
}

/**
 * Create a 1D base texture with specific properties.
 *
 * @param spec The texture specifications.
 */
Texture1D::Texture1D(const TextureSpecification& spec)
    : Texture(spec)
{
    m_Spec.Type = TextureType::TEXTURE1D;
}

/**
 * Create a 1D texture from input data and with specific properties.
 *
 * @param data The data for the 1D texture.
 * @param spec The texture specifications.
 */
Texture1D::Texture1D(const void *data, const TextureSpecification& spec)
    : Texture1D(spec)
{
    CreateTexture(data);
}

/**
 * Get the texture target based on the texture specification.
 *
 * @return The OpenGL texture target.
 */
GLenum Texture1D::TextureTarget() const
{
    return (GLenum)GL_TEXTURE_1D;
}

/**
 * Create and configure the texture based on the texture specification and provided data.
 *
 * @param data The texture data. This can be nullptr if the texture is to be written.
 */
void Texture1D::CreateTexture(const void *data)
{
    // Verify size of the 1D texture
    CORE_ASSERT(m_Spec.Width > 0, "1D texture size not properly defined!");
    
    // Bind the texture
    Bind();
    
    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, m_Spec.MipMaps));
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, false));
    
    // Create the texture based on the format and data type
    if (utils::OpenGL::IsDepthFormat(m_Spec.Format))
    {
        glTexStorage1D(GL_TEXTURE_1D, 1, utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                       m_Spec.Width);
        
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_1D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
    else
    {
        glTexImage1D(GL_TEXTURE_1D, 0, utils::OpenGL::TextureFormatToOpenGLInternalType(m_Spec.Format),
                     m_Spec.Width, 0, utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                     utils::OpenGL::TextureFormatToOpenGLDataType(m_Spec.Format), data);
    }
    
    // Generate mipmaps if specified
    if (m_Spec.MipMaps)
        glGenerateMipmap(GL_TEXTURE_1D);
    
    // Unbind the texture
    Unbind();
}
