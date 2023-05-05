#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include "Engine.h"
#include "Sandbox.h"

/**
 * Main function.
 */

int main()
{
    // Initialize the logging system
    Log::Init();
    
    // Create the application
    auto application = std::make_unique<Sandbox>("Basic 3D Renderer", 800, 600);
    application->Run();
}
