#pragma once

/**
 * Rendering application handler.
 */
class Application
{
public:
    /// Constructor(s)/ Destructor
    Application() = default;
    virtual ~Application() = default;
    /// Run
    void Run();
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    /// Operators
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
};
