#include "enginepch.h"
#include "Platform/Metal/Buffer/MetalIndexBuffer.h"

#include "Platform/Metal/MetalContext.h"

#include <Metal/Metal.h>

/**
 * Generate an index buffer and link it to the input indices.
 *
 * @param indices Index information for the vertices.
 * @param count Number of indices.
 */
MetalIndexBuffer::MetalIndexBuffer(const uint32_t *indices,
                                   const uint32_t count)
    : IndexBuffer(count)
{
    // Get the Metal graphics context
    MetalContext* context = dynamic_cast<MetalContext*>(&GraphicsContext::Get());
    CORE_ASSERT(context, "Graphic context is not Metal!");
    // Get the Metal device from the context
    id<MTLDevice> device = reinterpret_cast<id<MTLDevice>>(context->GetDevice());
    
    // Calculate the length of the buffer in bytes
    NSUInteger length = count * sizeof(uint32_t);
    
    // Create the Metal buffer
    id<MTLBuffer> buffer = [device 
                            newBufferWithBytes:indices
                            length:length
                            options:MTLResourceStorageModeShared];
    m_Buffer = reinterpret_cast<void*>(buffer);
}