#pragma once

#include "Common/Renderer/Texture/TextureCube.h"
#include "Platform/OpenGL/Texture/OpenGLTexture.h"

class OpenGLTextureCube : public TextureCube
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    OpenGLTextureCube();
    OpenGLTextureCube(const TextureSpecification& spec);
    
    OpenGLTextureCube(const void *data);
    OpenGLTextureCube(const std::vector<const void *>& data);
    OpenGLTextureCube(const void *data, const TextureSpecification& spec);
    OpenGLTextureCube(const std::vector<const void *>& data,
                      const TextureSpecification& spec);
    
    OpenGLTextureCube(const std::filesystem::path& directory,
                      const std::vector<std::string>& files, bool flip);
    OpenGLTextureCube(const std::filesystem::path& directory,
                      const std::vector<std::string>& files,
                      const TextureSpecification& spec,
                      bool flip);
    
    DEFINE_OPENGL_TEXTURE_DESTRUCTOR(TextureCube)
    
    // Usage
    // ----------------------------------------
    DEFINE_OPENGL_TEXTURE_BINDING_METHODS()
    
protected:
    DEFINE_OPENGL_TEXTURE_RESOURCE_METHODS()
    void CreateTexture(const std::vector<const void *> &data) override;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    DISABLE_COPY_AND_MOVE(OpenGLTextureCube);
};
