#pragma once

#include <glm/glm.hpp>

/**
 * Captures the scene and displays the resulting image in a viewport (camera abstraction).
 */
class Camera
{
public:
    /// Destructor
    virtual ~Camera() = default;
    /// Gets
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    float GetAspectRatio() const;
    float GetNearPlane() const;
    float GetFarPlane() const;
    const glm::vec3& GetPosition() const;
    const glm::vec3& GetRotation() const;
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;
    /// Sets
    void SetViewportSize(const int width, const int height);
    void SetNearPlane(const float nearPlane);
    void SetFarPlane(const float farPlane);
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);
    
// Remove the possibility of copying this resource
public:
    /// Constructors
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    /// Operators
    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) = delete;
    
protected:
    /// Constructor(s)
    Camera(const int width, const int height, const float near,
           const float far);
    /// Transformation matrices
    virtual void UpdateViewMatrix();
    virtual void UpdateProjectionMatrix();
    void UpdateCameraMatrices();
    
protected:
    /// Camera resolution
    unsigned int m_Width, m_Height;
    
    /// Distance to near and far plane
    float m_NearPlane, m_FarPlane;
    
    /// Camera position (x, y, z)
    glm::vec3 m_Position = glm::vec3(0.0f);
    /// Camera orientation (yaw, pitch and roll angles)
    glm::vec3 m_Rotation = glm::vec3(0.0f);
    
    // View matrix
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    /// Projection matrix
    glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
};
