#pragma once

#include "Renderer/Texture/TextureUtils.h"
#include "Renderer/Texture/Texture.h"

#include <filesystem>

/**
 * Represents a 1D texture that can be bound to geometry during rendering.
 *
 * The `Texture1D` class provides functionality to create, bind, unbind, and configure 1D textures.
 * 1D textures consist of a single line of texture data. These textures can be bound to specific texture
 * slots for use in a `Shader`.
 *
 * Copying or moving `Texture1D` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class Texture1D : public Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Texture1D();
    Texture1D(const void *data);
    Texture1D(const TextureSpecification& spec);
    Texture1D(const void *data, const TextureSpecification& spec);
    
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
    Texture1D(const Texture1D&) = delete;
    Texture1D(Texture1D&&) = delete;

    Texture1D& operator=(const Texture1D&) = delete;
    Texture1D& operator=(Texture1D&&) = delete;
};
