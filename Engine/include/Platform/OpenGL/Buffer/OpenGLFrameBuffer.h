#pragma once

#include "Common/Renderer/Buffer/FrameBuffer.h"
// TODO: Remove
//#include "Platform/OpenGL/Texture/OpenGLTextureUtils.h"

class OpenGLFrameBuffer : public FrameBuffer
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    OpenGLFrameBuffer(const FrameBufferSpecification& spec);
    ~OpenGLFrameBuffer() override;
    
    // Getter(s)
    // ----------------------------------------
    std::vector<char> GetAttachmentData(const unsigned int index) override;
    
    // Usage
    // ----------------------------------------
    void Bind() const override;
    void BindForDrawAttachment(const unsigned int index) const override;
    void BindForReadAttachment(const unsigned int index) const override;
    void BindForDrawAttachmentCube(const unsigned int index, const unsigned int face,
                                   const unsigned int level = 0) const override;
    void Unbind(const bool& genMipMaps = true) const override;
    
    // Draw
    // ----------------------------------------
    void ClearAttachment(const unsigned int index, const int value) override;
    
    // Blit
    // ----------------------------------------
    static void Blit(const std::shared_ptr<OpenGLFrameBuffer>& src,
                     const std::shared_ptr<OpenGLFrameBuffer>& dst,
                     const TextureFilter& filter = TextureFilter::Nearest,
                     const BufferState& buffersActive = {});
    static void BlitColorAttachments(const std::shared_ptr<OpenGLFrameBuffer>& src,
                                     const std::shared_ptr<OpenGLFrameBuffer>& dst,
                                     const unsigned int srcIndex, const unsigned int dstIndex,
                                     const TextureFilter& filter = TextureFilter::Nearest);
    
    // Save
    // ----------------------------------------
    void SaveAttachment(const unsigned int index, 
                        const std::filesystem::path& path) override;
    
private:
    // Destructor
    // ----------------------------------------
    void ReleaseFramebuffer() override;
    
    // Reset
    // ----------------------------------------
    void Invalidate() override;

    // Framebuffer variables
    // ----------------------------------------
private:
    ///< ID of the framebuffer.
    uint32_t m_ID = 0;
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    DISABLE_COPY_AND_MOVE(OpenGLFrameBuffer);
};
