#pragma once

#include <filesystem>

/**
 * An image used to add details to an rendered geometry.
 */
class Texture {
public:
    /// Constructors/Destructor
    Texture(const std::filesystem::path& filePath);
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
    /// Path to the file
    std::filesystem::path m_FilePath;
    /// Local storage of the texture
    unsigned char* m_LocalBuffer = nullptr;
    /// ID of the texture
    unsigned int m_ID = 0;

    /// Size (width and height)
    int m_Width = 0, m_Height = 0;
    /// Bits per pixel
    int m_BPP = 0;
    
    /// Texture flipping
    bool m_Flip = true;
};
