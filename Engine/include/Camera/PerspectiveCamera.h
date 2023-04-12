#pragma once

#include <glm/glm.hpp>

#include "Camera/Camera.h"

/**
 * Captures the scene and displays the resulting image in a viewport (camera abstraction).
 */
class PerspectiveCamera : public Camera
{
public:
    /// Constructor(s)/ Destructor
    PerspectiveCamera(const int width, const int height, const float fov = 45.0f,
                      const float near = 0.1f, const float far = 100.0f);
    /// Update
    void OnUpdate(const float ts) const;
    /// Gets
    float GetYaw() const;
    float GetPitch() const;
    float GetRoll() const;
    float GetFieldOfView() const;
    const glm::vec3& GetTarget() const;
    /// Sets
    void SetYaw(const float yaw);
    void SetPitch(const float pitch);
    void SetRoll(const float roll);
    void SetFieldOfView(const float fov);
    void SetTarget(const glm::vec3& target);
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    PerspectiveCamera(const PerspectiveCamera&) = delete;
    PerspectiveCamera(PerspectiveCamera&&) = delete;
    /// Operators
    PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;
    PerspectiveCamera& operator=(PerspectiveCamera&&) = delete;
    
protected:
    /// Transformation matrices
    void UpdateViewMatrix() override;
    void UpdateProjectionMatrix() override;
    /// Calculations
    glm::quat GetOrientation() const;
    glm::vec3 GetUpDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetFowardDirection() const;
    
protected:
    /// Camera field of view (angle in degrees)
    float m_FieldOfView;
    
    /// Camera viewing target (x, y, z)
    glm::vec3 m_Target = glm::vec3(0.0f);
    /// World up axis (default: y-axis)
    glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
};
