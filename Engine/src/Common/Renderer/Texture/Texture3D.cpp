#include "enginepch.h"
#include "Common/Renderer/Texture/Texture3D.h"

#include <GL/glew.h>
#include <stb_image.h>

// --------------------------------------------
// Texture (3D)
// --------------------------------------------

/**
 * Create a base 3D texture.
 */
Texture3D::Texture3D()
    : Texture()
{
    m_Spec.Type = TextureType::TEXTURE3D;
}

/**
 * Create a 3D texture from input data.
 *
 * @param data The data for the 3D texture.
 */
Texture3D::Texture3D(const void *data)
    : Texture3D()
{
    CreateTexture(data);
}

/**
 * Create a 3D base texture with specific properties.
 *
 * @param spec The texture specifications.
 */
Texture3D::Texture3D(const TextureSpecification& spec)
    : Texture(spec)
{
    m_Spec.Type = TextureType::TEXTURE3D;
}

/**
 * Create a 3D texture from input data and with specific properties.
 *
 * @param data The data for the 3D texture.
 * @param spec The texture specifications.
 */
Texture3D::Texture3D(const void *data, const TextureSpecification& spec)
    : Texture3D(spec)
{
    CreateTexture(data);
}

/**
 * Get the texture target based on the texture specification.
 *
 * @return The OpenGL texture target.
 */
GLenum Texture3D::TextureTarget() const
{
    return (GLenum)GL_TEXTURE_3D;
}

/**
 * Create and configure the texture based on the texture specification and provided data.
 *
 * @param data The texture data. This can be nullptr if the texture is to be written.
 */
void Texture3D::CreateTexture(const void *data)
{
    // Verify size of the 3D texture
    CORE_ASSERT(m_Spec.Width > 0 && m_Spec.Height > 0 && m_Spec.Depth > 0,
                "3D texture size not properly defined!");
    
    // Set texture wrapping and filtering parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R,
                    utils::OpenGL::TextureWrapToOpenGLType(m_Spec.Wrap));
    
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, m_Spec.MipMaps));
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER,
                    utils::OpenGL::TextureFilterToOpenGLType(m_Spec.Filter, false));
    
    // Create the texture based on the format and data type
    if (utils::OpenGL::IsDepthFormat(m_Spec.Format))
    {
        glTexStorage3D(GL_TEXTURE_3D, 1, utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                       m_Spec.Width, m_Spec.Height, m_Spec.Depth);
        
        float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_3D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }
    else
    {
        glTexImage3D(GL_TEXTURE_3D, 0, utils::OpenGL::TextureFormatToOpenGLInternalType(m_Spec.Format),
                     m_Spec.Width, m_Spec.Height, m_Spec.Depth, 0,
                     utils::OpenGL::TextureFormatToOpenGLBaseType(m_Spec.Format),
                     utils::OpenGL::TextureFormatToOpenGLDataType(m_Spec.Format), data);
    }
    
    // Generate mipmaps if specified
    if (m_Spec.MipMaps)
        glGenerateMipmap(GL_TEXTURE_3D);
    
    // Unbind the texture
    Unbind();
}
