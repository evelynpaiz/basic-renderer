#include "Renderer/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Core/Log.h"

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
 * Get the camera rotation angle in the y-axis.
 *
 * @returns Yaw angle (degrees).
 */
float PerspectiveCamera::GetYaw() const
{
    return m_Rotation.x;
}

/**
 * Get the camera rotation angle in the x-axis.
 *
 * @returns Pitch angle (degrees).
 */
float PerspectiveCamera::GetPitch() const
{
    return m_Rotation.y;
}

/**
 * Get the camera rotation angle in the z-axis.
 *
 * @returns Roll angle (degrees).
 */
float PerspectiveCamera::GetRoll() const
{
    return m_Rotation.z;
}

/**
 * Get the camera field of view.
 *
 * @returns Field of view angle (degrees).
 */
float PerspectiveCamera::GetFieldOfView() const
{
    return m_FieldOfView;
}

/**
 * Get the camera target coordinates (x, y, z).
 *
 * @returns Camera target.
 */
const glm::vec3& PerspectiveCamera::GetTarget() const
{
    return m_Target;
}

/**
 * Change the camera rotation in the y-axis.
 *
 * @param yaw The camera rotation angle.
 */
void PerspectiveCamera::SetYaw(const float yaw)
{
    m_Rotation.x = yaw;
    UpdateViewMatrix();
}

/**
 * Change the camera rotation in the x-axis.
 *
 * @param pitch The camera rotation angle.
 */
void PerspectiveCamera::SetPitch(const float pitch)
{
    m_Rotation.y = pitch;
    UpdateViewMatrix();
}

/**
 * Change the camera rotation in the z-axis.
 *
 * @param roll The camera rotation angle.
 */
void PerspectiveCamera::SetRoll(const float roll)
{
    m_Rotation.z = roll;
    UpdateViewMatrix();
}

/**
 * Change the camera field of view.
 *
 * @param fov The camera field of view (angle).
 */
void PerspectiveCamera::SetFieldOfView(const float fov)
{
    m_FieldOfView = fov;
}

/**
 * Change the camera target coordinates.
 *
 * @param roll The camera target (x, y, z).
 */
void PerspectiveCamera::SetTarget(const glm::vec3& target)
{
    m_Target = target;
    UpdateViewMatrix();
}

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
 * @returns The camera orientation.
 */
glm::quat PerspectiveCamera::GetOrientation() const
{
    return glm::quat(glm::radians(glm::vec3(-m_Rotation.y, -m_Rotation.x,
                                            -m_Rotation.z)));
}

/**
 * Get the camera's up direction vector.
 *
 * @returns The up vector.
 */
glm::vec3 PerspectiveCamera::GetUpDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * Get the camera's right direction vector.
 *
 * @returns The right vector.
 */
glm::vec3 PerspectiveCamera::GetRightDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

/**
 * Get the camera's forward direction vector.
 *
 * @returns The forward vector.
 */
glm::vec3 PerspectiveCamera::GetFowardDirection() const
{
    return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}
