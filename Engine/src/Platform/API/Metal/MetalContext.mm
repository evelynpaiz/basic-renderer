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

    // Create a command queue for submitting rendering commands to the GPU
    m_State->Queue = [m_State->Device newCommandQueue];
    CORE_ASSERT(m_State->Queue, "Metal initialization failed: Could not create command queue!");

    // Log the Metal device name for debugging and information
    NSString *deviceName = [m_State->Device name];
    CORE_INFO("Using Metal ({0})", std::string([deviceName UTF8String]));

    // Create the Metal swap chain for presenting rendered frames to the screen
    m_State->SwapChain = [CAMetalLayer layer];
    m_State->SwapChain.device = m_State->Device; // Associate the swap chain with the Metal device
    m_State->SwapChain.opaque = YES;            // Set the swap chain to opaque (no alpha blending)

    // Get the NSWindow associated with the GLFW window handle for platform integration
    NSWindow* parentWindow = (NSWindow*)glfwGetCocoaWindow(m_WindowHandle);

    // Set up the swap chain as the layer for the window's content view
    parentWindow.contentView.layer = m_State->SwapChain;
    parentWindow.contentView.wantsLayer = YES; // Ensure the content view manages a Core Animation layer
    
    // Get the surface to output the render result
    m_State->Surface = [m_State->SwapChain nextDrawable];
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
 *  Swaps the front and back buffers. This presents the rendered frame to the screen.
 */
void MetalContext::SwapBuffers()
{
    // Get the surface to output the render result
    m_State->Surface = [m_State->SwapChain nextDrawable];
}

/**
 * Clear the buffers to preset values.
 *
 * @param buffersActive State of the buffers.
 */
void MetalContext::Clear(const BufferState& buffersActive)
{
    Clear(glm::vec4(glm::vec3(0.0f), 1.0f), buffersActive);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 * @param buffersActive State of the buffers.
 */
void MetalContext::Clear(const glm::vec4& color, const BufferState& buffersActive) 
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

    // Create a new command buffer. This buffer will hold the rendering commands
    id<MTLCommandBuffer> buffer = [m_State->Queue commandBuffer];

    // Create a render command encoder to encode rendering commands into the buffer
    id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];
    [encoder endEncoding];

    // Present the drawable to the screen. This schedules the presentation
    // of the current framebuffer (which has now been cleared) to the display.
    [buffer presentDrawable:m_State->Surface];

    // Commit the command buffer to the GPU. This sends the commands
    // (in this case, just the clear command) to be executed by the GPU
    [buffer commit];
}
