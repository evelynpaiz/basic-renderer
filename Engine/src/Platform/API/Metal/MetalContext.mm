#include "enginepch.h"
#include "Platform/Metal/MetalContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>

/**
 * Holds the core Metal objects required for rendering.
 */
struct MetalContext::MetalState {
    ///< The Metal device (GPU) used for rendering.
    id<MTLDevice> Device;
    
    ///< The command queue for submitting rendering commands to the GPU.
    id<MTLCommandQueue> Queue;
    ///< The command queue for resource-related operations (textures, etc.).
    id<MTLCommandQueue> ResourceQueue;
    
    ///< The command buffer holding the rendering commands.
    id<MTLCommandBuffer> CommandBuffer;
    ///< The render command encoder to encode rendering commands into the buffer.
    id<MTLRenderCommandEncoder> Encoder;
    
    ///< The Metal-backed layer that manages the presentation of rendered frames to the screen.
    CAMetalLayer* SwapChain;
    
    ///< Screen buffer.
    id<CAMetalDrawable> Surface;
};

/**
 *  Constructs a Metal context for rendering.
 *
 *  @param windowHandle The GLFW window handle to associate with this context.
 */
MetalContext::MetalContext(GLFWwindow* windowHandle)
    : GraphicsContext(), m_WindowHandle(windowHandle)
{
    CORE_ASSERT(windowHandle, "Window handle is null!");
}

/**
 * Initializes the Metal rendering context.
 */
void MetalContext::Init() 
{
    // Initialize the Metal state object for managing Metal resources
    m_State = std::make_shared<MetalState>();

    // Get the default system Metal device (GPU)
    m_State->Device = MTLCreateSystemDefaultDevice();
    CORE_ASSERT(m_State->Device, "Metal initialization failed: Could not get default Metal device!");

    // Create the command queue(s) for submitting rendering commands to the GPU
    m_State->Queue = [m_State->Device newCommandQueue];
    m_State->ResourceQueue = [m_State->Device newCommandQueue];
    CORE_ASSERT(m_State->Queue && m_State->ResourceQueue, "Metal initialization failed: Could not create command queue(s)!");

    // Display the Metal general information
    CORE_INFO("Using Metal:");
    NSString *deviceName = [m_State->Device name];
    CORE_INFO("  Device: {0}", std::string([deviceName UTF8String]));

    // Create the Metal swap chain for presenting rendered frames to the screen
    m_State->SwapChain = [CAMetalLayer layer];
    m_State->SwapChain.device = m_State->Device; // Associate the swap chain with the Metal device
    m_State->SwapChain.opaque = YES;             // Set the swap chain to opaque (no alpha blending)

    // Get the NSWindow associated with the GLFW window handle for platform integration
    NSWindow* parentWindow = (NSWindow*)glfwGetCocoaWindow(m_WindowHandle);

    // Set up the swap chain as the layer for the window's content view
    parentWindow.contentView.layer = m_State->SwapChain;
    parentWindow.contentView.wantsLayer = YES; // Ensure the content view manages a Core Animation layer
    
    // Get the surface to output the render result
    m_State->Surface = [m_State->SwapChain nextDrawable];
    // Clear the buffer for the next frame
    Clear();
}

/**
 * Get the default system Metal device (GPU).
 *
 * @return The metal device as a void pointer, or `nullptr` if the device was not found.
 */
void* MetalContext::GetDevice() const
{
    return reinterpret_cast<void*>(m_State->Device);
}

/**
 * @brief Get the command encoder associated with the Metal context.
 *
 * @return A pointer to the command encoder, or `nullptr` if no command queue is available.
 */
void* MetalContext::GetEncoder() const
{
    return reinterpret_cast<void*>(m_State->Encoder);
}

/**
 * @brief Get the command queue for resource-related operations.
 *
 * @return A pointer to the command queue, or `nullptr` if no command queue is available.
 */
void* MetalContext::GetResourceQueue() const
{
    return reinterpret_cast<void*>(m_State->ResourceQueue);
}

/**
 *  Sets the window hints required for a Metal context.
 *
 *  This is a static function that should be called *before*
 *  creating the GLFW window to ensure a Metal-compatible
 *  context is created.
 */
void MetalContext::SetWindowHints()
{
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

/**
 * Define if the window's buffer swap will be synchronized with the vertical
 * refresh rate of the monitor.
 *
 * @param enabled Enable or not the vertical synchronization.
 */
void MetalContext::SetVerticalSync(bool enabled)
{
    // Make sure the swap chain has been initialized
    if (!m_State->SwapChain) {
        CORE_WARN("MetalContext::SetVerticalSync() called before swap chain initialization!");
        return;
    }
    
    // Set the vertical synchronization
    BOOL objcEnabled = enabled ? YES : NO;
    [m_State->SwapChain setPresentsWithTransaction: !objcEnabled];
}

/**
 * Clears the current render pass with the specified color.
 *
 * @param color The color to clear the render pass with.
 */
void MetalContext::Clear(const glm::vec4& color)
{
    // Define the clear color using the provided color
    MTLClearColor clearColor = MTLClearColorMake(color.r, color.g, color.b, color.a);
    
    // Create a render pass descriptor (defines how the render pass should be performed)
    MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
    
    // Configure the color attachment
    pass.colorAttachments[0].clearColor = clearColor;            // Set the clear color for this attachment
    pass.colorAttachments[0].loadAction  = MTLLoadActionClear;   // Clear the attachment to the clear color at the start
    pass.colorAttachments[0].storeAction = MTLStoreActionStore;  // Store the rendered results in the attachment
    pass.colorAttachments[0].texture = m_State->Surface.texture; // Specify the texture to use for this attachment

    // Create the new command buffer(s) for the next frame
    m_State->CommandBuffer = [m_State->Queue commandBuffer];
    
    // Create the render command encoder(s) to encode rendering commands into the buffer
    m_State->Encoder = [m_State->CommandBuffer renderCommandEncoderWithDescriptor:pass];
}

/**
 *  Swaps the front and back buffers. This presents the rendered frame to the screen.
 */
void MetalContext::SwapBuffers()
{
    // End encoding in the command encoder
    [m_State->Encoder endEncoding];
    
    // Present the drawable to the screen. This schedules the presentation
    // of the current framebuffer to the display
    [m_State->CommandBuffer presentDrawable:m_State->Surface];
    
    // Commit the command buffer. This submits all the commands in the buffer
    // for execution by the GPU
    [m_State->CommandBuffer commit];

    // Get the next drawable for the next frame
    m_State->Surface = [m_State->SwapChain nextDrawable];
}
