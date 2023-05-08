#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include "Engine.h"
#include "Viewer.h"

/**
 * Entry point of the application.
 *
 * The `main` function serves as the entry point of the application. It initializes the logging system,
 * creates an instance of the Viewer application and runs it.
 *
 * @return An integer indicating the exit status of the application.
 */
int main()
{
    // Initialize the logging system
    Log::Init();
    
    // Create the application
    auto application = std::make_unique<Viewer>("3D Viewer", 800, 600);
    application->Run();
}
