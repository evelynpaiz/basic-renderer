#pragma once

#include "Renderer/Texture/Texture.h"
#include "Renderer/Texture/TextureUtils.h"

/**
 * Structure to represent the state of color, depth, and stencil buffers.
 */
struct BufferState
{
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a buffer state with predefined buffer activation states.
    /// @param color Whether the color buffer is active (default: true).
    /// @param depth Whether the depth buffer is active (default: false).
    /// @param stencil Whether the stencil buffer is active (default: false).
    BufferState(bool color = true, bool depth = false, bool stencil = false)
        : colorBufferActive(color), depthBufferActive(depth), stencilBufferActive(stencil)
    {}
    
    // Buffer state variables
    // ----------------------------------------
    bool colorBufferActive;     ///< Indicates whether the color buffer is active.
    bool depthBufferActive;     ///< Indicates whether the depth buffer is active.
    bool stencilBufferActive;   ///< Indicates whether the stencil buffer is active.
};

namespace utils { namespace OpenGL
{

/**
 * Convert the buffers state to its corresponding OpenGL mask.
 *
 * @param buffersActive State of the buffers.
 *
 * @return Bitwise OR of masks that indicate the buffers to be cleared.
 */
inline GLbitfield BufferStateToOpenGLMask(const BufferState& buffersActive)
{
    GLbitfield mask = 0;
    if (buffersActive.colorBufferActive)
        mask |= GL_COLOR_BUFFER_BIT;
    if (buffersActive.depthBufferActive)
        mask |= GL_DEPTH_BUFFER_BIT;
    if (buffersActive.stencilBufferActive)
        mask |= GL_STENCIL_BUFFER_BIT;
    
    return mask;
}

} // namespace OpenGL
} // namespace utils

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
    
    /// @brief Get the active buffers in this framebuffer.
    /// @return The state of the color, depth and stencil buffers.
    BufferState GetActiveBuffers() const { return m_ActiveBuffers; }
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void BindForDrawAttachment(const unsigned int index) const;
    void BindForReadAttachment(const unsigned int index) const;
    void Unbind() const;
    
    // Draw
    // ----------------------------------------
    void ClearAttachment(const unsigned int index, const int value);
    
    // Blit
    // ----------------------------------------
    static void Blit(const std::shared_ptr<FrameBuffer>& src,
                     const std::shared_ptr<FrameBuffer>& dst,
                     const TextureFilter& filter = TextureFilter::Nearest,
                     const BufferState& buffersActive = {});
    static void BlitColorAttachments(const std::shared_ptr<FrameBuffer>& src,
                                     const std::shared_ptr<FrameBuffer>& dst,
                                     const unsigned int srcIndex, const unsigned int dstIndex,
                                     const TextureFilter& filter = TextureFilter::Nearest);
    
    // Reset
    // ----------------------------------------
    void Resize(const unsigned int width, const unsigned int height);
    void AdjustSampleCount(const unsigned int samples);
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
    
    ///< The states active in the framebuffer.
    BufferState m_ActiveBuffers = { false, false, false };
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer(FrameBuffer&&) = delete;

    FrameBuffer& operator=(const FrameBuffer&) = delete;
    FrameBuffer& operator=(FrameBuffer&&) = delete;
};
