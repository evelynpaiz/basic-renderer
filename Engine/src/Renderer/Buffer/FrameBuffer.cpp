#include "enginepch.h"
#include "Renderer/Buffer/FrameBuffer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <GL/glew.h>

/**
 * Generate a framebuffer.
 *
 * @param spec Framebuffer specifications.
 */
FrameBuffer::FrameBuffer(const FrameBufferSpecification& spec)
    : m_Spec(spec)
{
    // Define the specification for each framebuffer attachment
    for (auto& spec : m_Spec.AttachmentsSpec.TexturesSpec)
    {
        // Update the information of each attachment
        spec.Width = m_Spec.Width;
        spec.Height = m_Spec.Height;
        spec.Samples = m_Spec.Samples;
        
        if (spec.Wrap == TextureWrap::None)
        {
            spec.Wrap = utils::OpenGL::IsDepthFormat(spec.Format) ?
            TextureWrap::ClampToBorder : TextureWrap::ClampToEdge;
        }
        if (spec.Filter == TextureFilter::None)
            spec.Filter = TextureFilter::Linear;
        
        // Depth attachment
        if (utils::OpenGL::IsDepthFormat(spec.Format))
            m_DepthAttachmentSpec = spec;
        // Color attachment
        else
            m_ColorAttachmentsSpec.emplace_back(spec);
    }
    
    // Define the framebuffer along with all its attachments
    Invalidate();
}

/**
 * Delete the framebuffer.
 */
FrameBuffer::~FrameBuffer()
{
    ReleaseFramebuffer();
}

/**
 * Bind the framebuffer.
 */
void FrameBuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    glViewport(0, 0, m_Spec.Width, m_Spec.Height);
}

/**
 * Bind the framebuffer to draw in a specific color attachment.
 * @param index The color attachment index.
 */
void FrameBuffer::BindForDrawAttachment(const unsigned int index) const
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID);
    glViewport(0, 0, m_Spec.Width, m_Spec.Height);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + index);
}

/**
 * Bind the framebuffer to read a specific color attachment.
 * @param index The color attachment index.
 */
void FrameBuffer::BindForReadAttachment(const unsigned int index) const
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ID);
    glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
}

/**
 * Unbind the vertex buffer.
 */
void FrameBuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * Clear a specific attachment belonging to this framebuffer (set a default value on it).
 *
 * @param index Attachment index to be cleared.
 * @param value Clear (reset) value.
 */
void FrameBuffer::ClearAttachment(const unsigned int index, const int value)
{
    // TODO: support other types of data. For the moment this is only for RED images.
    auto& spec = m_ColorAttachmentsSpec[index];
    glClearTexImage(m_ColorAttachments[index]->m_ID, 0,
                    utils::OpenGL::TextureFormatToOpenGLInternalType(spec.Format),
                    GL_INT, &value);
}

/**
 * Copy a color attachment to this framebuffer color attachment.
 *
 * @param width Input framebuffer width.
 * @param height Input famebuffer height.
 */
void FrameBuffer::BlitColorAttachment(const int width, const int height)
{
    glBlitFramebuffer(0, 0, width, height, 0, 0, m_Spec.Width,
            m_Spec.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

/**
 * Copy a depth attachment to this framebuffer depth attachment.
 *
 * @param width Input framebuffer width.
 * @param height Input famebuffer height.
 */
void FrameBuffer::BlitDepthAttachment(const int width, const int height)
{
    glBlitFramebuffer(0, 0, width, height, 0, 0, m_Spec.Width,
            m_Spec.Height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

/**
 * Reset the size of the framebuffer.
 *
 * @param width Framebuffer width.
 * @param height Famebuffer height.
 */
void FrameBuffer::Resize(const unsigned int width, const unsigned int height)
{
    // Update the size of the framebuffer
    m_Spec.SetFrameBufferSize(width, height);
    
    // Update the size for the framebuffer attachments
    for (auto& spec : m_Spec.AttachmentsSpec.TexturesSpec)
        spec.SetTextureSize(width, height);
    
    for (auto& spec : m_ColorAttachmentsSpec)
        spec.SetTextureSize(width, height);
    
    m_DepthAttachmentSpec.SetTextureSize(width, height);
    
    // Reset the framebuffer
    Invalidate();
}

/**
 * Define/re-define the framebuffer and its attachments.
 */
void FrameBuffer::Invalidate()
{
    // Check if framebuffer already exists, if so, delete it
    if (m_ID)
    {
        ReleaseFramebuffer();

        m_ColorAttachments.clear();
        m_DepthAttachment = 0;
    }
    
    // Create the framebuffer
    glGenFramebuffers(1, &m_ID);
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    
    // Color attachments
    if (!m_ColorAttachmentsSpec.empty())
    {
        // Based on the defined specifications, generate the corresponding attachments
        m_ColorAttachments.resize(m_ColorAttachmentsSpec.size());
    
        for (unsigned int i = 0; i < (unsigned int)m_ColorAttachments.size(); i++)
        {
            m_ColorAttachments[i] = std::make_shared<Texture>(m_ColorAttachmentsSpec[i]);
            TextureFormat &format = m_ColorAttachments[i]->m_Spec.Format;
            if(format != TextureFormat::None || !utils::OpenGL::IsDepthFormat(format))
            {
                m_ColorAttachments[i]->CreateTexture(nullptr);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, m_ColorAttachments[i]->TextureTarget(),
                                       m_ColorAttachments[i]->m_ID, 0);
            }
        }
    }
    
    // Depth attachment
    if(m_DepthAttachmentSpec.Format != TextureFormat::None &&
       utils::OpenGL::IsDepthFormat(m_DepthAttachmentSpec.Format))
    {
        m_DepthAttachment = std::make_shared<Texture>(m_DepthAttachmentSpec);
        m_DepthAttachment->CreateTexture(nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, utils::OpenGL::TextureFormatToOpenGLDepthType(m_DepthAttachment->m_Spec.Format),
                               m_DepthAttachment->TextureTarget(), m_DepthAttachment->m_ID, 0);
    }
    
    // Draw the color attachments
    if (m_ColorAttachments.size() > 1)
    {
        CORE_ASSERT(m_ColorAttachments.size() <= 4, "Using more than 4 color attachments in the Framebuffer!");
        GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
        glDrawBuffers((int)m_ColorAttachments.size(), buffers);
    }
    // Only depth-pass
    else if (m_ColorAttachments.empty())
    {
        glDrawBuffer(GL_NONE);
    }
    
    CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * Releases the resources associated with the framebuffer.
 */
void FrameBuffer::ReleaseFramebuffer()
{
    glDeleteFramebuffers(1, &m_ID);
    m_DepthAttachment->ReleaseTexture();
    for (auto& attachment : m_ColorAttachments)
        attachment->ReleaseTexture();
}

/**
 * Save a color attachment into an output file.
 *
 * Reference:
 * https://lencerf.github.io/post/2019-09-21-save-the-opengl-rendering-to-image-file/
 *
 * @param index Index to the color attachment to be saved.
 * @param path File path.
 */
void FrameBuffer::SaveAttachment(const unsigned int index, const std::filesystem::path &path)
{
    GLsizei nrChannels = 3;
    GLsizei stride = nrChannels * m_Spec.Width;
    stride += (stride % 4) ? (4 - stride % 4) : 0;
    GLsizei bufferSize = stride * m_Spec.Height;
    std::vector<char> buffer(bufferSize);

    BindForReadAttachment(index);
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glReadPixels(0, 0, m_Spec.Width, m_Spec.Height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());

    stbi_flip_vertically_on_write(true);
    stbi_write_png(path.string().c_str(), m_Spec.Width, m_Spec.Height, nrChannels, buffer.data(), stride);
}
