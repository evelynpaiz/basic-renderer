#pragma once

#include "Engine.h"

/**
 * Sandbox application handler.
 */
class Sandbox : public Application
{
public:
    /// Constructor(s)/ Destructor
    Sandbox() = default;
    ~Sandbox() = default;
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Sandbox(const Sandbox&) = delete;
    Sandbox(Sandbox&&) = delete;
    /// Operators
    Sandbox& operator=(const Sandbox&) = delete;
    Sandbox& operator=(Sandbox&&) = delete;
};
