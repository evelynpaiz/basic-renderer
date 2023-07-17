#pragma once

#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include "Renderer/Material.h"

#include "Renderer/Renderer.h"

#include <glm/glm.hpp>

/**
 * Represents a mesh used for rendering geometry.
 *
 * The `Mesh` class provides functionality to define and render geometry using vertex data.
 * It encapsulates the necessary information, such as vertex positions, texture coordinates, normals,
 * etc., required to render a mesh. The class supports operations such as loading mesh data, binding
 * vertex buffers, and rendering the mesh.
 */
template<typename VertexData>
class Mesh
{
public:
    // Constructor(s)/Destructor
    // ----------------------------------------
    Mesh();
    Mesh(const std::vector<VertexData> &vertices,
         const std::vector<unsigned int> &indices,
         const BufferLayout &layout);
    /// @brief Delete the mesh.
    ~Mesh() = default;
    
    void DefineMesh(const std::vector<VertexData> &vertices,
                    const std::vector<unsigned int> &indices,
                    const BufferLayout &layout);
    
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

/**
 * Generate an empty mesh.
 */
template<typename VertexData>
Mesh<VertexData>::Mesh()
{
    m_VertexArray = std::make_shared<VertexArray>();
}

/**
 * Generate a mesh from a set of vertices and incides defined.
 *
 * @param vertices The vertex data of the mesh.
 * @param indices The index data of the mesh.
 */
template<typename VertexData>
Mesh<VertexData>::Mesh(const std::vector<VertexData> &vertices,
     const std::vector<unsigned int> &indices, const BufferLayout &layout)
    : Mesh()
{
    // Define the mesh information into corresponding buffers
    DefineMesh(vertices, indices, layout);
}

/**
 * @brief Define the mesh using the provided vertex and index data.
 *
 * @param vertices The vertex data of the mesh.
 * @param indices The index data of the mesh.
 */
template<typename VertexData>
void Mesh<VertexData>::DefineMesh(const std::vector<VertexData> &vertices,
                 const std::vector<unsigned int> &indices, const BufferLayout &layout)
{
    // Save the vertex and index information of the mesh
    m_Vertices = vertices;
    m_Indices = indices;
    
    // Copy the vertex data in the buffer and define its layout
    m_VertexBuffer = std::make_shared<VertexBuffer>(vertices.data(),
        sizeof(vertices) * sizeof(VertexData));
    m_VertexBuffer->SetLayout(layout);
    // Copy the index data in the buffer
    m_IndexBuffer = std::make_shared<IndexBuffer>(indices.data(), sizeof(indices));
    
    // Add the buffers information to the vertex array
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

/**
 * Render the mesh.
 *
 * @param transform Transformation matrix of the geometry.
 */
template<typename VertexData>
void Mesh<VertexData>::DrawMesh(const glm::mat4& transform)
{
    bool init = m_VertexBuffer && m_IndexBuffer;
    
    // Verify that the vertex information has been set for the mesh
    if (!init)
    {
        CORE_WARN("Mesh vertex information has not been defined!");
        return;
    }
    
    if (m_Material)
        Renderer::Draw(m_VertexArray, m_Material, transform);
    else
        Renderer::Draw(m_VertexArray);
}
