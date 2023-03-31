#pragma once

#include <filesystem>

/**
 * An image used to add details to an rendered geometry.
 */
class Texture {
public:
    /// Constructors/Destructor
    Texture(const std::filesystem::path& filePath, bool flip = true);
    ~Texture();
    /// Usage
    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    /// Operators
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;
    
private:
  /// Loading
    void LoadFromFile(const std::filesystem::path& filePath);
    void Generate2DTexture(const void *data);
    
private:
    /// Path to the file
    std::filesystem::path m_FilePath;
    /// Texture flipping
    bool m_Flip;
    
    /// ID of the texture
    unsigned int m_ID = 0;

    /// Size (width and height)
    int m_Width = 0, m_Height = 0;
    /// Number of channels
    int m_Channels = 0;
    
    /// Format
    unsigned int m_InternalFormat = 0;
    unsigned int m_DataFormat = 0;
};
