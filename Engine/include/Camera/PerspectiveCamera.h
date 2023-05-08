#pragma once

#include <glm/glm.hpp>

#include "Camera/Camera.h"

/**
 * Represents a perspective camera that captures the scene and displays it in a viewport.
 *
 * The `PerspectiveCamera`  class is a derived class of the Camera class, providing a perspective
 * projection for rendering. It inherits all the properties and functionality of the base Camera class and
 * adds additional methods to manipulate the camera's orientation and field of view. The camera's view
 * matrix and projection matrix are automatically updated when camera properties change.
 *
 * Copying or moving `PerspectiveCamera` objects is disabled to ensure single ownership and
 * prevent unintended camera duplication.
 */
class PerspectiveCamera : public Camera
{
public:
    // Constructor(s)/ Destructor
    PerspectiveCamera(const int width, const int height, const float fov = 45.0f,
                      const float near = 0.1f, const float far = 100.0f);
    // Update
    void OnUpdate(const float ts) const;
    // Get(s)
    float GetYaw() const;
    float GetPitch() const;
    float GetRoll() const;
    float GetFieldOfView() const;
    const glm::vec3& GetTarget() const;
    // Set(s)
    void SetYaw(const float yaw);
    void SetPitch(const float pitch);
    void SetRoll(const float roll);
    void SetFieldOfView(const float fov);
    void SetTarget(const glm::vec3& target);
    
protected:
    // Transformation matrices
    void UpdateViewMatrix() override;
    void UpdateProjectionMatrix() override;
    // Calculations
    glm::quat GetOrientation() const;
    glm::vec3 GetUpDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetFowardDirection() const;
    
// Remove the possibility of copying or moving this resource
public:
    // Constructors
    PerspectiveCamera(const PerspectiveCamera&) = delete;
    PerspectiveCamera(PerspectiveCamera&&) = delete;
    // Operators
    PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;
    PerspectiveCamera& operator=(PerspectiveCamera&&) = delete;
    
protected:
    ///< Camera field of view (angle in degrees).
    float m_FieldOfView;
    
    ///< Camera viewing target (x, y, z).
    glm::vec3 m_Target = glm::vec3(0.0f);
    ///< World up axis (default: y-axis).
    glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
};
