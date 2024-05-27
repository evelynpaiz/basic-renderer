#pragma once

#include "Common/Renderer/RendererAPI.h"

/**
 * Concrete implementation of the RendererAPI interface for Metal.
 *
 * The `MetalRendererAPI` class implements the `RendererAPI` abstract methods
 * specifically for the Metal rendering API.
 */
class MetalRendererAPI : public RendererAPI
{
public:
    // Initialization
    // ----------------------------------------
    void Init() override;
};
