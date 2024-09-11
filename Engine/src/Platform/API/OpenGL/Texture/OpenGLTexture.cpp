#include "enginepch.h"
#include "Platform/OpenGL/Texture/OpenGLTexture.h"

#include "Platform/OpenGL/Texture/OpenGLTextureUtils.h"

#include <GL/glew.h>

/**
 * Generate an new OpenGL texture.
 */
void OpenGLTexture::GLCreate(uint32_t& ID)
{
    glGenTextures(1, &ID);
}

/**
 * Deletes an OpenGL texture.
 */
void OpenGLTexture::GLRelease(uint32_t& ID)
{
    glDeleteTextures(1, &ID);
}

/**
 * Binds a texture to the active texture unit.
 *
 * @param ID   The ID of the texture object to bind.
 * @param type The type of the texture (e.g., `TextureType::TEXTURE2D`).
 */
void OpenGLTexture::GLBind(uint32_t ID, TextureType type)
{
    glBindTexture(utils::textures::gl::ToOpenGLTextureTarget(type), ID);
}

/**
 * Binds a texture to a specific texture unit.
 *
 * @param ID   The ID of the texture object to bind.
 * @param type The type of the texture.
 * @param slot The index of the texture unit to bind to.
 */
void OpenGLTexture::GLBindToTextureUnit(uint32_t ID, TextureType type,
                                        uint32_t slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    GLBind(ID, type);
}

/**
 * Unbinds the texture from the active texture unit.
 *
 * @param type The type of the texture to unbind.
 */
void OpenGLTexture::GLUnbind(TextureType type)
{
    glBindTexture(utils::textures::gl::ToOpenGLTextureTarget(type), 0);
}
