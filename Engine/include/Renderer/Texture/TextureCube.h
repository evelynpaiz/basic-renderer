#pragma once

#include "Renderer/Texture/TextureUtils.h"
#include "Renderer/Texture/Texture.h"

#include <filesystem>

/**
 * Represents a cube texture that can be bound to geometry during rendering.
 *
 * The `TextureCube` class provides functionality to create, bind, unbind, and configure cube textures.
 * Cube textures consist of six faces, each with its own texture data. These textures can
 * be bound to specific texture slots for use in a `Shader`.
 *
 * Copying or moving `TextureCube` objects is disabled to ensure single ownership and prevent
 * unintended texture duplication.
 */
class TextureCube : public Texture
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    TextureCube();
    TextureCube(const void *data);
    TextureCube(const std::vector<const void *>& data);
    TextureCube(const TextureSpecification& spec);
    TextureCube(const void *data, const TextureSpecification& spec);
    TextureCube(const std::vector<const void *>& data, const TextureSpecification& spec);
    
protected:
    // Target type
    // ----------------------------------------
    GLenum TextureTarget() const override;
    
    // Texture creation
    // ----------------------------------------
    void CreateTexture(const void *data) override;
    void CreateTexture(const std::vector<const void *>& data);
    
    // Texture variables
    // ----------------------------------------
protected:
    ///< Textures properties.
    std::vector<TextureSpecification> m_CubeSpecs;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    TextureCube(const TextureCube&) = delete;
    TextureCube(TextureCube&&) = delete;

    TextureCube& operator=(const TextureCube&) = delete;
    TextureCube& operator=(TextureCube&&) = delete;
};

/**
 * Represents a cube texture loaded from individual files.
 *
 * The `Texture3DResource` class is a specialization of `Texture3D` that provides functionality
 * to load 3D textures from individual image files, one for each face of the cube. It is particularly
 * useful for creating environment maps and reflections.
 *
 * Copying or moving `Texture3DResource` objects is disabled to ensure single ownership and prevent
 * unintended resource duplication.
 */
class TextureCubeResource : public TextureCube
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    TextureCubeResource(const std::filesystem::path& directory,
                        const std::vector<std::string>& files, bool flip = true);
    
private:
    // Loading
    // ----------------------------------------
    void LoadFromFile(const std::filesystem::path& directory,
                      const std::vector<std::string>& files);
    
    // Texture variables
    // ----------------------------------------
private:
    ///< Path to the files.
    std::filesystem::path m_Directory;
    ///< File names.
    std::vector<std::string> m_Files;
    
    ///< Texture flipping.
    bool m_Flip;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    TextureCubeResource(const TextureCubeResource&) = delete;
    TextureCubeResource(TextureCubeResource&&) = delete;

    TextureCubeResource& operator=(const TextureCubeResource&) = delete;
    TextureCubeResource& operator=(TextureCubeResource&&) = delete;
};
