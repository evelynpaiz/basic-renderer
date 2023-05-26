#pragma once

#include <glm/glm.hpp>

/**
 * Represents a camera that captures the scene and displays it in a viewport.
 *
 * The `Camera` class provides an abstraction for a camera in a rendering engine. It captures the scene
 * and provides methods to access and manipulate camera properties. The camera's view matrix and
 * projection matrix are automatically updated when camera properties change.
 *
 * Copying or moving `Camera` objects is disabled to ensure single ownership and prevent unintended
 * camera duplication.
 */
class Camera
{
public:
    // Destructor
    // ----------------------------------------
    /// @brief Delete the camera.
    virtual ~Camera() = default;
    
    // Getter(s)
    // ----------------------------------------
    /// @brief Get the camera resolution (width).
    /// @return Viewport width.
    unsigned int GetWidth() const { return m_Width; }
    /// @brief Get the camera resolution (height).
    /// @return Viewport height.
    unsigned int GetHeight() const { return m_Height; }
    /// @brief Get the camera aspect ratio.
    /// @return The aspect ratio (width/height).
    float GetAspectRatio() const
    {
        return (float)m_Width / (float)m_Height;
    }
    /// @brief Get the distance from the camera position to the near plane.
    /// @return The near plane distance.
    float GetNearPlane() const { return m_NearPlane; }
    /// @brief Get the distance from the camera position to the far plane.
    /// @return The far plane distance.
    float GetFarPlane() const { return m_FarPlane; }
    
    /// @brief Get the camera position (x, y, z).
    /// @return The camera position coordinates.
    const glm::vec3& GetPosition() const { return m_Position; }
    /// @brief Get the camera orientation (yaw, pitch, roll).
    /// @return The camera rotation angles.
    const glm::vec3& GetRotation() const { return m_Rotation; }
    
    /// @brief Get the camera view matrix (transformation from world space to view/camera space).
    /// @return The view matrix.
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    /// @brief Get the camera projection matrix (transformation from view/camera space to screen space).
    /// @return The projection matrix.
    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Change the camera resolution.
    /// @param width Viewport size (width).
    /// @param height Viewport size (height).
    void SetViewportSize(const int width, const int height)
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
    /// @brief Change the distance from the camera position to the near plane.
    /// @param nearPlane Distance to the near plane.
    void SetNearPlane(const float nearPlane)
    {
        m_NearPlane = nearPlane;
        UpdateProjectionMatrix();
    }
    /// @brief Change the distance from the camera position to the far plane.
    /// @param farPlane Distance to the far plane.
    void SetFarPlane(const float farPlane)
    {
        m_FarPlane = farPlane;
        UpdateProjectionMatrix();
    }
    
    /// @brief Change the camera position (x, y, z).
    /// @param position The camera center position.
    void SetPosition(const glm::vec3& position)
    {
        m_Position = position;
        UpdateViewMatrix();
    }
    /// @brief Change the camera orientation (yaw, pitch, roll).
    /// @param orientation The camera rotation angles.
    void SetRotation(const glm::vec3& rotation)
    {
        m_Rotation = rotation;
        UpdateViewMatrix();
    }
    
protected:
    // Constructor(s)
    // ----------------------------------------
    /// @brief Generate a camera.
    /// @param width Viewport size (width).
    /// @param height Viewport size (height).
    /// @param near Distance to the near plane.
    /// @param far Distance to the far plane.
    Camera(const int width, const int height, const float near,
           const float far)
        : m_Width(width), m_Height(height), m_NearPlane(near),
        m_FarPlane(far)
    {}
    
    // Transformation matrices
    // ----------------------------------------
    /// @brief Update the camera view matrix.
    virtual void UpdateViewMatrix() {}
    /// @brief Update the camera projection matrix.
    virtual void UpdateProjectionMatrix() {}
    /// @brief Update the camera matrices.
    void UpdateCameraMatrices()
    {
        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }
    
    // Camera variables
    // ----------------------------------------
protected:
    ///< Camera resolution.
    unsigned int m_Width, m_Height;
    
    ///< Distance to near and far plane.
    float m_NearPlane, m_FarPlane;
    
    ///< Camera position (x, y, z).
    glm::vec3 m_Position = glm::vec3(0.0f);
    /// Camera orientation (yaw, pitch and roll angles).
    glm::vec3 m_Rotation = glm::vec3(0.0f);
    
    ///< View matrix.
    glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
    ///< Projection matrix.
    glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
    
    // Disable the copying or moving of this resource
    // ----------------------------------------
public:
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;

    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) = delete;
};
