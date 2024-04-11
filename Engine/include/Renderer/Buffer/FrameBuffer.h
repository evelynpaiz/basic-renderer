#pragma once

#include "Core/Library.h"
#include "Renderer/Texture/TextureUtils.h"
#include "Renderer/Texture/Texture.h"

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
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Define the size of the framebuffer (in pixels).
    /// @param width The framebuffer size (width).
    /// @param height The framebuffer size (height)
    void SetFrameBufferSize(unsigned int width, unsigned int height = 0,
                            unsigned int depth = 0)
    {
        Width = width;
        Height = height;
        Depth = depth;
    }
    
    // Framebuffer specification variables
    // ----------------------------------------
    ///< The size (width, height, and depth) in pixels.
    unsigned int Width = 0, Height = 0, Depth = 0;
    ///< The number of samples in the framebuffer texture attachments (only valid for 2D textures).
    int Samples = 1;
    ///< A flag indicating whether mipmaps should be created for the texture. 
    bool MipMaps = false;
    
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
    /// @brief Get the framebuffer configuration.
    /// @return The specifications of the framebuffer.
    const FrameBufferSpecification& GetSpec() const { return m_Spec; }
    
    /// @brief Get a specific framebuffer color attachment.
    /// @param index Color attachment index.
    /// @return The color attachment (texture reference).
    const std::shared_ptr<Texture>& GetColorAttachment(const unsigned int index) const
    {
        CORE_ASSERT(index >= 0 && index < m_ColorAttachments.size(),
                    "Trying to get color attachment out of scope!");
        return m_ColorAttachments[index];
    }
    /// @brief Get the framebuffer depth attachment.
    /// @return The depth attachment (texture reference).
    const std::shared_ptr<Texture>& GetDepthAttachment() const { return m_DepthAttachment; }
    
    /// @brief Get the active buffers in this framebuffer.
    /// @return The state of the color, depth and stencil buffers.
    BufferState GetActiveBuffers() const { return m_ActiveBuffers; }
    
    // Usage
    // ----------------------------------------
    void Bind() const;
    void BindForDrawAttachment(const unsigned int index) const;
    void BindForReadAttachment(const unsigned int index) const;
    void BindForDrawAttachmentCube(const unsigned int index, const unsigned int face,
                                   const unsigned int level = 0) const;
    void Unbind(const bool& genMipMaps = true) const;
    
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
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Retrieves pixel data from a color attachment of the framebuffer.
    /// @param index The index of the color attachment to retrieve data from.
    /// @return A vector containing the pixel data of the color attachment, with each channel.
    template <typename T>
    std::vector<T> GetAttachmentData(const unsigned int index)
    {
        auto& format = m_ColorAttachmentsSpec[index].Format;
        int channels = utils::OpenGL::TextureFormatToChannelNumber(format);
        
        // Ensure numChannels is within a valid range
        if (channels < 1 || channels > 4)
            CORE_ASSERT(false, "Invalid number of channels in the color attachment!");
        
        int stride = channels * m_Spec.Width;
        channels += (stride % 4) ? (4 - stride % 4) : 0;
        int bufferSize = stride * (m_Spec.Height > 0 ? m_Spec.Height : 1.0f);
        std::vector<T> buffer(bufferSize);

        BindForReadAttachment(index);
        glPixelStorei(GL_PACK_ALIGNMENT, channels);
        
        // TODO: Add support for all texture types (currently only supports 1D and 2D).
        // consider using maybe:
        //glGetTexImage(m_ColorAttachments[index]->TextureTarget(), 0,
        //              utils::OpenGL::TextureFormatToOpenGLBaseType(format),
        //              utils::OpenGL::TextureFormatToOpenGLDataType(format),
        //              buffer.data());
        
        glReadPixels(0, 0, m_Spec.Width, (m_Spec.Height > 0 ? m_Spec.Height : 1.0f),
                     utils::OpenGL::TextureFormatToOpenGLBaseType(format),
                     utils::OpenGL::TextureFormatToOpenGLDataType(format),
                     buffer.data());
        
        return buffer;
    }
    
    // Reset
    // ----------------------------------------
    void Resize(const unsigned int width, const unsigned int height = 0,
                const unsigned int depth = 0);
    void AdjustSampleCount(const unsigned int samples);
    
    // Save
    // ----------------------------------------
    void SaveAttachment(const unsigned int index, const std::filesystem::path& path);
    
private:
    // Destructor
    // ----------------------------------------
    void ReleaseFramebuffer();
    
    // Reset
    // ----------------------------------------
    void Invalidate();

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

/**
 * A library for managing framebuffers used in rendering.
 *
 * The `FrameBufferLibrary` class provides functionality to add, create, retrieve, and check for
 * the existence of framebuffers within the library. Framebuffers can be associated with unique names
 * for easy access.
 */
class FrameBufferLibrary : public Library<std::shared_ptr<FrameBuffer>>
{
public:
    /// @brief Loads a framebuffer and adds it to the library.
    /// @tparam Type The type of object to load.
    /// @tparam Args The types of arguments to forward to the object constructor.
    /// @param name The name to associate with the loaded object.
    /// @param args The arguments to forward to the object constructor.
    /// @return The framebuffer created.
    std::shared_ptr<FrameBuffer> Create(const std::string& name,
                                        FrameBufferSpecification spec)
    {
        auto framebuffer = std::make_shared<FrameBuffer>(spec);
        Add(name, framebuffer);
        return framebuffer;
    }
};
