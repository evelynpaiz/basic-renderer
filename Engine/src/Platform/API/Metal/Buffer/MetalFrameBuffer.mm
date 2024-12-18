#include "enginepch.h"
#include "Platform/Metal/Buffer/MetalFrameBuffer.h"

#include "Platform/Metal/Texture/MetalTexture.h"

#include <stb_image_write.h>

#include <Metal/Metal.h>

/**
 * Holds the core Metal objects required for the framebuffer usage.
 */
struct MetalFrameBuffer::FrameState
{
    ///< The command buffer holding the rendering commands.
    id<MTLCommandBuffer> CommandBuffer;
    ///< The render command encoder to encode rendering commands into the buffer.
    id<MTLRenderCommandEncoder> Encoder;
};

/**
 * Generate a framebuffer.
 *
 * @param spec Framebuffer specifications.
 */
MetalFrameBuffer::MetalFrameBuffer(const FrameBufferSpecification& spec)
    : FrameBuffer(spec)
{
    // Define the framebuffer along with all its attachments
    Invalidate();
}

/**
 * Delete the framebuffer.
 */
MetalFrameBuffer::~MetalFrameBuffer()
{
    ReleaseFramebuffer();
}

/**
 * Define/re-define the framebuffer and its attachments.
 */
void MetalFrameBuffer::Invalidate()
{
    // Check if framebuffer already exists, if so, delete it
    ReleaseFramebuffer();
    
    // Define the framebuffer texture(s)
    DefineAttachments();
}
