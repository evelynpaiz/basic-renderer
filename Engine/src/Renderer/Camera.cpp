#include "Renderer/Camera.h"

#include "Core/Log.h"

/**
 * Generate a camera.
 *
 * @param width Viewport size (width).
 * @param height Viewport size (height).
 * @param near Distance to the near plane.
 * @param far Distance to the far plane.
 */
Camera::Camera(const int width, const int height, const float near, const float far)
    : m_Width(width), m_Height(height), m_NearPlane(near), m_FarPlane(far)
{}

/**
 * Get the camera resolution (width).
 *
 * @returns Viewport width.
 */
unsigned int Camera::GetWidth() const
{
    return m_Width;
}

/**
 * Get the camera resolution (height).
 *
 * @returns Viewport height.
 */
unsigned int Camera::GetHeight() const
{
    return m_Height;
}

/**
 * Get the camera aspect ratio.
 *
 * @returns The aspect ratio (width/height).
 */
float Camera::GetAspectRatio() const
{
    return (float)m_Width / (float)m_Height;
}

/**
 * Get the distance from the camera position to the near plane.
 *
 * @returns The near plane distance.
 */
float Camera::GetNearPlane() const
{
    return m_NearPlane;
}

/**
 * Get the distance from the camera position to the far plane.
 *
 * @returns The far plane distance.
 */
float Camera::GetFarPlane() const
{
    return m_FarPlane;
}

/**
 * Get the camera position (x, y, z).
 *
 * @returns The camera position coordinates.
 */
const glm::vec3& Camera::GetPosition() const
{
    return m_Position;
}

/**
 * Get the camera orientation (yaw, pitch, roll).
 *
 * @returns The camera rotation angles.
 */
const glm::vec3& Camera::GetRotation() const
{
    return m_Rotation;
}

/**
 * Get the camera view matrix (transformation from world space to view/camera space).
 *
 * @returns The view matrix.
 */
const glm::mat4& Camera::GetViewMatrix() const
{
    return m_ViewMatrix;
}

/**
 * Get the camera projection matrix (transformation from view/camera space to screen space).
 *
 * @returns The projection matrix.
 */
const glm::mat4& Camera::GetProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

/**
 * Change the camera resolution.
 *
 * @param width Viewport size (width).
 * @param height Viewport size (height).
 */
void Camera::SetViewportSize(const int width, const int height)
{
    // Check input values
    if (width <= 0 || height <= 0)
    {
        CORE_WARN("Attempted to rezize camera resolution to {0}, {1}", width, height);
        return;
    }

    // Define the new resolution value
    m_Width = width;
    m_Height = height;
    
    // Update the projetion matrix
    UpdateProjectionMatrix();
}

/**
 * Change the distance from the camera position to the near plane.
 *
 * @param nearPlane Distance to the near plane.
 */
void Camera::SetNearPlane(const float nearPlane)
{
    m_NearPlane = nearPlane;
    UpdateProjectionMatrix();
}

/**
 * Change the distance from the camera position to the far plane.
 *
 * @param farPlane Distance to the far plane.
 */
void Camera::SetFarPlane(const float farPlane)
{
    m_FarPlane = farPlane;
    UpdateProjectionMatrix();
}

/**
 * Change the camera position (x, y, z).
 *
 * @param position The camera center position.
 */
void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    UpdateViewMatrix();
}

/**
 * Change the camera orientation (yaw, pitch, roll).
 *
 * @param orientation The camera rotation angles.
 */
void Camera::SetRotation(const glm::vec3& rotation)
{
    m_Rotation = rotation;
    UpdateViewMatrix();
}

/**
 * Update the camera view matrix.
 */
void Camera::UpdateViewMatrix()
{}

/**
 * Update the camera projection matrix.
 */
void Camera::UpdateProjectionMatrix()
{}

/**
 * Update the camera matrices.
 */
void Camera::UpdateCameraMatrices()
{
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}
