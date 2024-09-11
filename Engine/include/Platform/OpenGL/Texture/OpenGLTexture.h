#pragma once

#include "Common/Renderer/Texture/TextureUtils.h"

/**
 * Provides a static interface for common OpenGL texture operations.
 *
 * This class encapsulates low-level OpenGL functions related to texture management. It offers
 * a simplified way to perform operations like creation, binding, unbinding, and deletion of texture
 * objects.
 *
 * @note `OpenGLTexture` is a non-instantiable utility class. All its members are static, and
 * it's not intended to be subclassed.
 */
class OpenGLTexture
{
public:
    // Texture Creator
    // ----------------------------------------
    static void GLCreate(uint32_t& ID);
    // Texture Destructor
    // ----------------------------------------
    static void GLRelease(uint32_t& ID);
    
    // Texture Usage
    // ----------------------------------------
    static void GLBind(uint32_t ID, TextureType type);
    static void GLBindToTextureUnit(uint32_t ID, TextureType type,
                                    uint32_t slot);
    static void GLUnbind(TextureType type);
    
    // Disable the creation of this resource
    // ----------------------------------------
public:
    OpenGLTexture() = delete;
};

// Destructor
// ----------------------------------------
#define DEFINE_OPENGL_TEXTURE_DESTRUCTOR(TextureType)\
    /** @brief Destructor to release the OpenGL texture resource. */\
    ~OpenGL##TextureType() override { ReleaseTexture(); }

// Usage
// ----------------------------------------
#define DEFINE_OPENGL_TEXTURE_BINDING_METHODS()\
    /** @brief Binds the texture to the active texture unit. */\
    void Bind() const override\
    {\
        OpenGLTexture::GLBind(m_ID, m_Spec.Type);\
    }\
    /** @brief Binds the texture to a specific texture unit. */\
    /** @param slot The index of the texture unit to bind to. */\
    void BindToTextureUnit(uint32_t slot) const override\
    {\
        OpenGLTexture::GLBindToTextureUnit(m_ID, m_Spec.Type, slot);\
    }\
    /** @brief Unbinds the texture from the active texture unit. */\
    void Unbind() const override\
    {\
        OpenGLTexture::GLUnbind(m_Spec.Type);\
    }

// Creation & Release
// ----------------------------------------
#define DEFINE_OPENGL_TEXTURE_RESOURCE_METHODS()\
    /** @brief Releases the underlying OpenGL texture resource. */\
    void ReleaseTexture() override\
    {\
        if (this)\
            OpenGLTexture::GLRelease(m_ID);\
    }\
    /** @brief Creates the OpenGL texture. */\
    void CreateTexture(const void* data) override;
