#pragma once

#include <glm/glm.hpp>

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Material/Material.h"

/**
 * Represents the different data that a vertex may contain.
 */
struct VertexData
{
    glm::vec4 position;         ///< Vertex position.
    glm::vec2 uv;               ///< Texture coordinate.
};

/**
 * Represents a mesh used for rendering geometry.
 *
 * The `Mesh` class provides functionality to define and render geometry using vertex data.
 * It encapsulates the necessary information, such as vertex positions, texture coordinates, normals,
 * etc., required to render a mesh. The class supports operations such as loading mesh data, binding
 * vertex buffers, and rendering the mesh.
 */
class Mesh
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Mesh();
    Mesh(const std::vector<VertexData> &vertices,
         const std::vector<unsigned int> &indices);
    /// @brief Delete the mesh.
    ~Mesh() = default;
    
    void DefineMesh(const std::vector<VertexData> &vertices,
               const std::vector<unsigned int> &indices);
    
    // Setter(s)
    // ----------------------------------------
    /// @brief Sets the material for the mesh.
    /// @param material Material defining the surface of the mesh.
    void SetMaterial(const std::shared_ptr<Material>& material)
    {
        m_Material = material;
    }
    
    // Render
    // ----------------------------------------
    void DrawMesh(const glm::mat4& transform = glm::mat4(1.0f));
    
    // Mesh variables
    // ----------------------------------------
private:
    ///< Vertex data of the mesh.
    std::vector<VertexData> m_Vertices;
    ///< Index data of the mesh.
    std::vector<unsigned int> m_Indices;
    
    ///< Vertex array.
    std::shared_ptr<VertexArray> m_VertexArray;
    ///< Vertex buffer.
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    ///< Index buffer.
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    
    ///< Mesh material
    std::shared_ptr<Material> m_Material;
};
