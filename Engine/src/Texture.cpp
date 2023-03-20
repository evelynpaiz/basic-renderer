#include "Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/**
 * Generate a texture from the input source file.
 *
 * @param filePath Texture file path.
 */
Texture::Texture(const std::filesystem::path& filePath)
    : m_FilePath(filePath)
{
    // Flip vertically the image (if needed)
    stbi_set_flip_vertically_on_load(m_Flip);
    
    // Load the image into our local buffer
    m_LocalBuffer = stbi_load(filePath.string().c_str(), &m_Width, &m_Height, &m_BPP, 0);
    
    // Generate a 2D texture
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Create the texture from the local buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Free memory
    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

/**
 * Delete the texture.
 */
Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

/**
 * Bind the texture.
 */
void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

/**
 * Unbind the texture.
 */
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
