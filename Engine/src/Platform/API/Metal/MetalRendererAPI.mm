#include "enginepch.h"
#include "Platform/Metal/MetalRendererAPI.h"

#include "Platform/Metal/MetalContext.h"
#include "Platform/Metal/MetalRendererUtils.h"

#include "Platform/Metal/Drawable/MetalDrawable.h"
#include "Platform/Metal/Buffer/MetalIndexBuffer.h"

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

/**
 * Initializes the Metal rendering API.
 *
 * This method handles the Metal-specific initialization procedures.
 */
void MetalRendererAPI::Init()
{}

/**
 * Clear the buffers to preset values.
 *
 * @param buffersActive State of the buffers.
 */
void MetalRendererAPI::Clear(const BufferState& buffersActive)
{
    Clear(glm::vec4(glm::vec4(0.0f)), buffersActive);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 * @param buffersActive State of the buffers.
 */
void MetalRendererAPI::Clear(const glm::vec4& color, const BufferState& buffersActive)
{
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    
    // Clear the buffer with the selected color
    context->Clear(color);
}

void MetalRendererAPI::Draw(const std::shared_ptr<Drawable>& drawable,
                            const PrimitiveType &primitive)
{
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    // Get the command encoder to encode rendering commands into the buffer
    id<MTLRenderCommandEncoder> encoder = reinterpret_cast<id<MTLRenderCommandEncoder>>(context->GetEncoder());
    
    // Bind the drawable object
    drawable->Bind();
    // Draw primitives
    auto metalIndexBuffer = std::dynamic_pointer_cast<MetalIndexBuffer>(drawable->GetIndexBuffer());
    CORE_ASSERT(metalIndexBuffer, "Invalid buffer cast - not a Metal index buffer!");
    
    id<MTLBuffer> indexBuffer = reinterpret_cast<id<MTLBuffer>>(metalIndexBuffer->GetBuffer());
    [encoder 
        drawIndexedPrimitives:utils::graphics::mtl::ToMetalPrimitive(primitive)
        indexCount:metalIndexBuffer->GetCount()
        indexType:MTLIndexTypeUInt32
        indexBuffer:indexBuffer
        indexBufferOffset:0];
}
 
/**
 * Set the viewport for rendering.
 *
 * @param x The x-coordinate of the lower-left corner of the viewport.
 * @param y The y-coordinate of the lower-left corner of the viewport.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 */
void MetalRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{}

/**
 * Set the depth buffer flag when rendering. If enabled, depth testing is enabled too.
 *
 * @param enable Enable or not the depth testing.
 */
void MetalRendererAPI::SetDepthTesting(bool enabled)
{}
