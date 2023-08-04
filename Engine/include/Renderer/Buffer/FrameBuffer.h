#pragma once

#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/TextureUtils.h"

/**
 * Defines the specification for framebuffer attachments.
 *
 * The `AttachmentSpecification` struct provides a way to define the specifications for
 * framebuffer attachments. It allows specifying one or more `TextureSpecification`
 * objects for the attachments. These texture specifications define the format, size, and other
 * properties of the textures used as attachments in the framebuffer.
 */
struct AttachmentSpecification
{
    // Constructor(s)
    // ----------------------------------------
    /// @brief Define a framebuffer attachment with with no texture specifications.
    AttachmentSpecification() = default;
    /// @brief Define a framebuffer attachment with texture specifications.
    /// @param spec The texture specifications.
    AttachmentSpecification(std::initializer_list<TextureSpecification> spec) :
        TexturesSpec(spec)
    { }

    // Attachment specification variables
    // ----------------------------------------
    ///< The texture specifications for the framebuffer attachments.
    std::vector<TextureSpecification> TexturesSpec;
};

/**
 * Defines the specifications for a framebuffer.
 *
 * The `FrameBufferSpecification` struct provides a way to define the specifications for
 * a framebuffer. It includes the framebuffer size (width and height) and the number of samples
 * for multisampling, if applicable. The struct also includes an `AttachmentSpecification`
 * object that defines the texture specifications for the framebuffer attachments.
 */
struct FrameBufferSpecification
{
    // Constructor(s)
    // ----------------------------------------
    /// @brief Define a framebuffer with a default specification.
    FrameBufferSpecification() = default;
    /// @brief Define a framebuffer with a specification.
    /// @param width The framebuffer size (width).
    /// @param height The framebuffer size (height)
    /// @param samples The number of samples.
    FrameBufferSpecification(unsigned int width, unsigned int height, unsigned int samples = 1)
        : Width(width), Height(height), Samples(samples)
    {}
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Define the size of the framebuffer (in pixels).
    /// @param width The framebuffer size (width).
    /// @param height The framebuffer size (height)
    void SetFrameBufferSize(unsigned int width, unsigned int height)
    {
        Width = width;
        Height = height;
    }
    
    // Framebuffer specification variables
    // ----------------------------------------
    ///< The size (width and height) in pixels.
    unsigned int Width = 0, Height = 0;
    ///< The number of samples in the framebuffer texture attachments.
    int Samples = 1;
    
    ///< The properties for framebuffer texture attachments.
    AttachmentSpecification AttachmentsSpec;
};

/**
 * Represents a framebuffer object for rendering off-screen.
 *
 * The `FrameBuffer` class provides functionality to create, bind, unbind, and resize a framebuffer.
 * It allows users to attach color and depth textures to the framebuffer for rendering.
 *
 * Copying or moving `FrameBuffer` objects is disabled to ensure single ownership and prevent
 * unintended buffer duplication.
 */
class FrameBuffer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    FrameBuffer(const FrameBufferSpecification& spec);
    ~FrameBuffer();
    
    // Getters
    // ----------------------------------------
    /// @brief Get a specific framebuffer color attachment.
    /// @param index Color attachment index.
    /// @return The color attachment (texture reference).
    std::shared_ptr<Texture>& GetColorAttachment(const unsigned int index)
    {
        CORE_ASSERT(index >= 0 && index < m_ColorAttachments.size(),
                    "Trying to get color attachment out of scope!");
        return m_ColorAttachments[index];
    }
    /// @brief Get the framebuffer depth attachment.
    /// @return The depth attachment (texture reference).
    std::shared_ptr<Texture>& GetDepthAttachment() { return m_DepthAttachment; }
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void BindForDrawAttachment(const unsigned int index) const;
    void BindForReadAttachment(const unsigned int index) const;
    void Unbind() const;
    
    // Draw
    // ----------------------------------------
    void ClearAttachment(const unsigned int index, const int value);
    
    void BlitColorAttachment(const int width, const int height);
    void BlitDepthAttachment(const int width, const int height);
    
    // Reset
    // ----------------------------------------
    void Resize(const unsigned int width, const unsigned int height);
    void Invalidate();
    
    // Save
    // ----------------------------------------
    void SaveAttachment(const unsigned int index, const std::filesystem::path& path);
    
private:
    // Destructor
    // ----------------------------------------
    void ReleaseFramebuffer();

    // Framebuffer variables
    // ----------------------------------------
private:
    ///< ID of the framebuffer.
    unsigned int m_ID = 0;
    
    ///< Depth attachment.
    std::shared_ptr<Texture> m_DepthAttachment;
    ///< Color attachments.
    std::vector<std::shared_ptr<Texture>> m_ColorAttachments;
    
    ///< Framebuffer properties.
    FrameBufferSpecification m_Spec;
    ///< Color attachments specifications.
    std::vector<TextureSpecification> m_ColorAttachmentsSpec;
    ///< Depth attachment specification.
    TextureSpecification m_DepthAttachmentSpec = TextureFormat::None;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer(FrameBuffer&&) = delete;

    FrameBuffer& operator=(const FrameBuffer&) = delete;
    FrameBuffer& operator=(FrameBuffer&&) = delete;
};
