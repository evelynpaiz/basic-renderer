#pragma once

#include "Common/Renderer/Buffer/BufferState.h"

#include <glm/glm.hpp>

/**
 * An abstract class representing a graphics context.
 *
 * The `GraphicsContext` class serves as an interface for interacting with
 * the underlying graphics API. It provides methods for initialization,
 * swapping buffers, and creating a context based on the specified window.
 */
class GraphicsContext
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Virtual destructor for proper cleanup.
    virtual ~GraphicsContext() = default;

    // Initialization
    // ----------------------------------------
    /// @brief Pure virtual function for initializing the graphics context.
    virtual void Init() = 0;
    static std::unique_ptr<GraphicsContext> Create(void* window);
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the graphics context instance.
    /// @return This graphics context.
    static GraphicsContext& Get() { return *s_Instance; }
    
    // Setter(s)
    // ----------------------------------------
    static void SetWindowHints();
    virtual void SetVerticalSync(bool enabled) = 0;
    
    // Clear
    // ----------------------------------------
    virtual void Clear(const BufferState& buffersActive = {}) = 0;
    virtual void Clear(const glm::vec4& color, const BufferState& buffersActive = {}) = 0;
    
    // Buffers
    // ----------------------------------------
    /// @brief Pure virtual function for swapping front and back buffers.
    virtual void SwapBuffers() = 0;
    
protected:
    // Constructor
    // ----------------------------------------
    GraphicsContext();
    
private:
    ///< Pointer to this graphics context.
    static GraphicsContext* s_Instance;
};
