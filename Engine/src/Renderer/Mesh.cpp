#include "enginepch.h"
#include "Renderer/Mesh.h"

#include "Renderer/Renderer.h"

/**
 * Generate an empty mesh.
 */
Mesh::Mesh()
{
    m_VertexArray = std::make_shared<VertexArray>();
}

/**
 * Generate a mesh from a set of vertices and incides defined.
 *
 * @param vertices The vertex data of the mesh.
 * @param indices The index data of the mesh.
 */
Mesh::Mesh(const std::vector<VertexData> &vertices,
     const std::vector<unsigned int> &indices)
    : Mesh()
{
    // Define the mesh information into corresponding buffers
    DefineMesh(vertices, indices);
}

/**
 * @brief Define the mesh using the provided vertex and index data.
 *
 * @param vertices The vertex data of the mesh.
 * @param indices The index data of the mesh.
 */
void Mesh::DefineMesh(const std::vector<VertexData> &vertices,
                 const std::vector<unsigned int> &indices)
{
    // Save the vertex and index information of the mesh
    m_Vertices = vertices;
    m_Indices = indices;
    
    // Copy the vertex data in the buffer and define its layout
    m_VertexBuffer = std::make_shared<VertexBuffer>(vertices.data(),
        sizeof(vertices) * sizeof(VertexData));
    m_VertexBuffer->SetLayout({
        { "a_Position", DataType::Vec4 },
        { "a_TextureCoord", DataType::Vec2 }
    });
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
void Mesh::DrawMesh(const glm::mat4& transform)
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
