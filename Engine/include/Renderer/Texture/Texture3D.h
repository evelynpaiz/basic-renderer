#pragma once

#include "Renderer/Texture/TextureUtils.h"
#include "Renderer/Texture/Texture.h"

#include <filesystem>

/**
 * Represents a 3D texture that can be bound to geometry during rendering.
 *
 * The `Texture3D` class provides functionality to create, bind, unbind, and configure 3D textures.
 * 3D textures consist of a volume with texture data. These textures can
 * be bound to specific texture slots for use in a `Shader`.
 *
 * Copying or moving `Texture3D` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class Texture3D : public Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture3D();
    Texture3D(const void *data);
    Texture3D(const TextureSpecification& spec);
    Texture3D(const void *data, const TextureSpecification& spec);
    
protected:
    // Target type
    // ----------------------------------------
    GLenum TextureTarget() const override;
    
    // Texture creation
    // ----------------------------------------
    void CreateTexture(const void *data) override;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Texture3D(const Texture3D&) = delete;
    Texture3D(Texture3D&&) = delete;

    Texture3D& operator=(const Texture3D&) = delete;
    Texture3D& operator=(Texture3D&&) = delete;
};
