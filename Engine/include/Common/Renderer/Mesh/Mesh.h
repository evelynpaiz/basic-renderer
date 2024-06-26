#pragma once

#include "Common/Renderer/Buffer/VertexArray.h"
#include "Common/Renderer/Buffer/VertexBuffer.h"
#include "Common/Renderer/Buffer/IndexBuffer.h"

#include "Common/Renderer/Material/Material.h"

#include "Common/Renderer/Renderer.h"

#include <glm/glm.hpp>

/**
 * Represents a mesh used for rendering geometry.
 *
 * The `Mesh` class provides functionality to define and render geometry using vertex data.
 * It encapsulates the necessary information, such as vertex positions, texture coordinates, normals,
 * etc., required to render a mesh. The class supports operations such as loading mesh data, binding
 * vertex buffers, and rendering the mesh.
 *
 * @tparam VertexData The type of vertex data used by the mesh.
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
    
    // Mesh definition
    // ----------------------------------------
    void DefineVertices(const std::vector<VertexData> &vertices, const BufferLayout &layout);
    void DefineIndices(const std::vector<unsigned int> &indices);
    
    /// @brief Define the mesh using the provided vertex and index data.
    /// @param vertices The vertex data of the mesh.
    /// @param indices The index data of the mesh.
    /// @param layout The layout of the vertex data in the buffer.
    void DefineMesh(const std::vector<VertexData> &vertices, const std::vector<unsigned int> &indices,
                    const BufferLayout &layout)
    {
        DefineVertices(vertices, layout);
        DefineIndices(indices);
    }
    
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
    void DrawMesh(const glm::mat4& transform = glm::mat4(1.0f),
                  const PrimitiveType &primitive = PrimitiveType::Triangles);
    
    // Mesh variables
    // ----------------------------------------
private:
    ///< Vertex data of the mesh.
    std::vector<std::vector<VertexData>> m_Vertices;
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
 * @param layout The layout of the vertex data in the buffer.
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
 * Define vertices that define the mesh.
 *
 * @param vertices The vertex data of the mesh.
 * @param layout The layout of the vertex data in the buffer.
 */
template<typename VertexData>
void Mesh<VertexData>::DefineVertices(const std::vector<VertexData> &vertices, const BufferLayout &layout)
{
    // Save the vertex information of the mesh
    m_Vertices.push_back(vertices);
    
    // Copy the vertex data in the buffer and define its layout
    m_VertexBuffer = std::make_shared<VertexBuffer>(vertices.data(),
        vertices.size() * sizeof(VertexData), vertices.size());
    m_VertexBuffer->SetLayout(layout);
    
    // Add the buffer information to the vertex array
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
}

/**
 * Define the indices that the mesh should use when it is drawed.
 *
 * @param indices The index data of the mesh.
 */
template<typename VertexData>
void Mesh<VertexData>::DefineIndices(const std::vector<unsigned int> &indices)
{
    // Save the index information of the mesh
    m_Indices = indices;
    
    // Copy the index data in the buffer
    m_IndexBuffer = std::make_shared<IndexBuffer>(indices.data(), indices.size());
    
    // Add the buffer information to the vertex array
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);
}

/**
 * Render the mesh.
 *
 * @param transform Transformation matrix of the geometry.
 * @param primitive The type of primitive to be drawn (e.g., Points, Lines, Triangles).
 */
template<typename VertexData>
void Mesh<VertexData>::DrawMesh(const glm::mat4 &transform,
                                const PrimitiveType &primitive)
{
    // Verify that the vertex information has been set for the mesh
    if (!m_VertexBuffer  && !m_IndexBuffer)
    {
        CORE_WARN("Mesh vertex or index information has not been defined!");
        return;
    }
    
    if (m_Material)
        Renderer::Draw(m_VertexArray, m_Material, transform, primitive);
    else
        Renderer::Draw(m_VertexArray, primitive);
}
