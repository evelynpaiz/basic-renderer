#include "enginepch.h"
#include "Renderer/Texture/Texture.h"

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/**
 * Generate a texture from the input source file.
 *
 * @param filePath Texture file path.
 * @param flip Fip the texture vertically.
 */
Texture::Texture(const std::filesystem::path& filePath, bool flip)
    : m_FilePath(filePath), m_Flip(flip)
{
    LoadFromFile(filePath);
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
 *
 * @param slot Texture slot position.
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

/**
 * Load the texture from an input (image) source file.
 *
 * @param filePath Texture file path.
 */
void Texture::LoadFromFile(const std::filesystem::path& filePath)
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
    m_Width = width;
    m_Height = height;
    m_Channels = channels;
    
    // Generate the 2D texture
    Generate2DTexture(data);
    
    // Free memory
    stbi_image_free(data);
}

/**
 * Generate a 2D texture from its loaded data.
 *
 * @param data Texture data.
 */
void Texture::Generate2DTexture(const void *data)
{
    // Define the format of the data to be used
    if (m_Channels == 4)
    {
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
    }
    else if (m_Channels == 3)
    {
        m_InternalFormat = GL_RGB8;
        m_DataFormat = GL_RGB;
    }
    
    CORE_ASSERT(m_InternalFormat & m_DataFormat,
                "Data format of " + m_FilePath.filename().string() + " not supported!");
    
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
    glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}
