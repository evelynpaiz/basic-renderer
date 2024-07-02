#include "enginepch.h"
#include "Common/Renderer/RendererCommand.h"

std::unique_ptr<RendererAPI> RendererCommand::s_API = RendererAPI::Create();

/**
 * Initialize the renderer command manager by initializing the graphics API.
 */
void RendererCommand::Init()
{
    s_API->Init();
}

/**
 * Clear the buffers to preset values.
 *
 * @param buffersActive State of the buffers.
 */
void RendererCommand::Clear(const BufferState& buffersActive)
{
    s_API->Clear(buffersActive);
}

/**
 * Clear the buffers to preset values.
 *
 * @param color Background color.
 * @param buffersActive State of the buffers.
 */
void RendererCommand::Clear(const glm::vec4& color, const BufferState& buffersActive)
{
    s_API->Clear(color, buffersActive);
}

/**
 * Render primitives from a drawable object using the specified primitive type.
 *
 * @param drawable The drawable object containing the data for rendering.
 * @param primitive The type of primitive to be drawn (e.g., Points, Lines, Triangles).
 */
void RendererCommand::Draw(const std::shared_ptr<Drawable>& drawable,
                           const PrimitiveType &primitive)
{
    s_API->Draw(drawable, primitive);
}

/**
 * Set the viewport for rendering.
 *
 * @param x The x-coordinate of the lower-left corner of the viewport.
 * @param y The y-coordinate of the lower-left corner of the viewport.
 * @param width The width of the viewport.
 * @param height The height of the viewport.
 */
void RendererCommand::SetViewport(unsigned int x, unsigned int y,
                                  unsigned int width, unsigned int height)
{
    s_API->SetViewport(x, y, width, height);
}

/**
 * Set the depth buffer flag when rendering. If enabled, depth testing is enabled too.
 *
 * @param enable Enable or not the depth testing.
 */
void RendererCommand::SetDepthTesting(const bool enabled)
{
    s_API->SetDepthTesting(enabled);
}
