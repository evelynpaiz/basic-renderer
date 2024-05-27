#include "enginepch.h"
#include "Common/Renderer/Texture/Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/**
 * Create a base texture.
 */
Texture::Texture()
{
    glGenTextures(1, &m_ID);
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
    glBindTexture(TextureTarget(), 0);
}
