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
