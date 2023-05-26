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
    // ----------------------------------------
    PerspectiveCamera(const int width, const int height, const float fov = 45.0f,
                      const float near = 0.1f, const float far = 100.0f);
    
    // Update
    // ----------------------------------------
    void OnUpdate(const float ts) const;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the camera rotation angle in the y-axis.
    /// @return Yaw angle (degrees).
    float GetYaw() const { return m_Rotation.x; }
    /// @brief Get the camera rotation angle in the x-axis.
    /// @return Pitch angle (degrees).
    float GetPitch() const { return m_Rotation.y; }
    /// @brief Get the camera rotation angle in the z-axis.
    /// @return Roll angle (degrees).
    float GetRoll() const { return m_Rotation.z; }
    /// @brief Get the camera field of view.
    /// @return Field of view angle (degrees).
    float GetFieldOfView() const { return m_FieldOfView; }
    /// @brief Get the camera target coordinates (x, y, z).
    /// @return Camera target.
    const glm::vec3& GetTarget() const { return m_Target; }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the camera rotation in the y-axis.
    /// @param yaw The camera rotation angle.
    void SetYaw(const float yaw)
    {
        m_Rotation.x = yaw;
        UpdateViewMatrix();
    }
    /// @brief Change the camera rotation in the x-axis.
    /// @param pitch The camera rotation angle.
    void SetPitch(const float pitch)
    {
        m_Rotation.y = pitch;
        UpdateViewMatrix();
    }
    /// @brief Change the camera rotation in the z-axis.
    /// @param roll The camera rotation angle.
    void SetRoll(const float roll)
    {
        m_Rotation.z = roll;
        UpdateViewMatrix();
    }
    /// @brief Change the camera field of view.
    /// @param fov The camera field of view (angle).
    void SetFieldOfView(const float fov)
    {
        m_FieldOfView = fov;
        UpdateProjectionMatrix();
    }
    /// @brief Change the camera target coordinates.
    /// @param target The camera target (x, y, z).
    void SetTarget(const glm::vec3& target)
    {
        m_Target = target;
        UpdateViewMatrix();
    }
    
protected:
    // Transformation matrices
    // ----------------------------------------
    void UpdateViewMatrix() override;
    void UpdateProjectionMatrix() override;
    
    // Calculations
    // ----------------------------------------
    glm::quat GetOrientation() const;
    glm::vec3 GetUpDirection() const;
    glm::vec3 GetRightDirection() const;
    glm::vec3 GetFowardDirection() const;
    
    // Perspective camera variables
    // ----------------------------------------
protected:
    ///< Camera field of view (angle in degrees).
    float m_FieldOfView;
    
    ///< Camera viewing target (x, y, z).
    glm::vec3 m_Target = glm::vec3(0.0f);
    ///< World up axis (default: y-axis).
    glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    // Constructors
    PerspectiveCamera(const PerspectiveCamera&) = delete;
    PerspectiveCamera(PerspectiveCamera&&) = delete;
    // Operators
    PerspectiveCamera& operator=(const PerspectiveCamera&) = delete;
    PerspectiveCamera& operator=(PerspectiveCamera&&) = delete;
};
