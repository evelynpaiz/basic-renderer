#include "enginepch.h"
#include "Camera/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

/**
 * Generate a perspective camera.
 *
 * @param width Viewport size (width).
 * @param height Viewport size (height).
 * @param fov Field of view angle (degrees).
 * @param near Distance to the near plane.
 * @param far Distance to the far plane.
 */
PerspectiveCamera::PerspectiveCamera(const int width, const int height,
    const float fov, const float near, const float far)
    : Camera(width, height, near, far), m_FieldOfView(fov)
{
    UpdateCameraMatrices();
}

/**
 * Update the camera.
 *
 * @param ts Time step in seconds (delta value).
 */
void PerspectiveCamera::OnUpdate(const float ts) const
{}

/**
 * Update the camera view matrix.
 */
void PerspectiveCamera::UpdateViewMatrix()
{
    // Get the camera current orientation
    glm::quat orientation = GetOrientation();
    // Compute the view matrix
    glm::mat4 view = glm::translate(glm::mat4(1.0f), m_Position)
        * glm::toMat4(orientation);
    m_ViewMatrix = glm::inverse(view);
}

/**
 * Update the camera projection matrix (perspective projection).
 */
void PerspectiveCamera::UpdateProjectionMatrix()
{
    m_ProjectionMatrix = glm::perspective(glm::radians(m_FieldOfView),
    GetAspectRatio(), m_NearPlane, m_FarPlane);
}

/**
 * Get the camera orientation defined as a quaternion.
 *
 * @return The camera orientation.
 */
glm::quat PerspectiveCamera::GetOrientation() const
{
    return glm::quat(glm::radians(glm::vec3(-m_Rotation.y, -m_Rotation.x,
                                            -m_Rotation.z)));
}

/**
 * Get the camera's up direction vector.
 *
 * @return The up vector.
 */
glm::vec3 PerspectiveCamera::GetUpDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * Get the camera's right direction vector.
 *
 * @return The right vector.
 */
glm::vec3 PerspectiveCamera::GetRightDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

/**
 * Get the camera's forward direction vector.
 *
 * @return The forward vector.
 */
glm::vec3 PerspectiveCamera::GetFowardDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}
